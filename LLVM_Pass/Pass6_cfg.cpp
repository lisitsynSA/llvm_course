#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {

  bool isFuncLogger(StringRef name) {
    return name == "binOptLogger" || name == "callLogger" ||
           name == "funcStartLogger" || name == "funcEndLogger";
  }
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << "\n";
    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      for (auto &B : F) {
        for (auto &I : B) {
          // Dump Instructions
          outs() << "Instruction: " << (uint64_t)(&I) << "\n";
          I.print(outs(), true);
          outs() << "\n";
        }
        outs() << "\n";
      }

      // Prepare builder for IR modification
      LLVMContext &Ctx = F.getContext();
      IRBuilder<> builder(Ctx);
      Type *retType = Type::getVoidTy(Ctx);

      // Prepare funcStartLogger function
      ArrayRef<Type *> funcStartParamTypes = {
          builder.getInt8Ty()->getPointerTo()};
      FunctionType *funcStartLogFuncType =
          FunctionType::get(retType, funcStartParamTypes, false);
      FunctionCallee funcStartLogFunc =
          M.getOrInsertFunction("funcStartLogger", funcStartLogFuncType);

      // Insert a call to funcStartLogger function in the function begin
      BasicBlock &entryBB = F.getEntryBlock();
      builder.SetInsertPoint(&entryBB.front());
      Value *funcName = builder.CreateGlobalStringPtr(F.getName());
      Value *args[] = {funcName};
      builder.CreateCall(funcStartLogFunc, args);

      // Prepare callLogger function
      ArrayRef<Type *> callParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                         builder.getInt8Ty()->getPointerTo(),
                                         Type::getInt64Ty(Ctx)};
      FunctionType *callLogFuncType =
          FunctionType::get(retType, callParamTypes, false);
      FunctionCallee callLogFunc =
          M.getOrInsertFunction("callLogger", callLogFuncType);

      // Prepare funcEndLogger function
      ArrayRef<Type *> funcEndParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                            Type::getInt64Ty(Ctx)};
      FunctionType *funcEndLogFuncType =
          FunctionType::get(retType, funcEndParamTypes, false);
      FunctionCallee funcEndLogFunc =
          M.getOrInsertFunction("funcEndLogger", funcEndLogFuncType);

      // Prepare binOptLogger function
      ArrayRef<Type *> binOptParamTypes = {Type::getInt32Ty(Ctx),
                                           Type::getInt32Ty(Ctx),
                                           Type::getInt32Ty(Ctx),
                                           builder.getInt8Ty()->getPointerTo(),
                                           builder.getInt8Ty()->getPointerTo(),
                                           Type::getInt64Ty(Ctx)};
      FunctionType *binOptLogFuncType =
          FunctionType::get(retType, binOptParamTypes, false);
      FunctionCallee binOptLogFunc =
          M.getOrInsertFunction("binOptLogger", binOptLogFuncType);

      // Insert loggers for call, binOpt and ret instructions
      for (auto &B : F) {
        for (auto &I : B) {
          Value *valueAddr =
              ConstantInt::get(builder.getInt64Ty(), (int64_t)(&I));
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
            }
          }
          if (auto *ret = dyn_cast<ReturnInst>(&I)) {
            // Insert before ret
            builder.SetInsertPoint(ret);

            // Insert a call to funcEndLogFunc function
            Value *funcName = builder.CreateGlobalStringPtr(F.getName());
            Value *args[] = {funcName, valueAddr};
            builder.CreateCall(funcEndLogFunc, args);
          }
          if (auto *op = dyn_cast<BinaryOperator>(&I)) {
            // Insert after op
            builder.SetInsertPoint(op);
            builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

            // Insert a call to binOptLogFunc function
            Value *lhs = op->getOperand(0);
            Value *rhs = op->getOperand(1);
            Value *funcName = builder.CreateGlobalStringPtr(F.getName());
            Value *opName = builder.CreateGlobalStringPtr(op->getOpcodeName());
            Value *args[] = {op, lhs, rhs, opName, funcName, valueAddr};
            builder.CreateCall(binOptLogFunc, args);
          }
        }
      }
    }
    outs() << "\n";
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([&](ModulePassManager &MPM, auto) {
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
