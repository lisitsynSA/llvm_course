// ISA format:
// Opcode
// Name
// SkipArgs: string -> 0 [ifstream InputFile]
// ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// Execute: args -> EXECUTION [uint32_t R1, uint32_t R2, uint32_t R3Imm, CPU *C]
// IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

// SkipArgs
#define SKIP_3ARGS                                                             \
  { InputFile >> Arg >> Arg >> Arg; }
#define SKIP_2ARGS                                                             \
  { InputFile >> Arg >> Arg; }
#define SKIP_1ARGS                                                             \
  { InputFile >> Arg; }

// ReadArgs
#define READ_REG(Reg)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.Reg = std::stoi(Arg.substr(1));                                          \
  }
#define READ_IMM                                                               \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.R3Imm = std::stoi(Arg);                                                  \
  }
#define READ_LABEL                                                             \
  {                                                                            \
    InputFile >> Arg;                                                          \
    if (BBName2PC.find(Arg) == BBName2PC.end()) {                              \
      ErrorMsg = std::string("Can't find label: " + Arg);                      \
      return true;                                                             \
    }                                                                          \
    I.R3Imm = BBName2PC[Arg];                                                  \
  }
#define READ_3REGS                                                             \
  { READ_REG(R1) READ_REG(R2) READ_REG(R3Imm) }
#define READ_2REGS_IMM                                                         \
  { READ_REG(R1) READ_REG(R2) READ_IMM }
#define READ_2REGS                                                             \
  { READ_REG(R1) READ_REG(R2) }
#define READ_REG_LABEL                                                         \
  { READ_REG(R1) READ_LABEL }
#define READ_REG_IMM                                                           \
  { READ_REG(R1) READ_IMM }

// WriteArgs
#define WRITE_REG(Reg)                                                         \
  { Stream << " x" << I.Reg; }
#define WRITE_IMM                                                              \
  { Stream << " " << I.R3Imm; }
#define WRITE_LABEL                                                            \
  { Stream << " " << PC2BBName[I.R3Imm]; }
#define WRITE_3REGS                                                            \
  { WRITE_REG(R1) WRITE_REG(R2) WRITE_REG(R3Imm) }
#define WRITE_2REGS_IMM                                                        \
  { WRITE_REG(R1) WRITE_REG(R2) WRITE_IMM }
#define WRITE_2REGS                                                            \
  { WRITE_REG(R1) WRITE_REG(R2) }
#define WRITE_REG_LABEL                                                        \
  { WRITE_REG(R1) WRITE_LABEL }
#define WRITE_REG_IMM                                                          \
  { WRITE_REG(R1) WRITE_IMM }

// IRGenExecute_
#define GEP2_32(Arg) builder.CreateConstGEP2_32(regFileType, regFile, 0, Arg)
#define LOAD_REG(Arg) builder.CreateLoad(int32Type, GEP2_32(Arg))
#define GEN_IMM(Arg) builder.getInt32(Arg)

// ISA_(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

//    EXIT (NO ARGS)
ISA_(0xBB, EXIT, {}, {}, {}, { C->Run = 0; }, { builder.CreateRetVoid(); })

//    FLUSH (NO ARGS)
ISA_(
    0xFF, FLUSH, {}, {}, {}, { simFlush(); },
    { builder.CreateCall(simFlushFunc); })

