#include "../include/TracePass.h"
#include "../include/trace.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>

using namespace llvm;

#define DEBUG_TYPE "trace-instrumentation"

int TraceInstrumentationPass::MemId = 0;

void TraceInstrumentationPass::initTracingFunctions(Module &M) {
  LLVMContext &Ctx = M.getContext();

  VoidTy = Type::getVoidTy(Ctx);
  Int8Ty = Type::getInt8Ty(Ctx);
  Int8PtrTy = PointerType::get(Int8Ty, 0);
  Int64Ty = Type::getInt64Ty(Ctx);
  Int64PtrTy = PointerType::get(Int64Ty, 0);

  // void @trace_called(i64 func_id, i64* args, i64 num_args)
  std::vector<Type *> CallArgs = {Int64Ty, Int64PtrTy, Int64Ty};
  TraceCallFnTy = FunctionType::get(VoidTy, CallArgs, false);
  TraceCallFn = M.getOrInsertFunction("trace_called", TraceCallFnTy);

  // void @trace_return(i64 func_id, i64 return_value)
  std::vector<Type *> ReturnArgs = {Int64Ty, Int64Ty};
  TraceReturnFnTy = FunctionType::get(VoidTy, ReturnArgs, false);
  TraceReturnFn = M.getOrInsertFunction("trace_return", TraceReturnFnTy);

  // void @trace_external_call(i64 func_id, i64* args, i64
  // num_args, i64 return_value)
  std::vector<Type *> ExtCallArgs = {Int64Ty, Int64PtrTy, Int64Ty, Int64Ty};
  TraceExternalCallFnTy = FunctionType::get(VoidTy, ExtCallArgs, false);
  TraceExternalCallFn =
      M.getOrInsertFunction("trace_external_call", TraceExternalCallFnTy);

  // void @trace_memory(i64 func_id, i64 memop_id, i64 addr,
  // i64 size, i64 value, i8 mem_type)
  std::vector<Type *> MemArgs = {Int64Ty, Int64Ty, Int64Ty,
                                 Int64Ty, Int64Ty, Int8Ty};
  TraceMemFnTy = FunctionType::get(VoidTy, MemArgs, false);
  TraceMemFn = M.getOrInsertFunction("trace_memory", TraceMemFnTy);
}

uint64_t TraceInstrumentationPass::getFunctionId(const Function &F) {
  const auto &name = F.getName().str();
  auto search = FuncIdMap.find(name);
  if (search == FuncIdMap.end()) {
    FuncIdMap[name] = static_cast<uint64_t>(std::hash<std::string>{}(name));
    return FuncIdMap[name];
  }
  return search->second;
}

Value *TraceInstrumentationPass::valueToI64(IRBuilder<> &Builder, Value *V) {
  LLVMContext &Ctx = Builder.getContext();
  Type *Ty = V->getType();

  if (Ty->isPointerTy()) {
    V = Builder.CreatePtrToInt(V, Type::getInt64Ty(Ctx));
    InsertedInstrs.insert(V);
    return V;
  }

  if (Ty->isIntegerTy()) {
    unsigned BitWidth = Ty->getIntegerBitWidth();
    if (BitWidth < 64) {
      V = Builder.CreateZExtOrTrunc(V, Type::getInt64Ty(Ctx));
    } else if (BitWidth > 64) {
      V = Builder.CreateTrunc(V, Type::getInt64Ty(Ctx));
    }
    InsertedInstrs.insert(V);
    return V;
  }

  if (Ty->isFloatTy()) {
    Value *Bits = Builder.CreateBitCast(V, Type::getInt32Ty(Ctx));
    InsertedInstrs.insert(Bits);
    V = Builder.CreateZExt(Bits, Type::getInt64Ty(Ctx));
    InsertedInstrs.insert(V);
    return V;
  }

  if (Ty->isDoubleTy()) {
    Value *Bits = Builder.CreateBitCast(V, Type::getInt64Ty(Ctx));
    InsertedInstrs.insert(Bits);
    return Bits;
  }

  // Для void и других типов — ноль
  if (Ty->isVoidTy()) {
    return ConstantInt::get(Ctx, APInt(64, 0));
  }

  // Упрощение: не поддерживаем векторы, структуры и т.п.
  // Можно добавить сериализацию по полям, но пока — ноль
  return ConstantInt::get(Ctx, APInt(64, 0));
}

