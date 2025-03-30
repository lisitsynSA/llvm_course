#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << '\n';
    bool changed = false;
    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      if (F.isDeclaration()) {
        continue;
      }

      F.print(outs());
      outs() << '\n';

      for (auto &B : F) {
        for (auto &I : B) {
          if (AllocaInst *Alloca = dyn_cast<AllocaInst>(&I)) {
            outs() << "\nAllocation: (BB " << &B << "):\n";
            Alloca->print(outs(), true);
            outs() << '\n';
            StoreInst *Store = nullptr;
            LoadInst *Load = nullptr;

            for (auto &U : Alloca->uses()) {
              Instruction *UseInst = cast<Instruction>(U.getUser());
              outs() << "\tUsers: ";
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

                Store->eraseFromParent();
                for (auto &U : Load->uses()) {
                  Instruction *UseInst = cast<Instruction>(U.getUser());
                  outs() << "\t Load Users: ";
                  UseInst->print(outs(), true);
                  outs() << '\n';
                  for (int i = 0; i < UseInst->getNumOperands(); i++) {
                    if (UseInst->getOperand(i) == Load) {
                      UseInst->setOperand(i, Val);
                    }
                  }
                  outs() << "\t Fixed Load Users: ";
                  UseInst->print(outs(), true);
                  outs() << '\n';
                }
                Load->eraseFromParent();
              }
            }
          }
        }
      }
      outs() << '\n';
      bool verif = verifyFunction(F, &outs());
      outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");
    }
    outs() << '\n';
    return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
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
