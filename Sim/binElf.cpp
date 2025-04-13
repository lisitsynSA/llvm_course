#include "elfio/elfio.hpp"
#include "include/bin.h"
#include "include/instr.h"
#include <cstdint>
#include <iomanip>
#include <sstream>
using namespace std;
using namespace ELFIO;

string hexCode(uint32_t i, uint32_t code) {
  std::stringstream stream;
  stream << setfill('0') << setw(4) << i << ": " << setw(8) << hex << code;
  return stream.str();
}

bool Binary::readBin(string FileName, string &ErrorMsg) {
  // Create an elfio reader
  elfio reader;

  // Load ELF data
  if (!reader.load(FileName)) {
    ErrorMsg = string("Can't find or process ELF file" + FileName);
    return true;
  }

  // Print ELF file sections info
  Elf_Half secNum = reader.sections.size();
  const uint32_t *code = nullptr;
  Elf_Xword appStart = 0;
  Elf_Xword appSize = 0;
  stringstream Stream;
  for (int sec = 0; sec < secNum; ++sec) {
    section *psec = reader.sections[sec];
    if (psec->get_name() == ".text") {
      code = (const uint32_t *)reader.sections[sec]->get_data();
      Stream << "[Section " << sec << "] " << psec->get_name()
             << " Size: " << psec->get_size() << "\n";
    }
    if (psec->get_type() == SHT_SYMTAB) {
      const symbol_section_accessor symbols(reader, psec);
      for (unsigned int symbol = 0; symbol < symbols.get_symbols_num();
           ++symbol) {
        string name;
        Elf64_Addr value;
        Elf_Xword size;
        unsigned char bind;
        unsigned char type;
        Elf_Half section_index;
        unsigned char other;

        // Read symbol properties
        symbols.get_symbol(symbol, name, value, size, bind, type, section_index,
                           other);
        if (name == "app") {
          appStart = value / 4;
          appSize = size / 4;
          Stream << "[Symbol " << symbol << "] " << name << " Offset: " << value
                 << " Size: " << size << endl;
        }
      }
    }
  }

  if (!code) {
    ErrorMsg = string("Can't find Entrypooint in " + FileName);
    return true;
  }

  PC2BBName[0] = "L0";
  BBName2PC["L0"] = 0;
  // Add Instructions and Labels
  for (uint32_t PC = 0; PC < appSize; ++PC) {
    uint32_t instr = code[appStart + PC];
    Instr I;
    // Parse Instruction
    I.R3Imm = instr & 0xFFFF;
    I.R2 = (instr >> 16) & 0xF;
    I.R1 = (instr >> 20) & 0xF;
    I.Op = instr >> 24;
    // Add Label
    if (I.Op == Instr::B || I.Op == Instr::BR_COND) {
      I.R3Imm = PC + (int16_t)I.R3Imm;
      string label = "L" + to_string(I.R3Imm);
      PC2BBName[I.R3Imm] = label;
      BBName2PC[label] = I.R3Imm;
    }
    Stream << hexCode(PC, instr) << "  ";
    switch (I.Op) {
    default:
      Stream << "Wrong Opcode\n";
      cout << Stream.str();
      return true;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    Stream << #_Name;                                                          \
    _WriteArgs;                                                                \
    Stream << "\n";                                                            \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    Instrs.push_back(I);
    // Add Label
    if (PC != appSize - 1 && (I.Op == Instr::B || I.Op == Instr::BR_COND)) {
      string label = "L" + to_string(PC + 1);
      PC2BBName[PC + 1] = label;
      BBName2PC[label] = PC + 1;
    }
  }
  cout << Stream.str();
  return false;
}