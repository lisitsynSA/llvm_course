#include "include/bin.h"
#include "include/cpu.h"
#include "include/extIR.h"
#include "include/fullIR.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    outs() << "\n[ERROR] Need 2 argument: file with assembler code and "
              "execution mod (1-3)\n  1: Simulation 2: IR with emulate funcs "
              "3: Full IR generation\n";
    return 1;
  }
  Instr::prepareDicts();
  Binary Bin;
  std::string ErrorMsg;
  if (Bin.readFile(argv[1], ErrorMsg)) {
    outs() << "\n[ASM READ ERROR] " << ErrorMsg << '\n';
    return 1;
  }
  outs() << "\n[BasicBlocks]\n" << Bin.writeBBs();
  outs() << "\n[Binary]\n" << Bin.writeInstrs();
  CPU Cpu;

  int Mode = atoi(argv[2]);
  switch (Mode) {
  case 1:
    // Simulation
    if (Cpu.Execute(Bin, ErrorMsg)) {
      outs() << "\n[CPU RUN ERROR] " << ErrorMsg << '\n';
      return 1;
    }
    break;
  case 2:
    // IR with emulate funcs
    {
      ExtIR Ext;
      Ext.buildIR(Bin);
      Ext.dumpIR();
      if (Ext.verifyIR())
        return 1;
      Ext.executeIR(Cpu);
    }
    break;
  case 3:
    // only IR
    {
      FullIR Full;
      Full.buildIR(Bin);
      Full.dumpIR();
      if (Full.verifyIR())
        return 1;
      Full.executeIR(Cpu);
    }
    break;
  default:
    outs() << "\n[ERROR] Incorrect 2nd argument, mode should be 1-3\n  1: "
              "Simulation 2: IR with emulate funcs 3: Full IR generation\n";
    return 1;
  }

  return 0;
}
