#include "include/instr.h"

std::map<std::string, uint32_t> Instr::Str2Op;
std::map<uint32_t, std::string> Instr::Op2Str;

void Instr::prepareDicts() {
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  Str2Op[#Name_] = Opcode_;                                                    \
  Op2Str[Opcode_] = #Name_;
#include "include/ISA.h"
#undef ISA_
}

uint32_t Instr::getOpcode(std::string &InstrName) {
  auto InstrRec = Str2Op.find(InstrName);
  if (InstrRec == Str2Op.end())
    return 0;
  return InstrRec->second;
}
