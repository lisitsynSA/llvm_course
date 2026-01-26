#include "../include/ModuleInfo.h"
#include "../include/ModuleInstrument.h"
#include "../include/TraceInfo.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

enum ToolMode { Instrument, TraceDump, ReplayGen, ExtReplayGen };

cl::opt<ToolMode> Mode(
    cl::desc("Choose tool mode:"), cl::Required,
    cl::values(
        clEnumValN(Instrument, "instrument", "Instrument input LLVM IR file"),
        clEnumValN(TraceDump, "trace-dump", "Dump application trace"),
        clEnumValN(ReplayGen, "replay-gen", "Generate replay LLVM IR file"),
        clEnumValN(ExtReplayGen, "ext-replay-gen",
                   "Generate extended replay LLVM IR file")));

cl::opt<std::string> InputIR("i", cl::desc("Input filename for LLVM IR"),
                             cl::value_desc("input.ll"));

cl::opt<std::string> OutputIR("o", cl::desc("Output filename for LLVM IR"),
                              cl::value_desc("output.ll"));

cl::opt<std::string> TraceName("t", cl::desc("Trace filename"),
                               cl::value_desc("app.trace"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv);
  LLVMContext Ctx;
  switch (Mode) {
  case Instrument:
    if (OutputIR.empty() || InputIR.empty()) {
      errs() << "[UNITOOL] OutputIR and InputIR are required for "
                "Instrumentation.\n";
      return 1;
    } else {
      outs() << "[UNITOOL] Start Instrumentation Mode\n";
      ModuleInstrument M(InputIR, Ctx);
      M.dumpModule(OutputIR);
    }
    break;
  case TraceDump:
    if (TraceName.empty()) {
      errs() << "[UNITOOL] Trace is required for Trace Dump.\n";
      return 1;
    } else {
      outs() << "[UNITOOL] Start Trace Dump Mode\n";
      TraceInfo Trace(TraceName);
      if (InputIR.empty()) {
        Trace.dump();
      } else {
        ModuleInfo M(InputIR, Ctx);
        Trace.dump(&M);
      }
    }
    break;
  case ReplayGen:
    if (TraceName.empty() || InputIR.empty()) {
      errs() << "[UNITOOL] Trace and InputIR are required for Replay "
                "Generation.\n";
      return 1;
    } else {
      outs() << "[UNITOOL] Start Replay Generation Mode\n";
      TraceInfo Trace(TraceName);
    }
    break;
  case ExtReplayGen:
    if (TraceName.empty() || InputIR.empty()) {
      errs() << "[UNITOOL] Trace and InputIR are required for Extended Replay "
                "Generation.\n";
      return 1;
    } else {
      outs() << "[UNITOOL] Start Extended Replay Generation Mode\n";
      TraceInfo Trace(TraceName);
    }
    break;
  }
  return 0;
}
