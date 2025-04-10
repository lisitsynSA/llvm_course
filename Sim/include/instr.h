#ifndef INSTR_H
#define INSTR_H
#include <cstdint>
#include <map>
#include <string>

struct Instr {
  enum {
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  _Name = _Opcode,
#include "ISA.h"
#undef _ISA
  };
  uint32_t Op;
  uint32_t R1;
  uint32_t R2;
  uint32_t R3Imm;
  static std::map<std::string, uint32_t> Str2Op;
  static std::map<uint32_t, std::string> Op2Str;
  static void prepareDicts();
  static uint32_t getOpcode(std::string &InstrName);
};
#endif // INSTR_H
