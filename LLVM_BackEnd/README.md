
# TableGen Experiments
```
llvm-tblgen test.td
llvm-tblgen test_i.td
llvm-tblgen test.td -print-enums -class=SimReg

cd llvm-project
./build/bin/llvm-tblgen llvm/lib/Target/X86/X86.td -print-enums -class Register -I llvm/include/ -I llvm/lib/Target/X86/
./build/bin/llvm-tblgen llvm/lib/Target/X86/X86.td -gen-register-info -I llvm/include/ -I llvm/lib/Target/X86/
```

# Build LLVM
```
git checkout llvmorg-20.1.0
cmake -S llvm -B build -G Ninja -DLLVM_USE_LINKER=lld -DCMAKE_INSTALL_PREFIX=install -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF
ninja -C build -j 8 llc
./build/bin/llc --version
./build/bin/llc -help-hidden
```
Sim target adding example: https://github.com/lisitsynSA/llvm-add-backend (sim_backend_20.1.0 branch)

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
.../llvm-project/build/bin/llc test.ll -march sim -debug
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

#### [Sim] 6. Add empty SimPassConfig: + [Sim] 9. Add createSimISelDag
+ SimMCTargetDesc.cpp : SimPassConfig
>ERROR: Assertion `InstPrinter' failed.

#### [Sim] 7. Add empty SimInstPrinter
+ Sim/SimTargetMachine.cpp : createSimMCInstPrinter
+ Sim/SimInstPrinter.h
>ERROR: llc: error: target does not support generation of this file type

#### [Sim] 8. Add empty SimAsmPrinter
+ SimAsmPrinter.cpp
>ERROR: Segmentation fault (compileModule(char**, llvm::LLVMContext&) in Target->getObjFileLowering())

#### [Sim] 10. Add SimTargetMachine::getObjFileLowering
+ SimTargetMachine.cpp: TLOF
>ERROR: Segmentation fault in Running pass 'Expand large div/rem' on function '@main'

#### [Sim] 11. Update Subtarget and add SimTargetLowering
+ SimISelLowering.h : SimTargetLowering
>ERROR: Segmentation fault in Running pass 'Sim DAG->DAG Pattern Instruction Selection' on function '@main' in STI->getFrameLowering()

#### [Sim] 12. Add getFrameLowering to SimSubtarget
+ SimSubtarget.h : *getFrameLowering
>ERROR: Not Implemented  UNREACHABLE executed at virtual SDValue LowerCall(...)

#### [Sim] 13. Add Calling Convention, MachineFunction and Lowering Functions
+ SimCallingConv.td, SimMachineFunctionInfo.h + Big SimISelLowering.cpp Update
>ERROR: Segmentation fault in Running pass 'Sim DAG->DAG Pattern Instruction Selection' on function '@main' in MF.getSubtarget().getRegisterInfo()

#### [Sim] 14. Update SimRegisterInfo and add to SimSubtarget
+ SimRegisterInfo.cpp .h updates
+ SimSubtarget.h : + getRegisterInfo
>ERROR: Creating constant: t1: i32 = Constant<12> Assertion `idx < size()' failed. TLI.getNumRegistersForCallingConv

#### [Sim] 15. Extend SimTargetLowering with SimRegisterInfo
+ SimTargetLowering.cpp SimTargetLowering update
>ERROR: Segmentation fault ISEL: Starting pattern match

#### [Sim] 16. Add InstrInfo and TSInfo to SimSubtarget
+ SimSubtarget.h : + getInstrInfo, getSelectionDAGInfo
Check instructions in asm file (test.s):
```
main:                                   ; @main
; %bb.0:

.Lfunc_end0:
```
#### [Sim] 17. Add full SimInstPrinter
+ MCTargetDesc/SimInstPrinter.cpp
```
main:                                   ; @main
; %bb.0:
	BR r0
.Lfunc_end0:
```

