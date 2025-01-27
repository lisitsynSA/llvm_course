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
struct MyPass : public FunctionPass {
  static char ID;
  MyPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    outs() << "\nIn a function called " << F.getName() << "!\n";

    // Prepare builder for IR modification
    LLVMContext &Ctx = F.getContext();
    IRBuilder<> builder(Ctx);
    bool changed = false;

    for (auto &B : F) {
      for (auto &I : B) {
        if (auto *op = dyn_cast<BinaryOperator>(&I)) {
          outs() << "Modified instruction:\n";
          I.print(outs(), true);
          outs() << '\n';
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

          changed = true;
        }
      }
    }
    return changed;
  }
};
} // namespace

char MyPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerMyPass(const PassManagerBuilder &,
                           legacy::PassManagerBase &PM) {
  PM.add(new MyPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerMyPass);
// RegisterMyPass(PassManagerBuilder::EP_OptimizerLast, registerMyPass); // only
// with -O2
