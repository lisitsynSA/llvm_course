#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <list>
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << "\n";
    bool changed = false;
    std::list<Instruction *> RemoveInstrs;
    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      if (F.isDeclaration()) {
        continue;
      }
      F.print(outs());

      for (auto &B : F) {
        for (auto &I : B) {
          if (auto *op = dyn_cast<BinaryOperator>(&I)) {
            outs() << "Modified instruction:\n";
            I.print(outs(), true);
            outs() << "\n";
            // Insert at the point where the instruction `op` appears.
            IRBuilder<> builder(op);

            // Make a sub with the same operands as `op`.
            Value *lhs = op->getOperand(0);
            Value *rhs = op->getOperand(1);
            Value *sub = builder.CreateSub(lhs, rhs);

            // Everywhere the old instruction was used as an operand, use our
            // new sub instruction instead.
            for (auto &U : op->uses()) {
              User *user = U.getUser(); // A User is anything with operands.
              user->setOperand(U.getOperandNo(), sub);
            }
            // 2 variants for removing (only RemoveInstrs works):
            // I.eraseFromParent();
            // RemoveInstrs.push_back(&I);
            changed = true;
            outs() << "\n";
            bool verif = verifyFunction(F, &outs());
            outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
          }
        }
      }
    }
    for (auto I : RemoveInstrs) {
      I->eraseFromParent();
    }
    return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([=](ModulePassManager &MPM, auto) {
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
