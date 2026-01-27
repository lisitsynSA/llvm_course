#include "../include/ModuleInfo.h"
#include "../include/ModuleInstrument.h"
#include "../include/ReplayGen.h"
#include "../include/TraceInfo.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

enum ToolMode { Instrument, TraceDump, ReplayGeneration };

cl::opt<ToolMode> Mode(cl::desc("Choose tool mode:"), cl::Required,
                       cl::values(clEnumValN(Instrument, "instrument",
                                             "Instrument input LLVM IR file"),
                                  clEnumValN(TraceDump, "trace-dump",
                                             "Dump application trace"),
                                  clEnumValN(ReplayGeneration, "replay-gen",
                                             "Generate replay LLVM IR file")));

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
      M.InstrumentModule();
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
  case ReplayGeneration:
    if (TraceName.empty() || InputIR.empty() || OutputIR.empty()) {
      errs() << "[UNITOOL] Trace, InputIR and OutputIR are required for Replay "
                "Generation.\n";
      return 1;
    } else {
      outs() << "[UNITOOL] Start Replay Generation Mode\n";
      TraceInfo Trace(TraceName);
      ReplayGen M(InputIR, Ctx);
      M.replayGeneration(Trace);
      M.dumpModule(OutputIR);
    }
    break;
  }
  return 0;
}
