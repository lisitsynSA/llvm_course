
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
void app() {
  for (int step = 0; step < 1000; ++step) {
    for (int y = 0; y < SIM_Y_SIZE; ++y)
      for (int x = 0; x < SIM_X_SIZE; ++x)
        simPutPixel(x, y, 0xFF000000 + x * y * step);
    simFlush();
  }
}
```
LLVM IR for app with Sim ClangBuiltins:
```
.../llvm-project/build/bin/clang ./app.c -target sim -emit-llvm -S -O2
```
app.s generation:
```
.../llvm-project/build/bin/llc app.ll -march sim -debug
```
>ERROR: Cannot select: t5: ch = br t3, BasicBlock:ch<for.cond5.preheader>
#### [Sim] 26. Add branch instruction B and btarget16 operand
+ instruction B and btarget16
>ERROR: Cannot select: t1: i32 = Constant<-16777216>
#### [Sim] 27. Add instructions MOVHI and ORI for i32 lowering
+ lowering i32 and instructions MOVHI and ORI
#### Offshoot for graphic.s
```
	MOVli r2 -1 <- incorrect
	MOVli r4 5
	PUTPIXEL r4 r4 r2
	FLUSH
	BR r0
```
```
ISEL: Starting selection on root node: t3: i32 = Constant<-1>
ISEL: Starting pattern match
  Initial Opcode index to 55
Creating constant: t8: i32 = TargetConstant<-1>
  Morphed node: t3: i32 = MOVLI TargetConstant:i32<-1>
ISEL: Match complete!
```
#### [Sim] 28. Fix i32 to simm16 lowering
```
ISEL: Starting selection on root node: t3: i32 = Constant<-1>
ISEL: Starting pattern match
  Initial Opcode index to 55
  Skipped scope entry (due to false predicate) at index 58, continuing at 76
Creating constant: t8: i32 = TargetConstant<-1>
Creating constant: t9: i32 = TargetConstant<65535>
Creating new machine node: t10: i32 = MOVHI TargetConstant:i32<65535>
  Created node: t10: i32 = MOVHI TargetConstant:i32<65535>
  Morphed node: t3: i32 = ORI t10, TargetConstant:i32<65535>
ISEL: Match complete!
```
```
  MOVhi r2 65535
  ORi r2 r2 65535
  MOVli r4 5
  PUTPIXEL r4 r4 r2
  FLUSH
  BR r0
```
#### Return to app.s generation:
>ERROR: LowerOperation not implemented for this target!
Legalizing: t26: ch = br_cc t22, seteq:ch, t10, Constant:i32<512>, BasicBlock:ch<for.cond.cleanup7>
#### [Sim] 29. Add instructions INC_EQi and BR_COND for br_cc lowering
+ instructions INC_EQi and BR_COND
>ERROR: Cannot select: t15: i32 = add nsw t7, t14
#### [Sim] 30. Add ADD instruction
+ instruction ADD
>ERROR: Target didn't implement TargetInstrInfo::copyPhysReg!
#### [Sim] 31. Add copyPhysReg method
+ copyPhysReg
```
app:
	MOVli r2 0
	MOVhi r4 65280
	ORi r4 r4 0 <- Optimization candidate: i32 lowering
	MOVli r9 1 <- Optimization candidate: Duplication of INC_EQi
.LBB0_1:
	MOVli r10 0
	MOVli r11 0
	B .LBB0_3
.LBB0_3:
	MOVli r13 0
	ORi r12 r4 0
	B .LBB0_6
.LBB0_6:
	PUTPIXEL r13 r11 r12
	ADD r12 r12 r10
	ADD r14 r13 r9 <- Optimization candidate: Duplication of INC_EQi
	INC_EQi r15 r13 512
	ORi r13 r14 0 <- Optimization candidate: Duplication of INC_EQi
	BR_COND r15 .LBB0_5
	B .LBB0_6
.LBB0_5:
	ADD r10 r10 r2
	ADD r12 r11 r9 <- Optimization candidate: Duplication of INC_EQi
	INC_EQi r13 r11 256
	ORi r11 r12 0 <- Optimization candidate: Duplication of INC_EQi
	BR_COND r13 .LBB0_4
	B .LBB0_3
.LBB0_4:
	ADD r10 r2 r9 <- Optimization candidate: Duplication of INC_EQi
	FLUSH
	INC_EQi r11 r2 1000
	ORi r2 r10 0 <- Optimization candidate: Duplication of INC_EQi
	BR_COND r11 .LBB0_2
	B .LBB0_1
