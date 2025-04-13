#ifndef CPU_H
#define CPU_H
#include "sim.h"
#include "bin.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>
#include <string>

struct CPU {
  static constexpr uint32_t RegSize = 16;
  uint32_t RegFile[RegSize] = {};
  uint32_t PC;
  uint32_t NextPC;
  uint32_t Run;
  bool DumpInstrs = false;

  bool Execute(Binary &Bin, std::string &ErrorMsg);
  std::string dumpStatus(Binary &Bin);

  static CPU *C;
  static void setCPU(CPU *Cpu) { C = Cpu; }
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  static void do_##_Name(uint32_t R1, uint32_t R2, uint32_t R3Imm) {           \
    if (C->DumpInstrs)                                                         \
      llvm::outs() << #_Name "\n";                                             \
    _Execute;                                                                  \
  }
#include "ISA.h"
#undef _ISA
};
#endif // CPU_H
