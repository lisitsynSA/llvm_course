#include "include/bin.h"
#include "include/instr.h"
#include <cstdint>
#include <fstream>
#include <sstream>

bool Binary::searchBBs(std::ifstream &InputFile, std::string &ErrorMsg) {
  std::string Name;
  std::string Arg;
  uint32_t PC = 0;
  uint32_t Opcode = 0;
  while (InputFile >> Name) {
    Opcode = Instr::getOpcode(Name);
    switch (Opcode) {
    default:
      if (BBName2PC.find(Name) != BBName2PC.end()) {
        ErrorMsg = std::string("Repetition of label: " + Name);
        return true;
      }
      BBName2PC[Name] = PC;
      if (PC2BBName.find(PC) != PC2BBName.end()) {
        ErrorMsg = std::string("2 labels can't be on the one PC: " + Name + " and " +
                          PC2BBName[PC]);
        return true;
      }
      PC2BBName[PC] = Name;
      continue;
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  case (Opcode_):                                                              \
    SkipArgs_;                                                                 \
    break;
#include "include/ISA.h"
#undef ISA_
    }
    PC++;
  }
  return false;
}

std::string Binary::writeBBs() {
  std::stringstream Stream;
  for (auto &it : BBName2PC) {
    Stream << "  " << it.second << ": " << it.first << '\n';
  }
  return Stream.str();
}

bool Binary::readInstrs(std::ifstream &InputFile, std::string &ErrorMsg) {
  std::string Name;
  std::string Arg;
  uint32_t Opcode = 0;
  while (InputFile >> Name) {
    Opcode = Instr::getOpcode(Name);
    Instr I;
    I.Op = Opcode;
    switch (Opcode) {
    default:
      if (BBName2PC.find(Name) != BBName2PC.end())
        continue;
      ErrorMsg = std::string("Wrong Opcode for " + Name);
      return true;
#define ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,       \
             IRGenExecute_)                                                    \
  case (Opcode_):                                                              \
    ReadArgs_;                                                                 \
    break;
#include "include/ISA.h"
#undef ISA_
    }
    Instrs.push_back(I);
  }
  return false;
}

std::string Binary::writeInstrs() {
  std::stringstream Stream;
  uint32_t PC = 0;
  for (Instr &I : Instrs) {
    auto Label = PC2BBName.find(PC);
    if (Label != PC2BBName.end()) {
      Stream << Label->second << '\n';
    }
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
    PC++;
  }
  return Stream.str();
}

bool Binary::readFile(std::string FileName, std::string &ErrorMsg) {
  std::ifstream Input;
  Input.open(FileName);
  if (!Input.is_open()) {
    ErrorMsg = std::string("Can't open " + FileName);
    return true;
  }
  std::string LocalErrorMsg;
  if (searchBBs(Input, LocalErrorMsg)) {
    ErrorMsg = std::string("In searchBBs: " + LocalErrorMsg);
    return true;
  }
  Input.clear();
  Input.seekg(0, std::ios::beg);
  if (readInstrs(Input, LocalErrorMsg)) {
    ErrorMsg = std::string("In readInstrs: " + LocalErrorMsg);
    return true;
  }
  return false;
}
