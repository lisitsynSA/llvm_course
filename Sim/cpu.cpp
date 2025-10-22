#include "include/cpu.h"
#include <iostream>
#include <sstream>

CPU *CPU::C;

bool CPU::Execute(Binary &Bin, std::string &ErrorMsg) {
  PC = 0;
  Run = 1;
  setCPU(this);
  simInit();
  while (Run) {
    Instr I = Bin.Instrs[PC];
    // cout << dumpStatus(Bin);
    NextPC = PC + 1;
    switch (I.Op) {
    default:
      ErrorMsg = std::string("Wrong Opcode: " + std::to_string(Bin.Instrs[PC].Op));
      return true;
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  case (Opcode_):                                                              \
    do_##Name_(I.R1, I.R2, I.R3Imm);                                           \
    break;
#include "include/ISA.h"
#undef ISA_
    }
    PC = NextPC;
  }
  simExit();
  return false;
}

std::string CPU::dumpStatus(Binary &Bin) {
  std::stringstream Stream;
  for (uint32_t i = 0; i < RegSize; i++) {
    Stream << " x" << i << ":" << (int32_t)RegFile[i] << "(" << std::hex
           << RegFile[i] << ")" << std::dec;
  }
  Stream << " PC:" << PC << '\n';
  Instr I = Bin.Instrs[PC];
  std::map<uint32_t, std::string> &PC2BBName = Bin.PC2BBName;
  switch (I.Op) {
  default:
    Stream << "\nWrong Opcode: " << I.Op << '\n';
    break;
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  case (Opcode_):                                                              \
    Stream << "  " << #Name_;                                                  \
    WriteArgs_;                                                                \
    Stream << '\n';                                                            \
    break;
#include "include/ISA.h"
#undef ISA_
  }
  return Stream.str();
}
