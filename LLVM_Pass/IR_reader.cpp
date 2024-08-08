#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main(int argc, char **argv) {
  if (argc < 2) {
    errs() << "Expected an argument - IR file name\n";
    exit(1);
  }

  LLVMContext Context;
  SMDiagnostic Err;
  std::unique_ptr<Module> Mod = parseIRFile(argv[1], Err, Context);

  if (!Mod) {
    Err.print(argv[0], errs());
    return 1;
  }
  Mod->print(outs(), nullptr);
  return 0;
}