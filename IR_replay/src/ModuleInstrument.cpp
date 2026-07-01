#include "../include/ModuleInstrument.h"
#include "../include/trace.h"
#include "llvm/IR/Verifier.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>

using namespace llvm;

void ModuleInstrument::initTracingFunctions() {
  VoidTy = Type::getVoidTy(Ctx);
  Int8Ty = Type::getInt8Ty(Ctx);
  Int8PtrTy = PointerType::get(Int8Ty, 0);
  Int64Ty = Type::getInt64Ty(Ctx);
  Int64PtrTy = PointerType::get(Int64Ty, 0);

  // void trace_called(uint64_t op_id, uint8_t *name, uint64_t *args, uint64_t
  //                   num_args)
  std::vector<Type *> CallArgs = {Int64Ty, Int8PtrTy, Int64PtrTy, Int64Ty};
  TraceCallFnTy = FunctionType::get(VoidTy, CallArgs, false);
  TraceCallFn = M->getOrInsertFunction("trace_called", TraceCallFnTy);

  // void trace_return(uint64_t op_id, uint64_t return_value)
  std::vector<Type *> ReturnArgs = {Int64Ty, Int64Ty};
  TraceReturnFnTy = FunctionType::get(VoidTy, ReturnArgs, false);
  TraceReturnFn = M->getOrInsertFunction("trace_return", TraceReturnFnTy);

  // void trace_external_call(uint64_t op_id, uint64_t *args, uint64_t num_args,
  //                          uint64_t return_value)
  std::vector<Type *> ExtCallArgs = {Int64Ty, Int64PtrTy, Int64Ty, Int64Ty};
  TraceExternalCallFnTy = FunctionType::get(VoidTy, ExtCallArgs, false);
  TraceExternalCallFn =
      M->getOrInsertFunction("trace_external_call", TraceExternalCallFnTy);

  // void trace_memory(uint64_t op_id, uint64_t addr, uint64_t size, uint64_t
  //                   value, uint8_t mem_type, uint64_t *ptrs)
  std::vector<Type *> MemArgs = {Int64Ty, Int64Ty, Int64Ty,
                                 Int64Ty, Int8Ty,  Int64PtrTy};
  TraceMemFnTy = FunctionType::get(VoidTy, MemArgs, false);
  TraceMemFn = M->getOrInsertFunction("trace_memory", TraceMemFnTy);
}

void ModuleInstrument::instruemntAllInstructions() {
  IRBuilder<> Builder(Ctx);
  std::vector<Type *> argsRef = {Int8PtrTy};
  FunctionType *printType =
      FunctionType::get(Builder.getInt32Ty(), argsRef, true);
  FunctionCallee printFunc = M->getOrInsertFunction("printf", printType);
  uint64_t Number = 0;
  Value *PrintFormat = nullptr;
  for (auto &[Id, F] : FuncsMap) {
    if (F->empty() || F->isDeclaration())
      continue;
    for (auto &BB : *F) {
      for (auto &I : BB) {
        if (isa<PHINode>(I))
          continue;
        Builder.SetInsertPoint(&I);
        Value *opName = Builder.CreateGlobalString(I.getOpcodeName());
        if (!PrintFormat)
          PrintFormat = Builder.CreateGlobalString("\%5d: \%s\n");
        Value *NumVal = Builder.getInt64(Number);
        Number++;
        Builder.CreateCall(printFunc, {PrintFormat, NumVal, opName});
      }
    }
  }
}

Value *ModuleInstrument::valueToI64(IRBuilder<> &Builder, Value *V) {
  if (!V) {
    return Builder.getInt64(0);
  }
  Type *Ty = V->getType();
  if (Ty->isPointerTy()) {
    return Builder.CreatePtrToInt(V, Int64Ty);
  }
  if (Ty->isIntegerTy()) {
    return Builder.CreateZExtOrTrunc(V, Int64Ty);
  }
  if (Ty->isFloatTy()) {
    Value *Bits = Builder.CreateBitCast(V, Type::getInt32Ty(Ctx));
    return Builder.CreateZExt(Bits, Int64Ty);
  }
  if (Ty->isDoubleTy()) {
    return Builder.CreateBitCast(V, Int64Ty);
  }
  if (Ty->isVoidTy()) {
    return Builder.getInt64(0);
  }
  // TODO: vectors and structures support
  // serialization through the fields should be here
  return Builder.getInt64(0);
}

