#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;

namespace {
struct SkeletonPass : public FunctionPass {
  static char ID;
  SkeletonPass() : FunctionPass(ID) {}

  bool isFuncLogger(StringRef name) {
    return name == "binOptLogger" || name == "callLogger" ||
           name == "funcStartLogger" || name == "funcEndLogger";
  }

  virtual bool runOnFunction(Function &F) {
    if (isFuncLogger(F.getName())) {
      return false;
    }
    // Dump Function
    outs() << "In a function called " << F.getName() << "\n";
    F.print(llvm::outs());
    outs() << "\n";

    // Dump function uses
    for (auto &U : F.uses()) {
      User *user = U.getUser();
      outs() << "[DOT] " << (uint64_t)(&F) << " -> " << (uint64_t)user << "\n";
      outs() << "    User:  " << (uint64_t)user;
      user->print(llvm::outs(), true);
      outs() << "\n";
    }

    for (auto &B : F) {
      // Dump BasicBlocks
      // outs() << "Basic block:\n";
      // B.print(llvm::outs());
      // outs() << "\n";
      for (auto &I : B) {
        // Dump Instructions
        outs() << "Instruction: " << (uint64_t)(&I) << "\n";
        I.print(llvm::outs(), true);
        outs() << "\n";
        // Dump instruction uses
        for (auto &U : I.uses()) {
          User *user = U.getUser();
          outs() << "[DOT] " << (uint64_t)(&I) << " -> " << (uint64_t)user
                 << "\n    User:  " << (uint64_t)user;
          user->print(llvm::outs(), true);
          outs() << "\n";
        }
      }
    }

    // Prepare builder for IR modification
    LLVMContext &Ctx = F.getContext();
    IRBuilder<> builder(Ctx);
    Type *retType = Type::getVoidTy(Ctx);

    // Prepare funcStartLogger function
    std::vector<Type *> funcStartParamTypes = {
        builder.getInt8Ty()->getPointerTo(),
        builder.getInt8Ty()->getPointerTo(), Type::getInt32Ty(Ctx)};
    FunctionType *funcStartLogFuncType =
        FunctionType::get(retType, funcStartParamTypes, false);
    FunctionCallee funcStartLogFunc = F.getParent()->getOrInsertFunction(
        "funcStartLogger", funcStartLogFuncType);

    // Insert a call to funcStartLogger function in the function begin
    BasicBlock &entryBB = F.getEntryBlock();
    builder.SetInsertPoint(&entryBB.front());
    Value *funcName = builder.CreateGlobalStringPtr(F.getName());
    Value *args[] = {funcName};
    builder.CreateCall(funcStartLogFunc, args);

    // Prepare binOptLogger function
    std::vector<Type *> binOptParamTypes = {Type::getInt32Ty(Ctx),
                                            Type::getInt32Ty(Ctx),
                                            Type::getInt32Ty(Ctx),
                                            builder.getInt8Ty()->getPointerTo(),
                                            builder.getInt8Ty()->getPointerTo(),
                                            Type::getInt32Ty(Ctx)};
    FunctionType *binOptLogFuncType =
        FunctionType::get(retType, binOptParamTypes, false);
    FunctionCallee binOptLogFunc =
        F.getParent()->getOrInsertFunction("binOptLogger", binOptLogFuncType);

    // Prepare callLogger function
    std::vector<Type *> callParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                          builder.getInt8Ty()->getPointerTo(),
                                          Type::getInt32Ty(Ctx)};
    FunctionType *callLogFuncType =
        FunctionType::get(retType, callParamTypes, false);
    FunctionCallee callLogFunc =
        F.getParent()->getOrInsertFunction("callLogger", callLogFuncType);

    // Prepare funcEndLogger function
    std::vector<Type *> funcEndParamTypes = {
        builder.getInt8Ty()->getPointerTo(), Type::getInt32Ty(Ctx)};
    FunctionType *funcEndLogFuncType =
        FunctionType::get(retType, funcEndParamTypes, false);
    FunctionCallee funcEndLogFunc =
        F.getParent()->getOrInsertFunction("funcEndLogger", funcEndLogFuncType);

    // Insert loggers for call, binOpt and ret instructions
    for (auto &B : F) {
      for (auto &I : B) {
        Value *valueAddr =
            ConstantInt::get(builder.getInt64Ty(), (int64_t)(&I));
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
      }
    }
    return true;
  }
};
} // namespace

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerSkeletonPass);
