#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      outs() << "In a function called " << F.getName() << "!\n";

      outs() << "Function body:\n";
      //F.dump(); Out-of-Date: no more dump support in modern llvm unless you enable it at compile time.
      F.print(llvm::outs());

      for (auto &B : F) {
        outs() << "Basic block:\n";
        B.print(llvm::outs());

        for (auto &I : B) {
          outs() << "Instruction: \n";
          I.print(llvm::outs(), true);
          outs() << "\n";
        }
      }

      return false;
    }
  };
}

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
