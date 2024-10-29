// ISA format:
// Opcode
// Name
// SkipArgs: string -> 0 [ifstream InputFile]
// ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// Execute: args -> EXECUTION [uint32_t R1, uint32_t R2, uint32_t R3Imm, CPU *C]
// IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

// SkipArgs
#define SKIP_3ARGS                                                             \
  { InputFile >> Arg >> Arg >> Arg; }
#define SKIP_2ARGS                                                             \
  { InputFile >> Arg >> Arg; }

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
#define READ_REG_LABEL                                                         \
  { READ_REG(R1) READ_LABEL }

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
#define WRITE_REG_LABEL                                                        \
  { WRITE_REG(R1) WRITE_LABEL }

// _IRGenExecute
#define GEP2_32(Arg) builder.CreateConstGEP2_32(regFileType, regFile, 0, Arg)
#define LOAD_REG(Arg) builder.CreateLoad(int32Type, GEP2_32(Arg))
#define GEN_IMM(Arg) builder.getInt32(Arg)

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

//    EXIT (NO ARGS)
_ISA(
    0x1, EXIT, {}, {}, {}, { C->Run = 0; }, { builder.CreateRetVoid(); })

//    FLUSH (NO ARGS)
_ISA(
    0x2, FLUSH, {}, {}, {}, { simFlush(); },
    { builder.CreateCall(simFlushFunc); })

//    XOR x1 x1 x1 (3REGS)
_ISA(
    0x3, XOR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] ^ C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateXor(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    MUL x3 x2 x1 (3REGS)
_ISA(
    0x4, MUL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2] * C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateMul(LOAD_REG(I.R2), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    SUBi x6 x6 16777216 (2REGS_IMM)
_ISA(
    0x5, SUBi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2] - R3Imm; },
    {
      builder.CreateStore(builder.CreateSub(LOAD_REG(I.R2), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    PUT_PIXEL x5 x2 x6 (3REGS)
_ISA(
    0x6, PUT_PIXEL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { simPutPixel(C->RegFile[R1], C->RegFile[R2], C->RegFile[R3Imm]); },
    {
      builder.CreateCall(simPutPixelFunc,
                         {LOAD_REG(I.R1), LOAD_REG(I.R2), LOAD_REG(I.R3Imm)});
    })

//    INC_NEi x4 x5 512 (2REGS_IMM)
_ISA(
    0x7, INC_NEi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = ++C->RegFile[R2] != R3Imm; },
    {
      Value *arg1_p = GEP2_32(I.R2);
      Value *arg1 =
          builder.CreateAdd(builder.CreateLoad(int32Type, arg1_p), GEN_IMM(1));
      builder.CreateStore(arg1, arg1_p);
      builder.CreateStore(builder.CreateICmpNE(arg1, GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })

//    BR_COND x4 label_13 (REG_IMM)
_ISA(
    0x8, BR_COND, SKIP_2ARGS, READ_REG_LABEL, WRITE_REG_LABEL,
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