Value *ModuleInstrument::instrumentArray(IRBuilder<> &Builder,
                                         std::vector<Value *> &Arr) {
  ArrayType *ArrayTy = ArrayType::get(Int64Ty, Arr.size());
  if (Arrays.find(Arr.size()) == Arrays.end()) {
    GlobalVariable *Array =
        new GlobalVariable(*Builder.GetInsertBlock()->getModule(), ArrayTy,
                           false, GlobalValue::PrivateLinkage, 0);
    Array->setInitializer(ConstantAggregateZero::get(ArrayTy));
    Arrays[Arr.size()] = Array;
  }
  GlobalVariable *Array = Arrays[Arr.size()];
  for (size_t i = 0; i < Arr.size(); ++i) {
    Value *GEP = Builder.CreateConstInBoundsGEP2_32(ArrayTy, Array, 0, i);
    Builder.CreateStore(Arr[i], GEP);
  }
  return Builder.CreateBitCast(Array, Int64PtrTy);
}

void ModuleInstrument::instrumentCall(CallInst *Call, uint64_t Id) {
  IRBuilder<> Builder(Ctx);
  Function *CalleeFunc = Call->getCalledFunction();
  if (!CalleeFunc) {
    // TODO: support function pointer call
    return;
  }

  // Skip all internal functions
  if (!CalleeFunc->isDeclaration())
    return;

  Builder.SetInsertPoint(Call->getNextNode());
  Value *CallId = Builder.getInt64(Id);

  // Collect arguments
  std::vector<Value *> ExtArgI64s;
  for (auto &Arg : Call->args()) {
    Value *AsI64 = valueToI64(Builder, Arg);
    ExtArgI64s.push_back(AsI64);
  }
  Value *ExtArrayPtr = instrumentArray(Builder, ExtArgI64s);
  Value *ExtRetValue = valueToI64(Builder, Call);

  // void trace_external_call(uint64_t op_id, uint64_t *args, uint64_t num_args,
  //                          uint64_t return_value)
  Builder.CreateCall(
      TraceExternalCallFn,
      {CallId, ExtArrayPtr, Builder.getInt64(ExtArgI64s.size()), ExtRetValue});
}

void ModuleInstrument::instrumentRet(llvm::ReturnInst *Ret, uint64_t Id) {
  IRBuilder<> Builder(Ctx);
  Builder.SetInsertPoint(Ret);
  Value *RetI64 = valueToI64(Builder, Ret->getReturnValue());
  Value *RetId = Builder.getInt64(Id);
  // void trace_return(uint64_t op_id, uint64_t return_value)
  Builder.CreateCall(TraceReturnFn, {RetId, RetI64});
}

bool ModuleInstrument::isLocalMem(Value *V) {
  for (auto &U : V->uses()) {
    User *user = U.getUser();
    if (dyn_cast<StoreInst>(user) || dyn_cast<LoadInst>(user)) {
      continue;
    }
    if (auto *Call = dyn_cast<CallInst>(user)) {
      if (Call->getCalledFunction()->isIntrinsic())
        continue;
    }
    if (auto *Gep = dyn_cast<GetElementPtrInst>(user))
      if (isLocalMem(Gep))
        continue;
    return false;
  }
  return true;
}

bool ModuleInstrument::isAllocaMem(Value *V) {
  if (auto *Alloca = dyn_cast<AllocaInst>(V)) {
    return isLocalMem(Alloca);
  }
  if (auto *Gep = dyn_cast<GetElementPtrInst>(V)) {
    return isLocalMem(Gep->getOperand(0));
  }
  if (auto *Load = dyn_cast<LoadInst>(V)) {
    return isLocalMem(Load->getOperand(0));
  }
  return false;
}

