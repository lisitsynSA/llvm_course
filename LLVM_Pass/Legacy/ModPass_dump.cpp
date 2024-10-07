#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
struct MyPass : public ModulePass {
  static char ID;
  MyPass() : ModulePass(ID) {}

  virtual bool runOnModule(Module &M) {
    // M.print(outs(), nullptr);

    for (auto &G : M.globals()) {
      // outs() << "Global Variable: ";
      G.print(outs());
      outs() << "\n";
    }
    for (auto &F : M) {
      // outs() << "Function: ";
      F.print(outs());
      outs() << "\n";
      /*for (auto &B : F) {
        outs() << "Basic block:\n";
        B.print(outs());

        for (auto &I : B) {
          outs() << "Instruction: \n";
          I.print(outs(), true);
          outs() << "\n";
        }
      }*/
    }
    return false;
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
    RegisterMyPass(PassManagerBuilder::EP_ModuleOptimizerEarly, registerMyPass);
