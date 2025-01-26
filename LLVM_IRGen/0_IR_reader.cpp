#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
using namespace llvm;

int main(int argc, char **argv) {
  if (argc < 2) {
    errs() << "Expected at least one argument - IR file name\n";
    exit(1);
  }

  LLVMContext Context;
  SMDiagnostic Err;
  std::unique_ptr<Module> Mod = parseIRFile(argv[1], Err, Context);

  if (!Mod) {
    Err.print(argv[0], errs());
    return 1;
  }
  for (auto &G : Mod->globals()) {
    outs() << "[Global Variable] " << G.getName() << '\n';
  }
  for (auto &F : *Mod) {
    outs() << "[Function] " << F.getName() << '\n';
  }
  if (argc == 3) {
    std::error_code EC;
    raw_fd_ostream OutputFile(argv[2], EC);
    if (!EC) {
      Mod->print(OutputFile, nullptr);
    }
  }
  return 0;
}
