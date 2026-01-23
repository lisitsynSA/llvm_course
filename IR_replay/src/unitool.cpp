#include "../include/ModuleInfo.h"
#include "../include/ModuleInstrument.h"
#include "../include/TraceInfo.h"

int main(int argc, char **argv) {
  llvm::LLVMContext Ctx;
  ModuleInstrument M(argv[1], Ctx);
  M.dumpModule(argv[2]);
  return 0;
}
