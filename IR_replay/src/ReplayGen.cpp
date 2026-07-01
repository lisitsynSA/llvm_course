#include "../include/ReplayGen.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include <cstdint>
#include <fstream>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <set>
#include <string>

using namespace llvm;

void ReplayGen::collectInfo(TraceInfo &trace) {
  uint64_t CallStack = 0;
  for (auto &Rec : trace.Trace) {
    if (Rec.Hdr.type == EVENT_FUNC_START) {
      if (CallStack == 0)
        ReplayEntryPoints.push_back(&Rec);
      CallStack++;
    }
    if (Rec.Hdr.type == EVENT_RETURN) {
      CallStack--;
    }
    if (Rec.Hdr.type == EVENT_EXTERNAL_CALL) {
      Function *Callee = getCallee(Rec.Hdr.op_id);
      if (Callee) {
        ExtFuncsCalls[Callee].push_back(&Rec);
        LastExtFunc = Callee;
      }
    }
    if (Rec.Hdr.type == EVENT_MEMOP) {
      // TODO: Support Memory Update Points from EntryPoints and External Calls
      handleMem(Rec);
    }
  }
  if (CallStack == 0)
    LastExtFunc = nullptr;
  if (LastExtFunc) {
    outs() << "\tReplay finish at " << ExtFuncsCalls[LastExtFunc].size()
           << " call of " << LastExtFunc->getName() << '\n';
  }
}

void ReplayGen::removeOptnoneAttrs() {
  for (auto &[Id, F] : FuncsMap) {
    if (F->empty() || F->isDeclaration())
      continue;
    F->removeFnAttr(Attribute::AttrKind::OptimizeNone);
  }
}

Value *ReplayGen::createValueFromBits(IRBuilder<> &Builder, Type *Ty,
                                      uint64_t bits) {
  if (Ty->isIntegerTy()) {
    unsigned width = Ty->getIntegerBitWidth();
    return ConstantInt::get(Ctx, APInt(width, bits, true));
  }
  if (Ty->isPointerTy()) {
    if (inMem(bits)) {
      return Builder.CreateBitCast(getMem(Builder, bits), Ty);
    } else {
      Value *IntVal = ConstantInt::get(Type::getInt64Ty(Ctx), bits);
      return Builder.CreateIntToPtr(IntVal, Ty);
    }
  }
  if (Ty->isFloatTy()) {
    float f;
    memcpy(&f, &bits, sizeof(float));
    return ConstantFP::get(Ty, f);
  }
  if (Ty->isDoubleTy()) {
    double d;
    memcpy(&d, &bits, sizeof(d));
    return ConstantFP::get(Ty, d);
  }
  return Constant::getNullValue(Ty);
}

