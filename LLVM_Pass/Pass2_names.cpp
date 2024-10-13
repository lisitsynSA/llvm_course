#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "\n[Module Pass] Module: " << M.getName() << "\n";
    for (auto &G : M.globals()) {
      outs() << "[Global Variable] " << G.getName() << "\n";
    }
    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << "\n";
    }
    return PreservedAnalyses::all();
  };
};

struct MyFuncPass : public PassInfoMixin<MyFuncPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    outs() << "\n[Function Pass] Module: " << F.getParent()->getName() << "\n";
    outs() << "[Function] " << F.getName() << "\n";
    return PreservedAnalyses::all();
  };
  static bool isRequired() { return true; }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    // clang hello.c -fpass-plugin=./libPass.so -O1 (w/o isRequired)
    PB.registerPipelineStartEPCallback([&](ModulePassManager &MPM, auto) {
      outs() << "Add pass to ModulePassManager in "
                "registerPipelineStartEPCallback\n";
      MPM.addPass(MyModPass{});
      return true;
    });
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      outs() << "Add pass to ModulePassManager in "
                "registerOptimizerLastEPCallback\n";
      MPM.addPass(createModuleToFunctionPassAdaptor(MyFuncPass{}));
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  outs() << "Entry point for a plugin\n";
  return getPassPluginInfo();
}
