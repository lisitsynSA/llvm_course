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

  virtual bool runOnFunction(Function &F) {
    outs() << "In a function " << F.getName() << "\n";
    F.print(outs());
    outs() << "\n";

    bool changed = false;
    for (auto &B : F) {
      for (auto &I : B) {
        if (AllocaInst *Alloca = dyn_cast<AllocaInst>(&I)) {
          outs() << "\nAllocation: (BB " << &B << "):\n";
          Alloca->print(outs(), true);
          outs() << "\n";
          StoreInst *Store = nullptr;
          LoadInst *Load = nullptr;

          for (auto &U : Alloca->uses()) {
            Instruction *UseInst = cast<Instruction>(U.getUser());
            outs() << "\tUse: ";
            UseInst->print(outs(), true);

            if (StoreInst *S = dyn_cast<StoreInst>(UseInst)) {
              if (Store == nullptr) {
                Store = S;
                outs() << " == STORE\n";
              } else {
                outs() << " == EXTRA STORE\n";
                Store = nullptr;
                break;
              }
            } else if (LoadInst *L = dyn_cast<LoadInst>(UseInst)) {
              if (Load == nullptr) {
                Load = L;
                outs() << " == LOAD\n";
              } else {
                Load = nullptr;
                outs() << " == EXTRA LOAD\n";
                break;
              }
            } else {
              Load = nullptr;
              outs() << " == EXTRA INSTR\n";
              break;
            }
          }
          if (Load != nullptr && Store != nullptr) {
            BasicBlock *LoadBB = Load->getParent();
            BasicBlock *StoreBB = Store->getParent();
            if (LoadBB == StoreBB) {
              outs() << "[PASS] Store and load in the same BB\n";
              continue;
            }
            outs() << "[PASS] Allocation is candidate\n";
            changed = true;
            Value *Val = Store->getOperand(0);
            Instruction *ValInst = dyn_cast<Instruction>(Val);

            if (ValInst) {
              if (ValInst->isEHPad() || ValInst->mayThrow()) {
                continue;
              }
              ValInst->moveBefore(&*LoadBB->getFirstInsertionPt());

              Store->removeFromParent();
              for (auto &U : Load->uses()) {
                Instruction *UseInst = cast<Instruction>(U.getUser());
                outs() << "\t Load Use: ";
                UseInst->print(outs(), true);
                outs() << "\n";
                for (int i = 0; i < UseInst->getNumOperands(); i++) {
                  if (UseInst->getOperand(i) == Load) {
                    UseInst->setOperand(i, Val);
                  }
                }
                outs() << "\t Fixed Load Use: ";
                UseInst->print(outs(), true);
                outs() << "\n";
              }
              Load->removeFromParent();
            }
          }
        }
      }
    }

    return changed;
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
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, // EP_OptimizerLast
                   registerSkeletonPass);
