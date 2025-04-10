#include "include/bin.h"
#include "include/instr.h"
#include <cstdint>
#include <fstream>
#include <sstream>
using namespace std;

bool Binary::searchBBs(ifstream &InputFile, string &ErrorMsg) {
  string Name;
  string Arg;
  uint32_t PC = 0;
  uint32_t Opcode = 0;
  while (InputFile >> Name) {
    Opcode = Instr::getOpcode(Name);
    switch (Opcode) {
    default:
      if (BBName2PC.find(Name) != BBName2PC.end()) {
        ErrorMsg = string("Repetition of label: " + Name);
        return true;
      }
      BBName2PC[Name] = PC;
      if (PC2BBName.find(PC) != PC2BBName.end()) {
        ErrorMsg = string("2 labels can't be on the one PC: " + Name + " and " +
                          PC2BBName[PC]);
        return true;
      }
      PC2BBName[PC] = Name;
      continue;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    _SkipArgs;                                                                 \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    PC++;
  }
  return false;
}

string Binary::writeBBs() {
  stringstream Stream;
  for (auto &it : BBName2PC) {
    Stream << "  " << it.second << ": " << it.first << "\n";
  }
  return Stream.str();
}

bool Binary::readInstrs(ifstream &InputFile, string &ErrorMsg) {
  string Name;
  string Arg;
  uint32_t Opcode = 0;
  while (InputFile >> Name) {
    Opcode = Instr::getOpcode(Name);
    Instr I;
    I.Op = Opcode;
    switch (Opcode) {
    default:
      if (BBName2PC.find(Name) != BBName2PC.end())
        continue;
      ErrorMsg = string("Wrong Opcode for " + Name);
      return true;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    _ReadArgs;                                                                 \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    Instrs.push_back(I);
  }
  return false;
}

string Binary::writeInstrs() {
  stringstream Stream;
  uint32_t PC = 0;
  for (Instr &I : Instrs) {
    auto Label = PC2BBName.find(PC);
    if (Label != PC2BBName.end()) {
      Stream << Label->second << "\n";
    }
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
    PC++;
  }
  return Stream.str();
}

bool Binary::readFile(string FileName, string &ErrorMsg) {
  ifstream Input;
  Input.open(FileName);
  if (!Input.is_open()) {
    ErrorMsg = string("Can't open " + FileName);
    return true;
  }
  string LocalErrorMsg;
  if (searchBBs(Input, LocalErrorMsg)) {
    ErrorMsg = string("In searchBBs: " + LocalErrorMsg);
    return true;
  }
  Input.clear();
  Input.seekg(0, ios::beg);
  if (readInstrs(Input, LocalErrorMsg)) {
    ErrorMsg = string("In readInstrs: " + LocalErrorMsg);
    return true;
  }
  return false;
}
