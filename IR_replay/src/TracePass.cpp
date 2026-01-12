// TraceInstrumentationPass.cpp
// LLVM Pass для инструментации модуля с целью сбора runtime IR трассы

// #include "llvm/IR/CallSite.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <fstream>

using namespace llvm;

#define DEBUG_TYPE "trace-instrumentation"

namespace {

struct TraceInstrumentationPass
    : public PassInfoMixin<TraceInstrumentationPass> {
  // Указатели на часто используемые типы
  Type *VoidTy;
  IntegerType *Int64Ty;
  PointerType *Int64PtrTy;
  PointerType *Int8PtrTy;
  FunctionType *TraceCallFnTy;
  FunctionType *TraceReturnFnTy;
  FunctionType *TraceExternalCallFnTy;
  FunctionType *TraceMemFnTy;

  // Указатели на вставляемые функции трассировки
  FunctionCallee TraceCallFn;
  FunctionCallee TraceReturnFn;
  FunctionCallee TraceExternalCallFn;
  FunctionCallee TraceMemFn;
  std::unordered_map<std::string, uint64_t> FuncIdMap;

  bool isFuncLogger(StringRef name) {
    return name == "trace_called" || name == "trace_external_call" ||
           name == "trace_return" || name == "trace_memory";
  }

  // Инициализация типов и функций трассировки
  void initTracingFunctions(Module &M) {
    LLVMContext &Ctx = M.getContext();

    VoidTy = Type::getVoidTy(Ctx);
    Int64Ty = Type::getInt64Ty(Ctx);
    // Int64PtrTy = Int64Ty->getPointerTo();
    Int64PtrTy = PointerType::get(Int64Ty, 0);
    // Int8PtrTy = Type::getInt8Ty(Ctx)->getPointerTo();
    Int8PtrTy = PointerType::get(Type::getInt8Ty(Ctx), 0);

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
    // i64 size, i64 value)
    std::vector<Type *> MemArgs = {Int64Ty, Int64Ty, Int64Ty, Int64Ty, Int64Ty};
    TraceMemFnTy = FunctionType::get(VoidTy, MemArgs, false);
    TraceMemFn = M.getOrInsertFunction("trace_memory", TraceMemFnTy);
  }

  // Генерация уникального ID для функции
  uint64_t getFunctionId(const Function &F) {
    const auto &name = F.getName().str();
    auto search = FuncIdMap.find(name);
    if (search == FuncIdMap.end()) {
      FuncIdMap[name] = static_cast<uint64_t>(std::hash<std::string>{}(name));
      return FuncIdMap[name];
    }
    return search->second;
  }

  Value *valueToI64(IRBuilder<> &Builder, Value *V) {
    LLVMContext &Ctx = Builder.getContext();
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
      Value *Bits = Builder.CreateBitCast(V, Type::getInt64Ty(Ctx));
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

  void instrumentCall(IRBuilder<> &Builder, CallInst *Call,
                      BasicBlock &EntryBB) {
    Value *Callee = Call->getCalledOperand();
    Function *CalleeFunc = Call->getCalledFunction();

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
    for (size_t i = 0; i < ExtArgI64s.size(); ++i) {
      Value *GEP =
          Builder.CreateConstInBoundsGEP2_32(ExtArrayTy, ExtArray, 0, i);
      Builder.CreateStore(ExtArgI64s[i], GEP);
    }
    Value *ExtArrayPtr = Builder.CreateBitCast(ExtArray, Int64PtrTy);

    // Результат вызова
    Value *ExtRetValue = Call->getType()->isVoidTy()
                             ? Builder.getInt64(0)
                             : valueToI64(Builder, Call);

    // Временно сохраняем результат вызова, если он используется
    // Мы не можем просто заменить CallInst — нужно сохранить значение
    // Поэтому создаём временный alloca, если нужно
    AllocaInst *RetAlloca = nullptr;
    if (!Call->use_empty() && !Call->getType()->isVoidTy()) {
      RetAlloca = new AllocaInst(Call->getType(), 0, "ret_alloca",
                                 //&EntryBB.front());
                                 EntryBB.begin());
      // Builder.SetInsertPoint(Call);
      Builder.CreateStore(Call, RetAlloca);
    }

    // Вставляем вызов трассировки ДО вызова
    Builder.CreateCall(TraceExternalCallFn,
                       {ExtFuncId, ExtArrayPtr,
                        Builder.getInt64(ExtArgI64s.size()), ExtRetValue});

    // Если был alloca — загружаем значение обратно
    /*if (RetAlloca) {
      Builder.SetInsertPoint(Call->getNextNode());
      Value *Reloaded =
          Builder.CreateLoad(RetAlloca->getAllocatedType(), RetAlloca);
      Call->replaceAllUsesWith(Reloaded);
    }*/

    // Удаляем оригинальный CallInst и заменяем на биткаст null (если
    // используется) Это опасно Мы не должны удалять CallInst, если он
    // используется. Вместо этого — оставляем вызов, но добавляем
    // трассировку ДО него. Мы не удаляем вызов Только добавляем
    // логирование. Таким образом, поведение остаётся тем же.
  }

  void addMemoryTrace(IRBuilder<> &Builder, Value *V, Instruction *I) {
    LLVMContext &Ctx = Builder.getContext();
    Value *ExtFuncId = Builder.getInt64(getFunctionId(*I->getParent()->getParent()));
    Builder.SetInsertPoint(I);

    // Получаем адрес и размер
    Value *Addr = valueToI64(Builder, V);
    Value *Size = Builder.getInt64(V->getType()->getScalarSizeInBits());
    Value *AsI64 = valueToI64(Builder, V);
    static int id = 0;
    Value *MemopId = Builder.getInt64(id++);

    // void @trace_memory(i64 func_id, i64 memop_id, i64 addr,
    // i64 size, i64 value)
    Builder.CreateCall(
        TraceMemFn, {ExtFuncId, MemopId, Addr, Size, AsI64});
  }

  // Инструментация тела функции: запись вызова и возврата
  void instrumentFunction(Function &F, Module &M) {
    if (F.empty() || F.isDeclaration() || isFuncLogger(F.getName()))
      return;

    LLVMContext &Ctx = M.getContext();
    IRBuilder<> Builder(Ctx);

    // В начало первой инструкции — вставляем trace_called
    BasicBlock &EntryBB = F.getEntryBlock();
    Builder.SetInsertPoint(&EntryBB, EntryBB.begin());

    Value *FuncId = Builder.getInt64(getFunctionId(F));

    // Собираем аргументы как i64
    std::vector<Value *> ArgI64s;
    for (auto &Arg : F.args()) {
      Value *AsI64 = valueToI64(Builder, &Arg);
      ArgI64s.push_back(AsI64);
    }

    // Создаём массив i64 на стеке
    ArrayType *ArgArrayTy = ArrayType::get(Int64Ty, ArgI64s.size());
    Value *ArgArray =
        Builder.CreateAlloca(ArgArrayTy, nullptr, "arg_array_i64");

    for (size_t i = 0; i < ArgI64s.size(); ++i) {
      Value *GEP =
          Builder.CreateConstInBoundsGEP2_32(ArgArrayTy, ArgArray, 0, i);
      Builder.CreateStore(ArgI64s[i], GEP);
    }

    // Передаём как i64*
    Value *ArgArrayPtr = Builder.CreateBitCast(ArgArray, Int64PtrTy);

    // Вызов: trace_called(func_id, func_name, arg_array, num_args)
    Builder.CreateCall(TraceCallFn,
                       {FuncId, ArgArrayPtr, Builder.getInt64(ArgI64s.size())});
    // Для возврата: обернуть все ret инструкции
    for (auto &BB : F) {
      if (auto *RetInst = dyn_cast<ReturnInst>(BB.getTerminator())) {
        Builder.SetInsertPoint(RetInst);
        Value *RetValue = RetInst->getReturnValue();
        Value *RetI64 = RetValue ? valueToI64(Builder, RetValue)
                                 : ConstantInt::get(Ctx, APInt(64, 0));

        Builder.CreateCall(TraceReturnFn, {FuncId, RetI64});
      }
    }

    // Инструментация вызовов внешних функций
    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *Call = dyn_cast<CallInst>(&I)) {
          instrumentCall(Builder, Call, EntryBB);
          for (Value *Arg : Call->args()) {
            if (auto *Ptr = dyn_cast<PointerType>(Arg->getType())) {
              addMemoryTrace(Builder, Arg, Call);
            }
          }
        }
        // Обработка load инструкций
        if (auto *Load = dyn_cast<LoadInst>(&I)) {
          addMemoryTrace(Builder, Load->getOperand(0), Load);
        }
        // Обработка store инструкций
        if (auto *Store = dyn_cast<StoreInst>(&I)) {
          addMemoryTrace(Builder, Store->getOperand(1), Store);
        }
      }
    }

    outs() << "[VERIFICATION] " << F.getName() << '\n';
    bool verif = verifyFunction(F, &outs());
    outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
  }

  void dumpFuncIdMap() {
    std::ofstream funcTrace("app.func.trace");
    for (auto &[name, id] : FuncIdMap) {
      funcTrace << name << " " << id << "\n";
    }
    funcTrace.close();
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    initTracingFunctions(M);

    for (Function &F : M) {
      instrumentFunction(F, M);
    }

    dumpFuncIdMap();

    // Мы изменяем IR, но не ломаем анализ — пересчитаем всё
    return PreservedAnalyses::none();
  }
};

} // namespace

// Регистрация через PassPlugin (LLVM 14+)
PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([=](ModulePassManager &MPM, auto) {
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
