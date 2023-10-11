#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
  struct MyPass : public FunctionPass {
    static char ID;
    MyPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      outs() << "\nIn a function called " << F.getName() << "!\n";
      F.print(outs());
      outs() << "\nFunction Uses: \n";
      for (auto &U : F.uses()) {
        User *user = U.getUser();
        user->print(outs(), true);
        outs() << "\n";
      }

      for (auto &B : F) {
        outs() << "\nBasic block:";
        B.print(outs());
        outs() << "BasicBlock Uses: \n";
        for (auto &U : B.uses()) {
          User *user = U.getUser();
          user->print(outs(), true);
          outs() << "\n";
        }

        for (auto &I : B) {
          outs() << "\nInstruction: \n";
          I.print(outs(), true);
          outs() << "\nUses: \n";
          for (auto &U : I.uses()) {
            User *user = U.getUser();
            user->print(outs(), true);
            outs() << "\n";
          }
          outs() << "Use: \n";
          for (auto &U : I.operands()) {
            Value *use = U.get();
            use->print(outs(), true);
            outs() << "\n";
          }
        }
      }

      return false;
    }
  };
}

char MyPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerMyPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new MyPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerMyPass);
