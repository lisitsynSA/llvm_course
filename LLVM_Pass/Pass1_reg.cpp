#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    // clang hello.c -fpass-plugin=./libPass.so
    PB.registerPipelineStartEPCallback([](ModulePassManager &MPM, auto) {
      outs() << "Add pass to ModulePassManager in "
                "registerPipelineStartEPCallback\n";
      return true;
    });
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto) {
      outs() << "Add pass to ModulePassManager in "
                "registerOptimizerLastEPCallback\n";
      return true;
    });
    // opt hello.ll -load-pass-plugin ./libPass.so -passes myFuncPass -o a.out
    PB.registerPipelineParsingCallback(
        [](StringRef name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) -> bool {
          if (name == "myFuncPass") {
            outs() << "Add pass to FunctionPassManager from "
                      "registerPipelineParsingCallback\n";
            return true;
          }
          return false;
        });
    // opt hello.ll -load-pass-plugin ./libPass.so -passes myModPass -o a.out
    PB.registerPipelineParsingCallback(
        [](StringRef name, ModulePassManager &MPM,
           ArrayRef<PassBuilder::PipelineElement>) -> bool {
          if (name == "myModPass") {
            outs() << "Add pass to ModulePassManager from "
                      "registerPipelineParsingCallback\n";
            return true;
          }
          return false;
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
