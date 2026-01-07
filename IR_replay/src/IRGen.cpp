// Генератор LLVM IR с воспроизведением последовательности вызовов через main()

#include "../include/TraceReplGen.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

int main(int argc, char **argv) {
  if (argc != 5) {
    errs() << "Usage: " << argv[0]
           << " <input.ll> <trace_func_file> <trace_file> <output.ll>\n";
    return 1;
  }

  LLVMContext Context;
  TraceReader Reader;
  TraceReplayGenerator Generator(Context);

  if (!Generator.loadOriginalModule(argv[1]))
    return 1;
  if (!Reader.loadFuncMap(argv[2]))
    return 1;
  if (!Reader.parse(argv[3]))
    return 1;

  Generator.populateMocks(Reader.getCallSequence(), Reader.getFuncMap());
  if (!Generator.generate())
    return 1;

  Generator.saveToFile(argv[4]);
  outs() << "Replay module with main() saved to " << argv[4] << '\n';
  return 0;
}
