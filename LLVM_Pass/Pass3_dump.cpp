#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << "\n";
    for (auto &G : M.globals()) {
      outs() << "[Global Variable] " << G.getName() << "\n";
      G.print(outs());
      outs() << "\n";
    }
    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      F.print(outs());

      for (auto &B : F) {
        outs() << "\n#[Basic block]";
        B.print(outs());

        for (auto &I : B) {
          outs() << "##[Instruction]\n";
          I.print(outs(), true);
          outs() << "\n";
        }
      }
      outs() << "\n";
    }
    outs() << "\n";
    return PreservedAnalyses::all();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
      return true;
    });
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto) {
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