Function *ReplayGen::createMockFunction(Function *F, bool isAllow) {
  const std::string &Name = F->getName().str();
  auto &Recs = ExtFuncsCalls[F];
  outs() << "\tcreateMockFunction for " << Name << " (" << Recs.size()
         << " calls)\n";
  bool isLastCall = (F == LastExtFunc);
  if (isAllow && !isLastCall) {
    outs() << "\t\tskip creation\n";
    return F;
  }
  FunctionType *FT = F->getFunctionType();
  Type *RetTy = FT->getReturnType();
  Function *Mock = Function::Create(FT, GlobalValue::ExternalLinkage,
                                    Name + ".mock", ExtMod.get());
  BasicBlock *Entry = BasicBlock::Create(Ctx, "entry", Mock);
  IRBuilder<> Builder(Entry);

  if (Recs.empty()) {
    // Never return from function
    Builder.CreateUnreachable();
    return Mock;
  }

  if (!isAllow && RetTy->isVoidTy()) {
    Builder.CreateRetVoid();
    return Mock;
  }

  // @0 = private global i64 zeroinitializer
  GlobalVariable *Counter = new GlobalVariable(*ExtMod, Int64Ty, false,
                                               GlobalValue::PrivateLinkage, 0);
  Counter->setInitializer(ConstantAggregateZero::get(Int64Ty));

  Value *Loaded = Builder.CreateLoad(Int64Ty, Counter);
  Value *Inc = Builder.CreateAdd(Loaded, Builder.getInt64(1));
  Builder.CreateStore(Inc, Counter);
  BasicBlock *Continue = BasicBlock::Create(Ctx, "continue", Mock);
  BasicBlock *Exit = BasicBlock::Create(Ctx, "exit", Mock);
  Value *Cond = Builder.CreateICmpEQ(Loaded, Builder.getInt64(Recs.size()));
  Builder.CreateCondBr(Cond, Exit, Continue);

  // exit:
  //   unreachable
  Builder.SetInsertPoint(Exit);
  Builder.CreateUnreachable();
  Builder.SetInsertPoint(Continue);

  if (isAllow) {
    // Allowed LastExtFunc
    outs() << "\t\tforward execution\n";
    std::vector<Value *> Args;
    for (auto &Arg : Mock->args()) {
      Args.push_back(&Arg);
    }
    FunctionCallee OrigCallee = ExtMod->getOrInsertFunction(Name, FT);
    Value *Call = Builder.CreateCall(OrigCallee, Args);

    if (FT->getReturnType()->isVoidTy()) {
      Builder.CreateRetVoid();
    } else {
      Builder.CreateRet(Call);
    }
    return Mock;
  }

  // TODO: Support Memory Update Points

  if (RetTy->isPointerTy()) {
    SwitchInst *Switch = Builder.CreateSwitch(Loaded, Exit);
    uint64_t i = 0;
    for (auto Rec : Recs) {
      BasicBlock *Case = BasicBlock::Create(Ctx, "", Mock);
      Builder.SetInsertPoint(Case);
      Value *RetVal = createValueFromBits(Builder, RetTy, Rec->Ret);
      Builder.CreateRet(RetVal);
      Switch->addCase(Builder.getInt64(i++), Case);
    }
    return Mock;
  }

  ArrayType *RetArrayTy = ArrayType::get(RetTy, Recs.size());
  GlobalVariable *RetArray = new GlobalVariable(*ExtMod, RetArrayTy, false,
                                                GlobalValue::PrivateLinkage, 0);
  std::vector<Constant *> RetsVals;
  unsigned width = RetTy->getIntegerBitWidth();
  for (auto Rec : Recs) {
    RetsVals.push_back(ConstantInt::get(Ctx, APInt(width, Rec->Ret, true)));
  }
  Constant *RetInit = ConstantArray::get(RetArrayTy, RetsVals);
  RetArray->setInitializer(RetInit);
  std::vector<Value *> GepArgs;
  GepArgs.push_back(Builder.getInt64(0));
  GepArgs.push_back(Loaded);
  Value *RetPointer = Builder.CreateGEP(RetArrayTy, RetArray, GepArgs);
  Value *RetLoad = Builder.CreateLoad(RetTy, RetPointer);
  Builder.CreateRet(RetLoad);

  // instrumentFuncStart(Mock, 0);
  return Mock;
}

void ReplayGen::createMocks(std::string &AllowFuncsFile) {
  std::set<std::string> AllowFuncs;
  if (!AllowFuncsFile.empty()) {
    std::ifstream File(AllowFuncsFile);
    std::string FuncName;
    while (std::getline(File, FuncName)) {
      AllowFuncs.insert(std::move(FuncName));
      File.clear();
    }
  }
  // Mock functions generation for external functions
  for (auto &[id, F] : FuncsMap) {
    if (F->isDeclaration()) {
      bool isAllow = AllowFuncs.count(F->getName().str()) != 0;
      Function *MockOrOrig = createMockFunction(F, isAllow);
      MocksMap[F] = M->getOrInsertFunction(MockOrOrig->getName(),
                                           MockOrOrig->getFunctionType());
    }
  }
  // Change Calls to mock functions
  for (auto &[id, Call] : CallsMap) {
    Function *Callee = Call->getCalledFunction();
    if (Callee->isDeclaration()) {
      Call->setCalledFunction(MocksMap[Callee]);
    }
  }
}