#### [Sim] 18. Implement lowerSimMachineInstrToMCInst for AsmPrinter
+ SimMCInstLower.cpp
```
main:                                   ; @main
; %bb.0:
	MOVli r9 12
	BR r0
.Lfunc_end0:
```
#### Extra experiments:
```
build/bin/llc build/test.ll -march sim -debug -view-isel-dags
```
![image](https://github.com/user-attachments/assets/dbde84db-faee-4fea-83e7-18be9d352f44)
```
build/bin/llc build/test.ll -march sim -debug -view-sched-dags
```
![image](https://github.com/user-attachments/assets/d0a4b2b8-a564-4f8c-8cce-37379c2006c3)

### 3) Generate simple BIN
```
.../llvm-project/build/bin/llc test.ll -march sim --filetype=obj
```
>ERROR: createMCCodeEmitter failed
#### [Sim] 19. Add SimMCCodeEmitter
+ SimMCCodeEmitter.cpp
>ERROR: createMCAsmBackend failed
#### [Sim] 20. Add SimAsmBackend
+ SimAsmBackend.cpp
>ERROR: ELFSimAsmBackend::createObjectTargetWriter

#### [Sim] 21. Add SimELFObjectWriter
+ SimELFObjectWriter.cpp + add Sim in ELF.h/.cpp ELFObjectFile.h and ELFDumper.cpp

#### [Sim] 22. Update Sim Instruction info
+ Update SimInstrInfo.td SimInstrFormats.td

#### llvm-readobj:
```
ninja -C build -j 8 llvm-readobj
.../llvm-project/build/bin/llvm-readobj test.o
```
```
File: test.o
Format: elf32-sim
Arch: sim
AddressSize: 32bit
LoadName: <Not found>
```
#### llvm-readelf:

```
ninja -C build -j 8 llvm-readelf
.../llvm-project/build/bin/llvm-readelf -a test.o
```
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
### 4) Generate graphic ASM
graphic.ll:
```
define dso_local void @app() {
entry:
  call void @llvm.sim.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.sim.flush()
  ret void
}

declare void @llvm.sim.putpixel(i32, i32, i32)

declare void @llvm.sim.flush()
```
```
.../llvm-project/build/bin/llc graphic.ll -march sim --filetype=asm
```
>ERROR: llvm::SimTargetLowering::LowerCall Assertion `getTargetMachine().shouldAssumeDSOLocal(GV)'
#### [Sim] 23. Add Sim intrinsics support (flush and putpixel)
+ llvm/include/llvm/IR/IntrinsicsSim.td + update SimInstrInfo.td
Check intrinsics in asm file (graphic.s):
```
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 -1
	MOVli r4 5
	PUTPIXEL r4 r4 r2
	FLUSH
	BR r0
.Lfunc_end0:
```
Add intrisics to the custom FrontEnd:
```
// declare void @llvm.sim.putpixel(i32 noundef, i32 noundef, i32 noundef)
ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                            Type::getInt32Ty(context),
                                            Type::getInt32Ty(context)};
FunctionType *simPutPixelType =
    FunctionType::get(voidType, simPutPixelParamTypes, false);
simPutPixelFunc =
    module->getOrInsertFunction("llvm.sim.putpixel", simPutPixelType);

// declare void @llvm.sim.flush()
FunctionType *simFlushType = FunctionType::get(voidType, false);
simFlushFunc =
    module->getOrInsertFunction("llvm.sim.flush", simFlushType);
```
### 5) Generate graphic BIN
```
.../llvm-project/build/bin/llc graphic.ll -march sim --filetype=obj
```
Check intrinsics in object file:
```
hexedit graphic.o
New position 0x34 (.text section address)
... FF FF 20 AA  05 00 40 AA  02 00 44 EE  00 00 00 FF  00 00 00 BB ...

```
# Extra step for clang FrontEnd
```
void app() {
    simPutPixel(5, 5, 0xFFFFFFFF);
    simFlush();
}
```
```
cmake .... -DLLVM_ENABLE_PROJECTS="clang"
ninja -C build -j 8 clang
.../llvm-project/build/bin/clang -emit-llvm -S graphic.c -target sim
.../llvm-project/build/bin/clang -c graphic.c -target sim
```
>ERROR: unknown target triple 'sim'

#### [Sim] 24. Register Sim target for Clang
+ clang/lib/Basic/Targets/Sim.cpp .h
>ERROR: call to undeclared function simPutPixel / simFlush
#### [Sim] 25. Add Sim ClangBuiltin support (flush and putpixel)
+ clang/include/clang/Basic/BuiltinsSim.def
```
; Function Attrs: noinline nounwind optnone
define dso_local void @app() #0 {
entry:
  call void @llvm.sim.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.sim.flush()
  ret void
}

; Function Attrs: nounwind
declare void @llvm.sim.putpixel(i32, i32, i32) #1

; Function Attrs: nounwind
declare void @llvm.sim.flush() #1
```

# Simple graphic application full support
### 6) Generate application ASM
```
.../llvm-project/build/bin/clang ./app.c -target sim -emit-llvm -S -O2
.../llvm-project/build/bin/llc app.ll -march sim
```
>ERROR: LLVM ERROR: Cannot select: t5: ch = br t3
#### [Sim] 9. Add all Sim instructions
```
.LBB0_3:
	PUTPIXEL r14 r13 r15
	ADD r15 r15 r12
	ADDi r14 r14 1
	B.NE r14 r9 .LBB0_3
```

### 7) Generate application BIN
```
.../llvm-project/build/bin/llc app.ll -march sim --filetype=obj
```
```
... 0F 00 ED EE  0C 00 FF 30  01 00 EE 40  FD FF E9 71 ...
```