void TraceInstrumentationPass::instrumentCall(IRBuilder<> &Builder,
                                              CallInst *Call) {
  Value *Callee = Call->getCalledOperand();
  Function *CalleeFunc = Call->getCalledFunction();

  if (isInstrInserted(Call))
    return;

  // Пропускаем intrinsic'и
  if (isa<IntrinsicInst>(Call))
    return;

  // Если вызов через указатель (неизвестная функция) — тоже можно
  // трассировать
  if (!CalleeFunc) {
    // Это вызов через функциональный указатель — сложнее, но можно
    // трассировать имя через адрес Упрощённо: пока пропускаем или
    // используем адрес
    return;
  }

  // Трассируем только внешние функции (не из этого модуля)
  if (!CalleeFunc->isDeclaration() || isFuncLogger(CalleeFunc->getName()))
    return;

  Builder.SetInsertPoint(Call->getNextNode());
  Value *ExtFuncId = Builder.getInt64(getFunctionId(*CalleeFunc));

  // Собираем аргументы как i64
  std::vector<Value *> ExtArgI64s;
  for (auto &Arg : Call->args()) {
    Value *AsI64 = valueToI64(Builder, Arg);
    ExtArgI64s.push_back(AsI64);
  }

  // Создаём массив i64
  ArrayType *ExtArrayTy = ArrayType::get(Int64Ty, ExtArgI64s.size());
  Value *ExtArray =
      Builder.CreateAlloca(ExtArrayTy, nullptr, "ext_arg_array_i64");
  InsertedInstrs.insert(ExtArray);
  for (size_t i = 0; i < ExtArgI64s.size(); ++i) {
    Value *GEP = Builder.CreateConstInBoundsGEP2_32(ExtArrayTy, ExtArray, 0, i);
    InsertedInstrs.insert(GEP);
    InsertedInstrs.insert(Builder.CreateStore(ExtArgI64s[i], GEP));
  }
  Value *ExtArrayPtr = Builder.CreateBitCast(ExtArray, Int64PtrTy);
  InsertedInstrs.insert(ExtArrayPtr);

  // Результат вызова
  Value *ExtRetValue = Call->getType()->isVoidTy() ? Builder.getInt64(0)
                                                   : valueToI64(Builder, Call);

  // Вставляем вызов трассировки ДО вызова
  InsertedInstrs.insert(Builder.CreateCall(
      TraceExternalCallFn, {ExtFuncId, ExtArrayPtr,
                            Builder.getInt64(ExtArgI64s.size()), ExtRetValue}));
}

void TraceInstrumentationPass::addMemoryTrace(IRBuilder<> &Builder, Value *V,
                                              Value *A, Instruction *I,
                                              uint64_t type) {
  if (isInstrInserted(I))
    return;
  if (type != MEM_UPD) {
    // Check mem2reg allocations
    if (auto *Alloca = dyn_cast<AllocaInst>(A)) {
      bool IsReg = true;
      for (auto &U : Alloca->uses()) {
        User *user = U.getUser();
        if (!dyn_cast<StoreInst>(user) && !dyn_cast<LoadInst>(user) &&
            !isInstrInserted(user)) {
          IsReg = false;
        }
      }
      if (IsReg)
        return;
    }
  } else {
    // Check updates from loggers or internal funcs
    if (auto *Call = dyn_cast<CallInst>(I)) {
      Function *CalleeFunc = Call->getCalledFunction();
      if (CalleeFunc &&
          (!CalleeFunc->isDeclaration() ||
           isFuncLogger(CalleeFunc->getName()) || isInstrInserted(Call)))
        return;
    }
  }
  Value *FuncId = Builder.getInt64(getFunctionId(*I->getParent()->getParent()));
  Builder.SetInsertPoint(I->getNextNode());

  // Получаем адрес и размер
  Value *Addr = valueToI64(Builder, A);
  Value *Size;
  if (V->getType()->isPointerTy()) {
    Size = Builder.getInt64(64);
  } else {
    Size = Builder.getInt64(V->getType()->getScalarSizeInBits());
  }
  Value *Val = valueToI64(Builder, V);
  Value *MemopId = Builder.getInt64(MemId++);
  Value *Type = Builder.getInt8(type);

  // void @trace_memory(i64 func_id, i64 memop_id, i64 addr,
  // i64 size, i64 value, i8 type)
  InsertedInstrs.insert(
      Builder.CreateCall(TraceMemFn, {FuncId, MemopId, Addr, Size, Val, Type}));
}

void TraceInstrumentationPass::addGepTrace(IRBuilder<> &Builder,
                                           GetElementPtrInst *Gep) {
  if (isInstrInserted(Gep))
    return;
  Value *FuncId =
      Builder.getInt64(getFunctionId(*Gep->getParent()->getParent()));
  Builder.SetInsertPoint(Gep->getNextNode());
  // Получаем адрес и размер
  Value *Addr = valueToI64(Builder, Gep);
  Value *V = Builder.getInt64(Gep->getNumIndices());
  Value *Size;
  if (Gep->getResultElementType()->isPointerTy()) {
    Size = Builder.getInt64(64);
  } else {
    Size = Builder.getInt64(Gep->getResultElementType()->getScalarSizeInBits());
  }
  Value *Val = valueToI64(Builder, V);
  Value *MemopId = Builder.getInt64(MemId++);
  Value *Type = Builder.getInt8(MEM_GEP);

  // void @trace_memory(i64 func_id, i64 memop_id, i64 addr,
  // i64 size, i64 value, i8 type)
  InsertedInstrs.insert(
      Builder.CreateCall(TraceMemFn, {FuncId, MemopId, Addr, Size, Val, Type}));
}

