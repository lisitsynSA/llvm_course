#include "../include/TraceReader.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main(int argc, char **argv) {
  if (argc != 2) {
    errs() << "Usage: " << argv[0] << " <trace_file>\n";
    return 1;
  }
  TraceReader Reader;

  if (!Reader.parse(argv[1]))
    return 1;
  return 0;
}
