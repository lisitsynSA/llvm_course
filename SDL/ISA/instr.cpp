#include "include/instr.h"
#include <sstream>
using namespace std;

map<string, uint32_t> Instr::Str2Op;
map<uint32_t, string> Instr::Op2Str;

void Instr::prepareDicts() {
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  Str2Op[#Name_] = Opcode_;                                                    \
  Op2Str[Opcode_] = #Name_;
#include "include/ISA.h"
#undef ISA_
}

uint32_t Instr::getOpcode(string &InstrName) {
  auto InstrRec = Str2Op.find(InstrName);
  if (InstrRec == Str2Op.end())
    return 0;
  return InstrRec->second;
}