void TraceInstrumentationPass::instrumentFuncStart(IRBuilder<> &Builder,
                                                   Function &F) {
  Value *FuncId = Builder.getInt64(getFunctionId(F));
  // В начало первой инструкции — вставляем trace_called
  BasicBlock &EntryBB = F.getEntryBlock();
  Builder.SetInsertPoint(&EntryBB, EntryBB.begin());

  // Собираем аргументы как i64
  std::vector<Value *> ArgI64s;
  for (auto &Arg : F.args()) {
    Value *AsI64 = valueToI64(Builder, &Arg);
    ArgI64s.push_back(AsI64);
  }

  // Создаём массив i64 на стеке
  ArrayType *ArgArrayTy = ArrayType::get(Int64Ty, ArgI64s.size());
  Value *ArgArray = Builder.CreateAlloca(ArgArrayTy, nullptr, "arg_array_i64");
  InsertedInstrs.insert(ArgArray);

  for (size_t i = 0; i < ArgI64s.size(); ++i) {
    Value *GEP = Builder.CreateConstInBoundsGEP2_32(ArgArrayTy, ArgArray, 0, i);
    InsertedInstrs.insert(GEP);
    InsertedInstrs.insert(Builder.CreateStore(ArgI64s[i], GEP));
  }

  // Передаём как i64*
  Value *ArgArrayPtr = Builder.CreateBitCast(ArgArray, Int64PtrTy);
  InsertedInstrs.insert(ArgArrayPtr);

  // Вызов: trace_called(func_id, func_name, arg_array, num_args)
  InsertedInstrs.insert(Builder.CreateCall(
      TraceCallFn, {FuncId, ArgArrayPtr, Builder.getInt64(ArgI64s.size())}));
}

// Инструментация тела функции: запись вызова и возврата
void TraceInstrumentationPass::instrumentFunction(Function &F, Module &M) {
  if (F.empty() || F.isDeclaration() || isFuncLogger(F.getName()))
    return;

  LLVMContext &Ctx = M.getContext();
  IRBuilder<> Builder(Ctx);
  Value *FuncId = Builder.getInt64(getFunctionId(F));

  for (auto &BB : F) {
    for (auto &I : BB) {
      // Инструментация вызовов внешних функций
      if (auto *Call = dyn_cast<CallInst>(&I)) {
        for (Value *Arg : Call->args()) {
          if (auto *Ptr = dyn_cast<PointerType>(Arg->getType())) {
            addMemoryTrace(Builder, Builder.getInt64(0), Arg, Call, MEM_UPD);
          }
        }
        instrumentCall(Builder, Call);
      }
      // Обработка load инструкций
      if (auto *Load = dyn_cast<LoadInst>(&I)) {
        addMemoryTrace(Builder, Load, Load->getOperand(0), Load, MEM_LOAD);
      }
      // Обработка store инструкций
      if (auto *Store = dyn_cast<StoreInst>(&I)) {
        addMemoryTrace(Builder, Store->getOperand(0), Store->getOperand(1),
                       Store, MEM_STORE);
      }
      // Обработка ret инструкций
      if (auto *RetInst = dyn_cast<ReturnInst>(&I)) {
        Builder.SetInsertPoint(RetInst);
        Value *RetValue = RetInst->getReturnValue();
        Value *RetI64 = RetValue ? valueToI64(Builder, RetValue)
                                 : ConstantInt::get(Ctx, APInt(64, 0));
        Builder.CreateCall(TraceReturnFn, {FuncId, RetI64});
      }
      // Обработка gep инструкций
      if (auto *Gep = dyn_cast<GetElementPtrInst>(&I)) {
        addGepTrace(Builder, Gep);
      }
    }
  }

  instrumentFuncStart(Builder, F);

  outs() << "[VERIFICATION] " << F.getName() << '\n';
  bool verif = verifyFunction(F, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
}

void TraceInstrumentationPass::dumpFuncIdMap() {
  std::ofstream funcTrace("app.func.trace");
  for (auto &[name, funcId] : FuncIdMap) {
    funcTrace << name << " " << funcId << "\n";
  }
  funcTrace.close();
}

PreservedAnalyses TraceInstrumentationPass::run(Module &M,
                                                ModuleAnalysisManager &MAM) {
  initTracingFunctions(M);

  for (Function &F : M) {
    instrumentFunction(F, M);
  }

  dumpFuncIdMap();

  // Мы изменяем IR, но не ломаем анализ — пересчитаем всё
  return PreservedAnalyses::none();
}

// Регистрация через PassPlugin (LLVM 14+)
PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([=](ModulePassManager &MPM, auto) {
      MPM.addPass(TraceInstrumentationPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
