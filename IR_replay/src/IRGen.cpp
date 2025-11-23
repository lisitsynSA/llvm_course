// Генератор LLVM IR с воспроизведением последовательности вызовов через main()

#include "../include/TraceReplGen.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

int main(int argc, char **argv) {
  if (argc != 4) {
    errs() << "Usage: " << argv[0] << " <input.ll> <trace_file> <output.ll>\n";
    return 1;
  }

  LLVMContext Context;
  TraceReader Reader;
  TraceReplayGenerator Generator(Context);

  if (!Generator.loadOriginalModule(argv[1]))
    return 1;
  if (!Reader.parse(argv[2]))
    return 1;

  Generator.populateMocks(Reader.getCallSequence());
  if (!Generator.generate())
    return 1;

  Generator.saveToFile(argv[3]);
  outs() << "Replay module with main() saved to " << argv[3] << '\n';
  return 0;
}
