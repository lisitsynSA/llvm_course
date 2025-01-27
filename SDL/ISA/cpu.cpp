#include "include/cpu.h"
#include <sstream>

CPU *CPU::C;

bool CPU::Execute(Binary &Bin, std::string &ErrorMsg) {
  PC = 0;
  Run = 1;
  setCPU(this);
  simInit();
  while (Run) {
    Instr I = Bin.Instrs[PC];
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

std::string CPU::dumpStatus() {
  std::stringstream Stream;
  for (uint32_t i = 0; i < RegSize; i++) {
    Stream << " x" << i << ":" << RegFile[i];
  }
  Stream << " PC:" << PC << '\n';
  return Stream.str();
}
