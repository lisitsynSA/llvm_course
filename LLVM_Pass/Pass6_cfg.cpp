#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  Type *voidType;
  Type *int8PtrTy;
  Type *int32Ty;
  Type *int64Ty;

  bool isFuncLogger(StringRef name) {
    return name == "binOptLogger" || name == "callLogger" ||
           name == "funcStartLogger" || name == "funcEndLogger" ||
           name == "resIntLogger";
  }

  bool insertFuncStartLog(Module &M, Function &F, IRBuilder<> &builder) {
    // Prepare funcStartLogger function
    ArrayRef<Type *> funcStartParamTypes = {int8PtrTy};
    FunctionType *funcStartLogFuncType =
        FunctionType::get(voidType, funcStartParamTypes, false);
    FunctionCallee funcStartLogFunc =
        M.getOrInsertFunction("funcStartLogger", funcStartLogFuncType);

    // Insert a call to funcStartLogger function in the function begin
    BasicBlock &entryBB = F.getEntryBlock();
    builder.SetInsertPoint(&entryBB.front());
    Value *funcName = builder.CreateGlobalStringPtr(F.getName());
    Value *args[] = {funcName};
    builder.CreateCall(funcStartLogFunc, args);

    return true;
  }

  bool insertCallLog(Module &M, Function &F, IRBuilder<> &builder) {
    // Prepare callLogger function
    ArrayRef<Type *> callParamTypes = {int8PtrTy, int8PtrTy, int64Ty};
    FunctionType *callLogFuncType =
        FunctionType::get(voidType, callParamTypes, false);
    FunctionCallee callLogFunc =
        M.getOrInsertFunction("callLogger", callLogFuncType);

    // Prepare resIntLogger function
    ArrayRef<Type *> resIntParamTypes = {int64Ty, int64Ty};
    FunctionType *resIntLogFuncType =
        FunctionType::get(voidType, resIntParamTypes, false);
    FunctionCallee resIntLogFunc =
        M.getOrInsertFunction("resIntLogger", resIntLogFuncType);

    bool Inserted = false;
    // Insert loggers for call, binOpt and ret instructions
    for (auto &B : F) {
      for (auto &I : B) {
        Value *valueAddr = ConstantInt::get(int64Ty, (int64_t)(&I));
        if (auto *call = dyn_cast<CallInst>(&I)) {
          // Insert before call
          builder.SetInsertPoint(call);

          // Insert a call to callLogger function
          Function *callee = call->getCalledFunction();
          if (callee && !isFuncLogger(callee->getName())) {
            Value *calleeName =
                builder.CreateGlobalStringPtr(callee->getName());
            Value *funcName = builder.CreateGlobalStringPtr(F.getName());
            Value *args[] = {funcName, calleeName, valueAddr};
            builder.CreateCall(callLogFunc, args);
            Inserted = true;

            // Insert result dump
            if (!call->getType()->isVoidTy()) {
              builder.SetInsertPoint(call->getNextNode());
              Value *resArgs[] = {call, valueAddr};
              builder.CreateCall(resIntLogFunc, resArgs);
            }
          }
        }
      }
    }
    return Inserted;
  }

  bool insertFuncEndLog(Module &M, Function &F, IRBuilder<> &builder) {
    // Prepare funcEndLogger function
    ArrayRef<Type *> funcEndParamTypes = {int8PtrTy, int64Ty};
    FunctionType *funcEndLogFuncType =
        FunctionType::get(voidType, funcEndParamTypes, false);
    FunctionCallee funcEndLogFunc =
        M.getOrInsertFunction("funcEndLogger", funcEndLogFuncType);

    bool Inserted = false;
    // Insert loggers for call, binOpt and ret instructions
    for (auto &B : F) {
      for (auto &I : B) {
        Value *valueAddr = ConstantInt::get(int64Ty, (int64_t)(&I));
        if (auto *ret = dyn_cast<ReturnInst>(&I)) {
          // Insert before ret
          builder.SetInsertPoint(ret);

          // Insert a call to funcEndLogFunc function
          Value *funcName = builder.CreateGlobalStringPtr(F.getName());
          Value *args[] = {funcName, valueAddr};
          builder.CreateCall(funcEndLogFunc, args);
          Inserted = true;
        }
      }
    }
    return Inserted;
  }

  bool insertBinOptLog(Module &M, Function &F, IRBuilder<> &builder) {
    // Prepare binOptLogger function
    ArrayRef<Type *> binOptParamTypes = {int32Ty,   int32Ty,   int32Ty,
                                         int8PtrTy, int8PtrTy, int64Ty};
    FunctionType *binOptLogFuncType =
        FunctionType::get(voidType, binOptParamTypes, false);
    FunctionCallee binOptLogFunc =
        M.getOrInsertFunction("binOptLogger", binOptLogFuncType);

    bool Inserted = false;
    // Insert loggers for call, binOpt and ret instructions
    for (auto &B : F) {
      for (auto &I : B) {
        Value *valueAddr = ConstantInt::get(int64Ty, (int64_t)(&I));
        if (auto *op = dyn_cast<BinaryOperator>(&I)) {
          // Insert after op
          builder.SetInsertPoint(op);
          builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
          // builder.SetInsertPoint(op->getNextNode());

          // Insert a call to binOptLogFunc function
          Value *lhs = op->getOperand(0);
          Value *rhs = op->getOperand(1);
          Value *funcName = builder.CreateGlobalStringPtr(F.getName());
          Value *opName = builder.CreateGlobalStringPtr(op->getOpcodeName());
          Value *args[] = {op, lhs, rhs, opName, funcName, valueAddr};
          builder.CreateCall(binOptLogFunc, args);
          Inserted = true;
        }
      }
    }
    return Inserted;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << '\n';

    // Prepare builder for IR modification
    LLVMContext &Ctx = M.getContext();
    IRBuilder<> builder(Ctx);
    voidType = Type::getVoidTy(Ctx);
    int8PtrTy = Type::getInt8Ty(Ctx)->getPointerTo();
    int32Ty = Type::getInt32Ty(Ctx);
    int64Ty = Type::getInt64Ty(Ctx);

    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      if (insertFuncStartLog(M, F, builder)) {
        outs() << "insertFuncStartLog done\n";
      }

      if (insertCallLog(M, F, builder)) {
        outs() << "insertCallLog done\n";
      }
      if (insertFuncEndLog(M, F, builder)) {
        outs() << "insertFuncEndLog done\n";
      }

      if (insertBinOptLog(M, F, builder)) {
        outs() << "insertBinOptLog done\n";
      }

      outs() << '\n';
      bool verif = verifyFunction(F, &outs());
      outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");
    }
    outs() << '\n';
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    // PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto) {
    PB.registerPipelineStartEPCallback([](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
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