void ModuleInstrument::instrumentMem(Value *V, Value *A, Instruction *I,
                                     uint64_t type, uint64_t Id) {
  // Check mem2reg allocations
  if (isAllocaMem(A)) {
    return;
  }
  IRBuilder<> Builder(Ctx);
  Builder.SetInsertPoint(I->getNextNode());
  Value *Ptrs = Builder.CreateBitCast(Builder.getInt64(0), Int64PtrTy);

  Value *OpId = Builder.getInt64(Id);
  Value *Addr = valueToI64(Builder, A);
  Value *Size = getTypeSize(Builder, V->getType());
  Value *Val = valueToI64(Builder, V);
  Value *Type = Builder.getInt8(type);

  // void trace_memory(uint64_t op_id, uint64_t addr, uint64_t size, uint64_t
  //                   value, uint8_t mem_type, uint64_t *ptrs)
  Builder.CreateCall(TraceMemFn, {OpId, Addr, Size, Val, Type, Ptrs});
}

void ModuleInstrument::instrumentGep(GetElementPtrInst *Gep, uint64_t Id) {
  // Check mem2reg allocations
  if (isAllocaMem(Gep->getOperand(0))) {
    return;
  }
  IRBuilder<> Builder(Ctx);
  // Collect ponters chain
  Builder.SetInsertPoint(Gep->getNextNode());
  std::vector<Value *> PtrI64s;
  Value *CurPtr = Gep->getOperand(0);
  Type *CurType = Gep->getSourceElementType();
  for (auto &index : Gep->indices()) {
    Value *GEP0 = Builder.CreateGEP(CurType, CurPtr, {Builder.getInt64(0)});
    PtrI64s.push_back(valueToI64(Builder, GEP0));
    Value *GEP = Builder.CreateGEP(CurType, CurPtr, {index});
    PtrI64s.push_back(valueToI64(Builder, GEP));
    CurPtr = GEP;
    CurType = CurPtr->getType();
  }
  Value *Ptrs = instrumentArray(Builder, PtrI64s);

  Value *GepId = Builder.getInt64(Id);
  Value *Addr = valueToI64(Builder, Gep->getOperand(0));
  Value *Size = getTypeSize(Builder, Gep->getResultElementType());
  Value *Val = Builder.getInt64(PtrI64s.size());
  Value *Type = Builder.getInt8(MEM_GEP);

  Builder.CreateCall(TraceMemFn, {GepId, Addr, Size, Val, Type, Ptrs});
}

void ModuleInstrument::instrumentFuncStart(Function *F, uint64_t Id) {
  if (F->empty() || F->isDeclaration())
    return;
  IRBuilder<> Builder(Ctx);
  Value *OpId = Builder.getInt64(Id);
  // Insert trace_called in the function begin
  BasicBlock &EntryBB = F->getEntryBlock();
  Builder.SetInsertPoint(&EntryBB, EntryBB.begin());
  Value *FuncName = Builder.CreateGlobalString(F->getName());

  // Gather arguments as i64
  std::vector<Value *> ArgI64s;
  for (auto &Arg : F->args()) {
    Value *AsI64 = valueToI64(Builder, &Arg);
    ArgI64s.push_back(AsI64);
  }
  Value *ArgArrayPtr = instrumentArray(Builder, ArgI64s);

  // void trace_called(uint64_t op_id, uint8_t *name, uint64_t *args, uint64_t
  //                   num_args)
  Builder.CreateCall(TraceCallFn, {OpId, FuncName, ArgArrayPtr,
                                   Builder.getInt64(ArgI64s.size())});
}

void ModuleInstrument::InstrumentModule(bool Debug) {
  outs() << "[UNITOOL] Instrumentation\n";
  initTracingFunctions();

  for (auto &[Id, Call] : CallsMap) {
    instrumentCall(Call, Id);
  }

  for (auto &[Id, Ret] : RetsMap) {
    instrumentRet(Ret, Id);
  }

  for (auto &[Id, Load] : LoadsMap) {
    instrumentMem(Load, Load->getOperand(0), Load, MEM_LOAD, Id);
  }

  for (auto &[Id, Store] : StoresMap) {
    instrumentMem(Store->getOperand(0), Store->getOperand(1), Store, MEM_STORE,
                  Id);
  }

  for (auto &[Id, Gep] : GepsMap) {
    instrumentGep(Gep, Id);
  }

  for (auto &[Id, F] : FuncsMap) {
    instrumentFuncStart(F, Id);
  }

  if (Debug)
    instruemntAllInstructions();

  bool verif = verifyModule(*M, &outs());
  outs() << "[UNITOOL] Instrumentation Verification: "
         << (verif ? "FAIL\n" : "OK\n");
}
