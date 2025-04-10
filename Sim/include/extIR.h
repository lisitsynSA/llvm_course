#ifndef EXTIR_H
#define EXTIR_H
#include "bin.h"
#include "cpu.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

struct ExtIR {
  llvm::LLVMContext context;
  llvm::Module *module;
  llvm::Function *mainFunc;
  llvm::GlobalVariable *regFile;

  void buildIR(Binary &Bin);
  void dumpIR();
  bool verifyIR();
  void executeIR(CPU &Cpu);
};

#endif // EXTIR_H