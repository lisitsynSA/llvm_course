#include "../include/ReplayGen.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

void ReplayGen::collectInfo(TraceInfo &trace) {
  uint64_t CallStack = 0;
  for (auto &Rec : trace.Trace) {
    if (Rec.Hdr.type == EVENT_FUNC_START) {
      if (CallStack == 0)
        ReplayRecs.push_back(&Rec);
      CallStack++;
    }
    if (Rec.Hdr.type == EVENT_RETURN) {
      CallStack--;
    }
    if (Rec.Hdr.type == EVENT_EXTERNAL_CALL) {
      Function *Callee = getCallee(Rec.Hdr.op_id);
      if (Callee)
        ExtFuncsInfo[Callee].push_back(&Rec);
    }
  }
}

Value *ReplayGen::createValueFromBits(IRBuilder<> &Builder, Type *Ty,
                                      uint64_t bits) {
  if (Ty->isIntegerTy()) {
    unsigned width = Ty->getIntegerBitWidth();
    return ConstantInt::get(Ctx, APInt(width, bits, true));
  }
  if (Ty->isPointerTy()) {
    Value *IntVal = ConstantInt::get(Type::getInt64Ty(Ctx), bits);
    return Builder.CreateIntToPtr(IntVal, Ty);
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

Function *ReplayGen::createMockFunction(Function *F) {
  const std::string &Name = F->getName().str();
  outs() << "#  createMockFunction for " << Name << '\n';
  FunctionType *FT = F->getFunctionType();
  Function *Mock = Function::Create(FT, GlobalValue::InternalLinkage,
                                    Name + ".mock", M.get());
  BasicBlock *Entry = BasicBlock::Create(Ctx, "entry", Mock);
  IRBuilder<> Builder(Entry);

  auto &Recs = ExtFuncsInfo[F];
  if (Recs.empty()) {
    // Never return from function
    Builder.CreateUnreachable();
    return Mock;
  }

  TraceRecord *Rec = Recs.front();
  Recs.erase(Recs.begin());

  Value *RetVal = createValueFromBits(Builder, FT->getReturnType(), Rec->Ret);
  Builder.CreateRet(RetVal);

  instrumentFuncStart(Mock, 0);
  return Mock;
}

void ReplayGen::createMocks() {
  // Mock functions generation for external functions
  for (auto &[id, F] : FuncsMap) {
    if (F->isDeclaration()) {
      MocksMap[F] = createMockFunction(F);
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
  outs() << "#  createOrigCall for " << Name << '\n';
  FunctionType *FT = F->getFunctionType();
  if (Name == "main")
    F->setName(Name + ".orig");

  Value *FuncName = Builder.CreateGlobalStringPtr(F->getName());
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
  Builder.CreateCall(TraceCallFn, {Builder.getInt64(0), FuncName, ArgArrayPtr,
                                   Builder.getInt64(ArgI64s.size())});
  Builder.CreateCall(F, Args);
}

void ReplayGen::replayChain() {
  Function *NewMain =
      Function::Create(FunctionType::get(Type::getVoidTy(Ctx), false),
                       GlobalValue::ExternalLinkage, "main.new", M.get());
  BasicBlock *EntryBB = BasicBlock::Create(Ctx, "entry", NewMain);
  IRBuilder<> Builder(Ctx);
  Builder.SetInsertPoint(EntryBB);
  // Create Replay chain
  for (auto Rec : ReplayRecs) {
    createOrigCall(Builder, Rec);
  }
  // Rename new main function
  NewMain->setName("main");
  Builder.CreateRetVoid();
}

void ReplayGen::replayGeneration(TraceInfo &trace) {
  outs() << "[UNITOOL] Replay generation\n";

  initTracingFunctions();
  collectInfo(trace);
  createMocks();
  replayChain();

  bool verif = verifyModule(*M, &outs());
  outs() << "[UNITOOL] Replay Verification: " << (verif ? "FAIL\n" : "OK\n");
}