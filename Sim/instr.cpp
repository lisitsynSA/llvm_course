#include "include/instr.h"
#include <sstream>
using namespace std;

map<string, uint32_t> Instr::Str2Op;
map<uint32_t, string> Instr::Op2Str;

void Instr::prepareDicts() {
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  Str2Op[#_Name] = _Opcode;                                                    \
  Op2Str[_Opcode] = #_Name;
#include "include/ISA.h"
#undef _ISA
}

uint32_t Instr::getOpcode(string &InstrName) {
  auto InstrRec = Str2Op.find(InstrName);
  if (InstrRec == Str2Op.end())
    return 0;
  return InstrRec->second;
}
