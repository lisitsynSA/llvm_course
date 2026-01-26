#include "../include/ModuleInstrument.h"
#include "../include/trace.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

bool ModuleInstrument::isFuncLogger(StringRef name) {
  return name == "trace_called" || name == "trace_external_call" ||
         name == "trace_return" || name == "trace_memory";
}

void ModuleInstrument::initTracingFunctions() {
  VoidTy = Type::getVoidTy(Ctx);
  Int8Ty = Type::getInt8Ty(Ctx);
  Int8PtrTy = PointerType::get(Int8Ty, 0);
  Int64Ty = Type::getInt64Ty(Ctx);
  Int64PtrTy = PointerType::get(Int64Ty, 0);

  // void trace_called(uint64_t func_id, uint64_t *args, uint64_t num_args)
  std::vector<Type *> CallArgs = {Int64Ty, Int64PtrTy, Int64Ty};
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

Value *ModuleInstrument::valueToI64(IRBuilder<> &Builder, Value *V) {
  if (!V) {
    return Builder.getInt64(0);
  }
  Type *Ty = V->getType();
  if (Ty->isPointerTy()) {
    return Builder.CreatePtrToInt(V, Type::getInt64Ty(Ctx));
  }
  if (Ty->isIntegerTy()) {
    unsigned BitWidth = Ty->getIntegerBitWidth();
    if (BitWidth < 64) {
      V = Builder.CreateZExtOrTrunc(V, Type::getInt64Ty(Ctx));
    } else if (BitWidth > 64) {
      V = Builder.CreateTrunc(V, Type::getInt64Ty(Ctx));
    }
    return V;
  }
  if (Ty->isFloatTy()) {
    Value *Bits = Builder.CreateBitCast(V, Type::getInt32Ty(Ctx));
    return Builder.CreateZExt(Bits, Type::getInt64Ty(Ctx));
  }
  if (Ty->isDoubleTy()) {
    return Builder.CreateBitCast(V, Type::getInt64Ty(Ctx));
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
  Value *Alloca = Builder.CreateAlloca(ArrayTy, nullptr);
  for (size_t i = 0; i < Arr.size(); ++i) {
    Value *GEP = Builder.CreateConstInBoundsGEP2_32(ArrayTy, Alloca, 0, i);
    Builder.CreateStore(Arr[i], GEP);
  }
  return Builder.CreateBitCast(Alloca, Int64PtrTy);
}

void ModuleInstrument::instrumentCall(CallInst *Call, uint64_t Id) {
  IRBuilder<> Builder(Ctx);
  if (isa<IntrinsicInst>(Call))
    return;

  Function *CalleeFunc = Call->getCalledFunction();
  if (!CalleeFunc) {
    // TODO: support function pointer call
    return;
  }

  // Skip all internal functions
  if (!CalleeFunc->isDeclaration() || isFuncLogger(CalleeFunc->getName()))
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

void ModuleInstrument::instrumentMem(Value *V, Value *A, Instruction *I,
                                     uint64_t type, uint64_t Id) {
  IRBuilder<> Builder(Ctx);
  // Check mem2reg allocations
  if (auto *Alloca = dyn_cast<AllocaInst>(A)) {
    bool IsReg = true;
    for (auto &U : Alloca->uses()) {
      User *user = U.getUser();
      if (!dyn_cast<StoreInst>(user) && !dyn_cast<LoadInst>(user)) {
        IsReg = false;
      }
    }
    if (IsReg)
      return;
  }
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
  IRBuilder<> Builder(Ctx);
  // Collect ponters chain
  Builder.SetInsertPoint(Gep->getNextNode());
  std::vector<Value *> PtrI64s;
  Value *CurPtr = Gep->getOperand(0);
  Type *CurType = Gep->getSourceElementType();
  for (auto &index : Gep->indices()) {
    Value *GEP = Builder.CreateGEP(CurType, CurPtr, {index});
    Value *AsI64 = valueToI64(Builder, GEP);
    PtrI64s.push_back(AsI64);
    CurPtr = GEP;
    CurType = CurPtr->getType();
  }
  Value *Ptrs = instrumentArray(Builder, PtrI64s);

  Value *GepId = Builder.getInt64(Id);
  Value *Addr = valueToI64(Builder, Gep->getOperand(0));
  Value *Size = getTypeSize(Builder, Gep->getResultElementType());
  Value *Val = Builder.getInt64(PtrI64s.size());
  Value *Type = Builder.getInt8(MEM_GEP);

  // void trace_memory(uint64_t op_id, uint64_t addr, uint64_t size, uint64_t
  //                   value, uint8_t mem_type, uint64_t *ptrs)
  Builder.CreateCall(TraceMemFn, {GepId, Addr, Size, Val, Type, Ptrs});
}

void ModuleInstrument::instrumentFuncStart(Function *F, uint64_t Id) {
  if (F->empty() || F->isDeclaration() || isFuncLogger(F->getName()))
    return;
  IRBuilder<> Builder(Ctx);
  Value *OpId = Builder.getInt64(Id);
  // В начало первой инструкции — вставляем trace_called
  BasicBlock &EntryBB = F->getEntryBlock();
  Builder.SetInsertPoint(&EntryBB, EntryBB.begin());

  // Собираем аргументы как i64
  std::vector<Value *> ArgI64s;
  for (auto &Arg : F->args()) {
    Value *AsI64 = valueToI64(Builder, &Arg);
    ArgI64s.push_back(AsI64);
  }
  Value *ArgArrayPtr = instrumentArray(Builder, ArgI64s);

  // trace_called(uint64_t func_id, uint64_t *args, uint64_t num_args)
  Builder.CreateCall(TraceCallFn,
                     {OpId, ArgArrayPtr, Builder.getInt64(ArgI64s.size())});
}

void ModuleInstrument::InstrumentModule() {
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
}

ModuleInstrument::ModuleInstrument(std::string path, llvm::LLVMContext &C)
    : ModuleInfo(path, C) {
  outs() << "[UNITOOL] Instrument " << path << "\n";
  InstrumentModule();
  bool verif = verifyModule(*M, &outs());
  outs() << "[UNITOOL] Instrumentation Verification: "
         << (verif ? "FAIL\n" : "OK\n");
}