
# TableGen Experiments
```
llvm-tblgen test.td
llvm-tblgen test_i.td
llvm-tblgen test.td -print-enums -class=SimReg

cd llvm-project
./build/bin/llvm-tblgen llvm/lib/Target/X86/X86.td -print-enums -class Register -I llvm/include/
```

# Build LLVM
```
git checkout llvmorg-18.1.1
mkdir build && cd build
cmake -S ../llvm/ -B ./ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./install -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_TARGETS_TO_BUILD=Sim
ninja -j4
```
Sim target adding example: https://github.com/lisitsynSA/llvm-add-backend

# Steps for custom FrontEnd
### 1) Registered
#### [Sim] 1. Register a new Sim architecture BackEnd:
+ Add Sim to LLVM info
+ CMakeLists.txt  MCTargetDesc  Sim.h  SimTargetMachine.cpp  SimTargetMachine.h  TargetInfo
```
.../llvm-project/build/bin/llc --version
  ...
  Registered Targets:
    sim - Simulator target for LLVM course
```
### 2) Generate simple ASM
test.ll:
```
define dso_local i32 @main() {
  ret i32 12
}
```
```
.../llvm-project/build/bin/llc test.ll -march sim
```
#### [Sim] 2. Add Register Info for Sim architecture:
>ERROR: void llvm::TargetPassConfig::addPassesToHandleExceptions(): Assertion `MCAI && "No MCAsmInfo"' failed.
+ Sim/SimTargetMachine.cpp SimTargetMachine +initAsmInfo();
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `MRI && "Unable to create reg info"' failed.
+ SimMCTargetDesc.cpp : createSimMCRegisterInfo
+ SimRegisterInfo.td/.h/.cpp + generation
+ SimGenRegisterInfo.inc including:
```
const SimFrameLowering *
SimGenRegisterInfo::getFrameLowering(const MachineFunction &MF) {
  return static_cast<const SimFrameLowering *>(
      MF.getSubtarget().getFrameLowering());
}
```
+ SimFrameLowering.h (virtual... =0)
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `MII && "Unable to create instruction info"' failed.
#### [Sim] 3. Add Instruction Info for Sim architecture:
+ SimMCTargetDesc.cpp : createSimMCInstrInfo
+ SimInstrFormat.td SimInstrInfo.td/.h/.cpp + generation
+ SimImfo.h
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `STI && "Unable to create subtarget info"' failed.
#### [Sim] 4. Add empty Subtarget for Sim architecture:
+ SimMCTargetDesc.cpp : createSimMCSubtargetInfo + SimSubtarget.h/.cpp + gen SimGenSubtargetInfo.inc 
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `TmpAsmInfo && "MCAsmInfo not initialized. "
#### [Sim] 5. Add SimMCAsmInfo for Sim architecture:
+ SimMCTargetDesc.cpp : createSimMCAsmInfo + SimMCAsmInfo.h/.cpp
>ERROR: llc: error: target does not support generation of this file type
#### [Sim] 6. Add Sim info for Asm generation:
+ Many actions that should be splitted to several commits
Check inctructions in asm file (test.s):
```
main:                                   ; @main
; %bb.0:
	MOVli r9 12
	BR r0
.Lfunc_end0:
```
### 3) Generate simple BIN
```
.../llvm-project/build/bin/llc test.ll -march sim --filetype=obj
.../llvm-project/build/bin/llvm-readobj test.o
.../llvm-project/build/bin/llvm-readelf -a test.o
```
#### [Sim] 7. Add Sim info for Obj generation:
>ERROR: createMCCodeEmitter failed
+ SimMCCodeEmitter.cpp
>ERROR: createMCAsmBackend failed
+ SimAsmBackend.cpp SimELFObjectWriter.cpp + add Sim in ELF.h/.cpp ELFObjectFile.h and ELFDumper.cpp
#### llvm-readobj:
```
File: test.o
Format: elf32-sim
Arch: sim
AddressSize: 32bit
LoadName: <Not found>
```
#### llvm-readelf:
```
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Simulator target for LLVM course
....
  Number of section headers:         5
  Section header string table index: 1
There are 5 section headers, starting at offset 0xa0:

Section Headers:
  [Nr] Name              Type            Address  Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .strtab           STRTAB          00000000 00006c 000034 00      0   0  1
  [ 2] .text             PROGBITS        00000000 000034 000008 00  AX  0   0  4
  [ 3] .note.GNU-stack   PROGBITS        00000000 00003c 000000 00      0   0  1
  [ 4] .symtab           SYMTAB          00000000 00003c 000030 10      1   2  4
```
Check inctructions in object file:
```
hexedit test.o
New position 0x34 (.text section address)
... 0C 00 90 AA  00 00 00 BB ...

```
### 4) Generate application ASM
```
.../llvm-project/build/bin/llc app.ll -march sim
```
>ERROR: LLVM ERROR: Cannot select: t5: ch = br t3

### 5) Generate application BIN
```
.../llvm-project/build/bin/llc app.ll -march sim --filetype=obj
```

# Steps for clang FrontEnd
### 0) Add clang to build
```
cmake .... -DLLVM_ENABLE_PROJECTS="clang"
 ```
### 1) Registered
```
.../llvm-project/build/bin/llc --version
.../llvm-project/build/bin/clang -print-targets
  ...
  Registered Targets:
    sim - Sim 32
```
### 2) Generate simple ASM
```
.../llvm-project/build/bin/llc test.ll -march sim
.../llvm-project/build/bin/clang test.ll -target sim -S
vim test.s
```
### 3) Generate simple BIN
```
.../llvm-project/build/bin/clang test.ll -target sim -c
.../llvm-project/build/bin/llc test.ll -march sim --filetype=obj
readelf -a test.o

```