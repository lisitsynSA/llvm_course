#include "include/cpu.h"
#include <iostream>
#include <sstream>
using namespace std;

CPU *CPU::C;

bool CPU::Execute(Binary &Bin, string &ErrorMsg) {
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
      ErrorMsg = string("Wrong Opcode: " + to_string(Bin.Instrs[PC].Op));
      return true;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    do_##_Name(I.R1, I.R2, I.R3Imm);                                           \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    PC = NextPC;
  }
  simExit();
  return false;
}

string CPU::dumpStatus(Binary &Bin) {
  stringstream Stream;
  for (uint32_t i = 0; i < RegSize; i++) {
    Stream << " x" << i << ":" << (int32_t)RegFile[i] << "(" << hex
           << RegFile[i] << ")" << dec;
  }
  Stream << " PC:" << PC << "\n";
  Instr I = Bin.Instrs[PC];
  std::map<uint32_t, std::string> &PC2BBName = Bin.PC2BBName;
  switch (I.Op) {
  default:
    Stream << "\nWrong Opcode: " << I.Op << "\n";
    break;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    Stream << "  " << #_Name;                                                  \
    _WriteArgs;                                                                \
    Stream << "\n";                                                            \
    break;
#include "include/ISA.h"
#undef _ISA
  }
  return Stream.str();
}