.LBB0_2:
	BR r0
```

```
t0: ch,glue = EntryToken
t3: i32,ch = CopyFromReg t0, Register:i32 %7
t7: i32,ch = CopyFromReg t0, Register:i32 %6
t10: i32 = add nuw nsw t3, Constant:i32<1>
      t12: ch = CopyToReg t0, Register:i32 %8, t10
          t14: i32,ch = CopyFromReg t0, Register:i32 %1
        t15: i32 = add nsw t7, t14
      t17: ch = CopyToReg t0, Register:i32 %9, t15
        t5: i32,ch = CopyFromReg t0, Register:i32 %2
      t8: ch = llvm.sim.putpixel t0, TargetConstant:i32<11547>, t3, t5, t7
    t22: ch = TokenFactor t12, t17, t8
  t26: ch = br_cc t22, seteq:ch, t10, Constant:i32<512>, BasicBlock:ch<for.cond.cleanup7 0x560325b3b150>
t25: ch = br t26, BasicBlock:ch<for.body8 0x560325b3b270>

ISEL: Starting selection on root node: t26: ch = br_cc t22, seteq:ch, t10, Constant:i32<512>, BasicBlock:ch<for.cond.cleanup7 0x56215ba7c2e0>
ISEL: Starting pattern match
  Initial Opcode index to 4
  OpcodeSwitch from 9 to 13
Creating constant: t27: i32 = TargetConstant<512>
Creating new machine node: t28: i32 = INC_EQi t3, TargetConstant:i32<512>
  Created node: t28: i32 = INC_EQi t3, TargetConstant:i32<512>
  Morphed node: t26: ch = BR_COND t28, BasicBlock:ch<for.cond.cleanup7 0x56215ba7c2e0>, t22
ISEL: Match complete!
```
#### [Sim] 32. Optimize patterns and instructions
+ better i32 lowering, correct BR_CC lowering
```
app:
	MOVli r2 0          == STEP = 0
.LBB0_1:
	MOVli r4 0          == COLOR_INC
	MOVli r9 0          == Y = 0
	B .LBB0_3
.LBB0_3:
	MOVli r10 0         == X = 0
	MOVhi r11 65280     == COLOR = 0xFF000000
	B .LBB0_6
.LBB0_6:
	PUTPIXEL r10 r9 r11 == PIXEL X Y COLOR
	INC_EQi r12 r10 512 == (++X == 512)
	ADD r11 r11 r4      == COLOR += COLOR_INC
	BR_COND r12 .LBB0_5
	B .LBB0_6
.LBB0_5:
	INC_EQi r10 r9 256 == (++Y == 256)
	ADD r4 r4 r2       == COLOR_INC += STEP
	BR_COND r10 .LBB0_4
	B .LBB0_3
.LBB0_4:
	INC_EQi r4 r2 1000 == (++STEP == 1000)
	FLUSH
	BR_COND r4 .LBB0_2
	B .LBB0_1
.LBB0_2:
	BR r0
```
Support custom FlexBison FrontEnd output:
```
opt app.ll -O2 -o app.opt.ll -S
```
>ERROR: Cannot select: t26: ch = br_cc t22, setne:ch, t10, Constant:i32<512>, BasicBlock:ch<for.cond.cleanup7>
+ instruction INC_NEi
Support custom ANTLR FrontEnd output:
>ERROR: Cannot select: t8: i32 = mul t6, t7
+ instruction MUL
#### [Sim] 33. Add instructions INC_NEi and MUL
+ instructions INC_NEi and MUL

### 7) Generate application BIN
```
.../llvm-project/build/bin/llc app.ll -march sim --filetype=obj
```
```
...
          .LBB0_6:
0B 00 A9 EE  PUTPIXEL r10 r9 r11
00 02 CA 90  INC_EQi r12 r10 512
04 00 BB 30  ADD r11 r11 r4
00 00 C0 BC  BR_COND r12 .LBB0_5 <- Empty offset
00 00 00 B0  B .LBB0_6           <- Empty offset
          .LBB0_5:
...
```
#### [Sim] 34. Add fixup_Sim_PC16 for offsets updates
```
          .LBB0_6:
0B 00 A9 EE  PUTPIXEL r10 r9 r11
00 02 CA 90  INC_EQi r12 r10 512
04 00 BB 30  ADD r11 r11 r4
02 00 C0 BC  BR_COND r12 .LBB0_5 <- Offset: 2
FC FF 00 B0  B .LBB0_6           <- Offset: -4
          .LBB0_5:
```