void ReplayGen::createOrigCall(IRBuilder<> &Builder, TraceRecord *Rec) {
  Function *F = FuncsMap[Rec->Hdr.op_id];
  const std::string &Name = F->getName().str();
  outs() << "\tcreateOrigCall for " << Name << '\n';
  FunctionType *FT = F->getFunctionType();
  if (Name == "main")
    F->setName(Name + ".orig");

  // TODO: Support Memory Update Points

  Value *FuncNameStr = Builder.CreateGlobalString(F->getName());
  Value *FuncName = Builder.CreateBitCast(FuncNameStr, Int8PtrTy);
  uint64_t i = 0;
  std::vector<Value *> Args;
  std::vector<Value *> ArgI64s;
  for (auto &Arg : F->args()) {
    Args.push_back(createValueFromBits(Builder, Arg.getType(), Rec->Args[i]));
    ArgI64s.push_back(Builder.getInt64(Rec->Args[i]));
    i++;
  }
  Value *ArgArrayPtr = instrumentArray(Builder, ArgI64s);

  // void trace_called(uint64_t op_id, uint8_t *name, uint64_t *args, uint64_t
  //                   num_args)
  FunctionCallee ExtTraceCallFn =
      ExtMod->getOrInsertFunction("trace_called", TraceCallFnTy);
  Builder.CreateCall(ExtTraceCallFn,
                     {Builder.getInt64(0), FuncName, ArgArrayPtr,
                      Builder.getInt64(ArgI64s.size())});
  FunctionCallee ExtF =
      ExtMod->getOrInsertFunction(F->getName(), F->getFunctionType());
  Builder.CreateCall(ExtF, Args);
}

void ReplayGen::replayChain() {
  Function *NewMain =
      Function::Create(FunctionType::get(Type::getInt32Ty(Ctx), false),
                       GlobalValue::ExternalLinkage, "main.new", ExtMod.get());
  BasicBlock *EntryBB = BasicBlock::Create(Ctx, "entry", NewMain);
  IRBuilder<> Builder(Ctx);
  Builder.SetInsertPoint(EntryBB);
  // Create Replay chain
  for (auto Rec : ReplayEntryPoints) {
    createOrigCall(Builder, Rec);
  }
  // Rename new main function
  NewMain->setName("main");
  Builder.CreateRet(Builder.getInt32(0));
}

void ReplayGen::replayGeneration(TraceInfo &trace, std::string &AllowFunsFile,
                                 bool Debug) {
  outs() << "[UNITOOL] Replay generation\n";

  initTracingFunctions();
  collectInfo(trace);
  removeOptnoneAttrs();
  prepareArrays();
  createMocks(AllowFunsFile);
  replayChain();
  if (Debug) {
    instrumentAllInstructions();
    for (auto &[Id, F] : FuncsMap)
      instrumentFuncStart(F, Id);
  }

  bool verif = verifyModule(*M, &outs());
  outs() << "[UNITOOL] Replay Verification: " << (verif ? "FAIL\n" : "OK\n");
  verif = verifyModule(*ExtMod, &outs());
  outs() << "[UNITOOL] Compensation Verification: "
         << (verif ? "FAIL\n" : "OK\n");
}

void ReplayGen::addPrepCall() {
  FunctionCallee PrepFunc = ExtMod->getOrInsertFunction(
      "preparation_function", FunctionType::get(VoidTy, false));
  Function *Main = ExtMod->getFunction("main");
  if (Main) {
    IRBuilder<> Builder(&Main->getEntryBlock().front());
    Builder.CreateCall(PrepFunc, {});
  }
}