//    ADD x3 x2 x1 (3REGS)
ISA_(
    0x30, ADD, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] + C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateAdd(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    MUL x3 x2 x1 (3REGS)
ISA_(
    0x32, MUL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] * C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateMul(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    XOR x1 x1 x1 (3REGS)
ISA_(
    0x36, XOR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] ^ C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateXor(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    SUBi x6 x6 16777216 (2REGS_IMM)
ISA_(
    0x41, SUBi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] - R3Imm; },
    {
      builder.CreateStore(builder.CreateSub(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    ORi x6 x6 16777216 (2REGS_IMM)
ISA_(
    0x44, ORi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] | R3Imm; },
    {
      builder.CreateStore(builder.CreateOr(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    PUT_PIXEL x5 x2 x6 (3REGS)
ISA_(
    0xEE, PUT_PIXEL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { simPutPixel(C->RegFile[R1], C->RegFile[R2], C->RegFile[R3Imm]); },
    {
      builder.CreateCall(simPutPixelFunc,
                         {LOAD_REG(I.R1), LOAD_REG(I.R2), LOAD_REG(I.R3Imm)});
    })

//    INC_NEi x4 x5 512 (2REGS_IMM)
ISA_(
    0x91, INC_NEi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = ++C->RegFile[R2] != R3Imm; },
    {
      Value *arg1_p = GEP2_32(I.R2);
      Value *arg1 =
          builder.CreateAdd(builder.CreateLoad(int32Type, arg1_p), GEN_IMM(1));
      builder.CreateStore(arg1, arg1_p);
      Value *cmp = builder.CreateSExt(
          builder.CreateICmpNE(arg1, GEN_IMM(I.R3Imm)), int32Type);
      builder.CreateStore(cmp, GEP2_32(I.R1));
    })

//    INC_EQi x4 x5 512 (2REGS_IMM)
ISA_(
    0x90, INC_EQi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = ++C->RegFile[R2] == R3Imm; },
    {
      Value *arg1_p = GEP2_32(I.R2);
      Value *arg1 =
          builder.CreateAdd(builder.CreateLoad(int32Type, arg1_p), GEN_IMM(1));
      builder.CreateStore(arg1, arg1_p);
      Value *cmp = builder.CreateSExt(
          builder.CreateICmpEQ(arg1, GEN_IMM(I.R3Imm)), int32Type);
      builder.CreateStore(cmp, GEP2_32(I.R1));
    })

//    BR_COND x4 label_13 (REG_IMM)
ISA_(
    0xBC, BR_COND, SKIP_2ARGS, READ_REG_LABEL, WRITE_REG_LABEL,
    {
      if (C->RegFile[R1]) {
        C->NextPC = R3Imm;
      }
    },
    {
      PC++;
      builder.CreateCondBr(
          builder.CreateTrunc(LOAD_REG(I.R1), builder.getInt1Ty()),
          BBMap[I.R3Imm], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    B label_13 (IMM)
ISA_(
    0xB0, B, SKIP_1ARGS, READ_LABEL, WRITE_LABEL, { C->NextPC = R3Imm; },
    {
      PC++;
      builder.CreateBr(BBMap[I.R3Imm]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    MOVli r2 0 (REG_IMM)
ISA_(
    0xAA, MOVli, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[R1] = R3Imm; },
    { builder.CreateStore(GEN_IMM(I.R3Imm), GEP2_32(I.R1)); })

//    MOVhi r11 65280 (REG_IMM)
ISA_(
    0xAF, MOVhi, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[R1] = R3Imm << 16; },
    { builder.CreateStore(GEN_IMM(I.R3Imm << 16), GEP2_32(I.R1)); })

// Support app2.c
//    RAND r4 (REG)
ISA_(
    0xDD, RAND, SKIP_1ARGS, READ_REG(R1), WRITE_REG(R1),
    { C->RegFile[R1] = simRand(); },
    { builder.CreateStore(builder.CreateCall(simRandFunc), GEP2_32(I.R1)); })
//    ABS r4 r11 (2REGS)
ISA_(
    0xAB, ABS, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    {
      int32_t r2 = C->RegFile[R2];
      C->RegFile[R1] = r2 < 0 ? -r2 : r2;
    },
    {
      builder.CreateStore(
          builder.CreateCall(AbsFunc, {LOAD_REG(I.R2), builder.getInt1(true)}),
          GEP2_32(I.R1));
    })
//    UREMi r2 r2 10 (2REGS_IMM)
ISA_(
    0x4a, UREMi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] % R3Imm; },
    {
      builder.CreateStore(builder.CreateURem(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    ANDi r4 r4 510 (2REGS_IMM)
ISA_(
    0x45, ANDi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] & R3Imm; },
    {
      builder.CreateStore(builder.CreateAnd(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    MULi r4 r4 6554 (2REGS_IMM)
ISA_(
    0x42, MULi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] * R3Imm; },
    {
      builder.CreateStore(builder.CreateMul(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SRAi r14 r2 31 (2REGS_IMM)
ISA_(
    0x47, SRAi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    {
      int32_t r2 = C->RegFile[R2];
      C->RegFile[R1] = r2 >> R3Imm;
    },
    {
      builder.CreateStore(builder.CreateAShr(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SRLi r4 r4 16 (2REGS_IMM)
ISA_(
    0x48, SRLi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] >> R3Imm; },
    {
      builder.CreateStore(builder.CreateLShr(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SHLi r14 r14 16 (2REGS_IMM)
ISA_(
    0x49, SHLi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] << R3Imm; },
    {
      builder.CreateStore(builder.CreateShl(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SUB r14 r15 r14 (3REGS)
ISA_(
    0x31, SUB, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] - C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateSub(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    OR r14 r15 r14 (3REGS)
ISA_(
    0x34, OR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] | C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateOr(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    DIVi r15 r9 50 (2REGS_IMM)
ISA_(
    0x43, DIVi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    {
      int32_t r2 = C->RegFile[R2];
      int32_t r3 = R3Imm;
      C->RegFile[R1] = r2 / r3;
    },
    {
      builder.CreateStore(builder.CreateSDiv(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })