/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Target Instruction Enum Values and Descriptors                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_INSTRINFO_ENUM
#undef GET_INSTRINFO_ENUM
namespace llvm::Sim {
  enum {
    PHI	= 0,
    INLINEASM	= 1,
    INLINEASM_BR	= 2,
    CFI_INSTRUCTION	= 3,
    EH_LABEL	= 4,
    GC_LABEL	= 5,
    ANNOTATION_LABEL	= 6,
    KILL	= 7,
    EXTRACT_SUBREG	= 8,
    INSERT_SUBREG	= 9,
    IMPLICIT_DEF	= 10,
    INIT_UNDEF	= 11,
    SUBREG_TO_REG	= 12,
    COPY_TO_REGCLASS	= 13,
    DBG_VALUE	= 14,
    DBG_VALUE_LIST	= 15,
    DBG_INSTR_REF	= 16,
    DBG_PHI	= 17,
    DBG_LABEL	= 18,
    REG_SEQUENCE	= 19,
    COPY	= 20,
    BUNDLE	= 21,
    LIFETIME_START	= 22,
    LIFETIME_END	= 23,
    PSEUDO_PROBE	= 24,
    ARITH_FENCE	= 25,
    STACKMAP	= 26,
    FENTRY_CALL	= 27,
    PATCHPOINT	= 28,
    LOAD_STACK_GUARD	= 29,
    PREALLOCATED_SETUP	= 30,
    PREALLOCATED_ARG	= 31,
    STATEPOINT	= 32,
    LOCAL_ESCAPE	= 33,
    FAULTING_OP	= 34,
    PATCHABLE_OP	= 35,
    PATCHABLE_FUNCTION_ENTER	= 36,
    PATCHABLE_RET	= 37,
    PATCHABLE_FUNCTION_EXIT	= 38,
    PATCHABLE_TAIL_CALL	= 39,
    PATCHABLE_EVENT_CALL	= 40,
    PATCHABLE_TYPED_EVENT_CALL	= 41,
    ICALL_BRANCH_FUNNEL	= 42,
    FAKE_USE	= 43,
    MEMBARRIER	= 44,
    JUMP_TABLE_DEBUG_INFO	= 45,
    CONVERGENCECTRL_ENTRY	= 46,
    CONVERGENCECTRL_ANCHOR	= 47,
    CONVERGENCECTRL_LOOP	= 48,
    CONVERGENCECTRL_GLUE	= 49,
    G_ASSERT_SEXT	= 50,
    G_ASSERT_ZEXT	= 51,
    G_ASSERT_ALIGN	= 52,
    G_ADD	= 53,
    G_SUB	= 54,
    G_MUL	= 55,
    G_SDIV	= 56,
    G_UDIV	= 57,
    G_SREM	= 58,
    G_UREM	= 59,
    G_SDIVREM	= 60,
    G_UDIVREM	= 61,
    G_AND	= 62,
    G_OR	= 63,
    G_XOR	= 64,
    G_ABDS	= 65,
    G_ABDU	= 66,
    G_IMPLICIT_DEF	= 67,
    G_PHI	= 68,
    G_FRAME_INDEX	= 69,
    G_GLOBAL_VALUE	= 70,
    G_PTRAUTH_GLOBAL_VALUE	= 71,
    G_CONSTANT_POOL	= 72,
    G_EXTRACT	= 73,
    G_UNMERGE_VALUES	= 74,
    G_INSERT	= 75,
    G_MERGE_VALUES	= 76,
    G_BUILD_VECTOR	= 77,
    G_BUILD_VECTOR_TRUNC	= 78,
    G_CONCAT_VECTORS	= 79,
    G_PTRTOINT	= 80,
    G_INTTOPTR	= 81,
    G_BITCAST	= 82,
    G_FREEZE	= 83,
    G_CONSTANT_FOLD_BARRIER	= 84,
    G_INTRINSIC_FPTRUNC_ROUND	= 85,
    G_INTRINSIC_TRUNC	= 86,
    G_INTRINSIC_ROUND	= 87,
    G_INTRINSIC_LRINT	= 88,
    G_INTRINSIC_LLRINT	= 89,
    G_INTRINSIC_ROUNDEVEN	= 90,
    G_READCYCLECOUNTER	= 91,
    G_READSTEADYCOUNTER	= 92,
    G_LOAD	= 93,
    G_SEXTLOAD	= 94,
    G_ZEXTLOAD	= 95,
    G_INDEXED_LOAD	= 96,
    G_INDEXED_SEXTLOAD	= 97,
    G_INDEXED_ZEXTLOAD	= 98,
    G_STORE	= 99,
    G_INDEXED_STORE	= 100,
    G_ATOMIC_CMPXCHG_WITH_SUCCESS	= 101,
    G_ATOMIC_CMPXCHG	= 102,
    G_ATOMICRMW_XCHG	= 103,
    G_ATOMICRMW_ADD	= 104,
    G_ATOMICRMW_SUB	= 105,
    G_ATOMICRMW_AND	= 106,
    G_ATOMICRMW_NAND	= 107,
    G_ATOMICRMW_OR	= 108,
    G_ATOMICRMW_XOR	= 109,
    G_ATOMICRMW_MAX	= 110,
    G_ATOMICRMW_MIN	= 111,
    G_ATOMICRMW_UMAX	= 112,
    G_ATOMICRMW_UMIN	= 113,
    G_ATOMICRMW_FADD	= 114,
    G_ATOMICRMW_FSUB	= 115,
    G_ATOMICRMW_FMAX	= 116,
    G_ATOMICRMW_FMIN	= 117,
    G_ATOMICRMW_UINC_WRAP	= 118,
    G_ATOMICRMW_UDEC_WRAP	= 119,
    G_ATOMICRMW_USUB_COND	= 120,
    G_ATOMICRMW_USUB_SAT	= 121,
    G_FENCE	= 122,
    G_PREFETCH	= 123,
    G_BRCOND	= 124,
    G_BRINDIRECT	= 125,
    G_INVOKE_REGION_START	= 126,
    G_INTRINSIC	= 127,
    G_INTRINSIC_W_SIDE_EFFECTS	= 128,
    G_INTRINSIC_CONVERGENT	= 129,
    G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS	= 130,
    G_ANYEXT	= 131,
    G_TRUNC	= 132,
    G_CONSTANT	= 133,
    G_FCONSTANT	= 134,
    G_VASTART	= 135,
    G_VAARG	= 136,
    G_SEXT	= 137,
    G_SEXT_INREG	= 138,
    G_ZEXT	= 139,
    G_SHL	= 140,
    G_LSHR	= 141,
    G_ASHR	= 142,
    G_FSHL	= 143,
    G_FSHR	= 144,
    G_ROTR	= 145,
    G_ROTL	= 146,
    G_ICMP	= 147,
    G_FCMP	= 148,
    G_SCMP	= 149,
    G_UCMP	= 150,
    G_SELECT	= 151,
    G_UADDO	= 152,
    G_UADDE	= 153,
    G_USUBO	= 154,
    G_USUBE	= 155,
    G_SADDO	= 156,
    G_SADDE	= 157,
    G_SSUBO	= 158,
    G_SSUBE	= 159,
    G_UMULO	= 160,
    G_SMULO	= 161,
    G_UMULH	= 162,
    G_SMULH	= 163,
    G_UADDSAT	= 164,
    G_SADDSAT	= 165,
    G_USUBSAT	= 166,
    G_SSUBSAT	= 167,
    G_USHLSAT	= 168,
    G_SSHLSAT	= 169,
    G_SMULFIX	= 170,
    G_UMULFIX	= 171,
    G_SMULFIXSAT	= 172,
    G_UMULFIXSAT	= 173,
    G_SDIVFIX	= 174,
    G_UDIVFIX	= 175,
    G_SDIVFIXSAT	= 176,
    G_UDIVFIXSAT	= 177,
    G_FADD	= 178,
    G_FSUB	= 179,
    G_FMUL	= 180,
    G_FMA	= 181,
    G_FMAD	= 182,
    G_FDIV	= 183,
    G_FREM	= 184,
    G_FPOW	= 185,
    G_FPOWI	= 186,
    G_FEXP	= 187,
    G_FEXP2	= 188,
    G_FEXP10	= 189,
    G_FLOG	= 190,
    G_FLOG2	= 191,
    G_FLOG10	= 192,
    G_FLDEXP	= 193,
    G_FFREXP	= 194,
    G_FNEG	= 195,
    G_FPEXT	= 196,
    G_FPTRUNC	= 197,
    G_FPTOSI	= 198,
    G_FPTOUI	= 199,
    G_SITOFP	= 200,
    G_UITOFP	= 201,
    G_FPTOSI_SAT	= 202,
    G_FPTOUI_SAT	= 203,
    G_FABS	= 204,
    G_FCOPYSIGN	= 205,
    G_IS_FPCLASS	= 206,
    G_FCANONICALIZE	= 207,
    G_FMINNUM	= 208,
    G_FMAXNUM	= 209,
    G_FMINNUM_IEEE	= 210,
    G_FMAXNUM_IEEE	= 211,
    G_FMINIMUM	= 212,
    G_FMAXIMUM	= 213,
    G_GET_FPENV	= 214,
    G_SET_FPENV	= 215,
    G_RESET_FPENV	= 216,
    G_GET_FPMODE	= 217,
    G_SET_FPMODE	= 218,
    G_RESET_FPMODE	= 219,
    G_PTR_ADD	= 220,
    G_PTRMASK	= 221,
    G_SMIN	= 222,
    G_SMAX	= 223,
    G_UMIN	= 224,
    G_UMAX	= 225,
    G_ABS	= 226,
    G_LROUND	= 227,
    G_LLROUND	= 228,
    G_BR	= 229,
    G_BRJT	= 230,
    G_VSCALE	= 231,
    G_INSERT_SUBVECTOR	= 232,
    G_EXTRACT_SUBVECTOR	= 233,
    G_INSERT_VECTOR_ELT	= 234,
    G_EXTRACT_VECTOR_ELT	= 235,
    G_SHUFFLE_VECTOR	= 236,
    G_SPLAT_VECTOR	= 237,
    G_STEP_VECTOR	= 238,
    G_VECTOR_COMPRESS	= 239,
    G_CTTZ	= 240,
    G_CTTZ_ZERO_UNDEF	= 241,
    G_CTLZ	= 242,
    G_CTLZ_ZERO_UNDEF	= 243,
    G_CTPOP	= 244,
    G_BSWAP	= 245,
    G_BITREVERSE	= 246,
    G_FCEIL	= 247,
    G_FCOS	= 248,
    G_FSIN	= 249,
    G_FSINCOS	= 250,
    G_FTAN	= 251,
    G_FACOS	= 252,
    G_FASIN	= 253,
    G_FATAN	= 254,
    G_FATAN2	= 255,
    G_FCOSH	= 256,
    G_FSINH	= 257,
    G_FTANH	= 258,
    G_FSQRT	= 259,
    G_FFLOOR	= 260,
    G_FRINT	= 261,
    G_FNEARBYINT	= 262,
    G_ADDRSPACE_CAST	= 263,
    G_BLOCK_ADDR	= 264,
    G_JUMP_TABLE	= 265,
    G_DYN_STACKALLOC	= 266,
    G_STACKSAVE	= 267,
    G_STACKRESTORE	= 268,
    G_STRICT_FADD	= 269,
    G_STRICT_FSUB	= 270,
    G_STRICT_FMUL	= 271,
    G_STRICT_FDIV	= 272,
    G_STRICT_FREM	= 273,
    G_STRICT_FMA	= 274,
    G_STRICT_FSQRT	= 275,
    G_STRICT_FLDEXP	= 276,
    G_READ_REGISTER	= 277,
    G_WRITE_REGISTER	= 278,
    G_MEMCPY	= 279,
    G_MEMCPY_INLINE	= 280,
    G_MEMMOVE	= 281,
    G_MEMSET	= 282,
    G_BZERO	= 283,
    G_TRAP	= 284,
    G_DEBUGTRAP	= 285,
    G_UBSANTRAP	= 286,
    G_VECREDUCE_SEQ_FADD	= 287,
    G_VECREDUCE_SEQ_FMUL	= 288,
    G_VECREDUCE_FADD	= 289,
    G_VECREDUCE_FMUL	= 290,
    G_VECREDUCE_FMAX	= 291,
    G_VECREDUCE_FMIN	= 292,
    G_VECREDUCE_FMAXIMUM	= 293,
    G_VECREDUCE_FMINIMUM	= 294,
    G_VECREDUCE_ADD	= 295,
    G_VECREDUCE_MUL	= 296,
    G_VECREDUCE_AND	= 297,
    G_VECREDUCE_OR	= 298,
    G_VECREDUCE_XOR	= 299,
    G_VECREDUCE_SMAX	= 300,
    G_VECREDUCE_SMIN	= 301,
    G_VECREDUCE_UMAX	= 302,
    G_VECREDUCE_UMIN	= 303,
    G_SBFX	= 304,
    G_UBFX	= 305,
    ADD	= 306,
    INSTRUCTION_LIST_END = 307
  };

} // end namespace llvm::Sim
#endif // GET_INSTRINFO_ENUM

#ifdef GET_INSTRINFO_SCHED_ENUM
#undef GET_INSTRINFO_SCHED_ENUM
namespace llvm::Sim::Sched {

  enum {
    NoInstrModel	= 0,
    SCHED_LIST_END = 1
  };
} // end namespace llvm::Sim::Sched
#endif // GET_INSTRINFO_SCHED_ENUM

#if defined(GET_INSTRINFO_MC_DESC) || defined(GET_INSTRINFO_CTOR_DTOR)
namespace llvm {

struct SimInstrTable {
  MCInstrDesc Insts[307];
  static_assert(alignof(MCInstrDesc) >= alignof(MCOperandInfo), "Unwanted padding between Insts and OperandInfo");
  MCOperandInfo OperandInfo[155];
  static_assert(alignof(MCOperandInfo) >= alignof(MCPhysReg), "Unwanted padding between OperandInfo and ImplicitOps");
  MCPhysReg ImplicitOps[1];
};

} // end namespace llvm
#endif // defined(GET_INSTRINFO_MC_DESC) || defined(GET_INSTRINFO_CTOR_DTOR)

#ifdef GET_INSTRINFO_MC_DESC
#undef GET_INSTRINFO_MC_DESC
namespace llvm {

static_assert(sizeof(MCOperandInfo) % sizeof(MCPhysReg) == 0);
static constexpr unsigned SimImpOpBase = sizeof SimInstrTable::OperandInfo / (sizeof(MCPhysReg));

extern const SimInstrTable SimDescs = {
  {
    { 306,	3,	1,	4,	0,	0,	0,	SimImpOpBase + 0,	152,	0|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #306 = ADD
    { 305,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	148,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #305 = G_UBFX
    { 304,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	148,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #304 = G_SBFX
    { 303,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #303 = G_VECREDUCE_UMIN
    { 302,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #302 = G_VECREDUCE_UMAX
    { 301,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #301 = G_VECREDUCE_SMIN
    { 300,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #300 = G_VECREDUCE_SMAX
    { 299,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #299 = G_VECREDUCE_XOR
    { 298,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #298 = G_VECREDUCE_OR
    { 297,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #297 = G_VECREDUCE_AND
    { 296,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #296 = G_VECREDUCE_MUL
    { 295,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #295 = G_VECREDUCE_ADD
    { 294,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #294 = G_VECREDUCE_FMINIMUM
    { 293,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #293 = G_VECREDUCE_FMAXIMUM
    { 292,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #292 = G_VECREDUCE_FMIN
    { 291,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #291 = G_VECREDUCE_FMAX
    { 290,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #290 = G_VECREDUCE_FMUL
    { 289,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #289 = G_VECREDUCE_FADD
    { 288,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	131,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #288 = G_VECREDUCE_SEQ_FMUL
    { 287,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	131,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #287 = G_VECREDUCE_SEQ_FADD
    { 286,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #286 = G_UBSANTRAP
    { 285,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #285 = G_DEBUGTRAP
    { 284,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #284 = G_TRAP
    { 283,	3,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	58,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #283 = G_BZERO
    { 282,	4,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	144,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #282 = G_MEMSET
    { 281,	4,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	144,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #281 = G_MEMMOVE
    { 280,	3,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	131,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #280 = G_MEMCPY_INLINE
    { 279,	4,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	144,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #279 = G_MEMCPY
    { 278,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	142,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #278 = G_WRITE_REGISTER
    { 277,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #277 = G_READ_REGISTER
    { 276,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #276 = G_STRICT_FLDEXP
    { 275,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #275 = G_STRICT_FSQRT
    { 274,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	46,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #274 = G_STRICT_FMA
    { 273,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #273 = G_STRICT_FREM
    { 272,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #272 = G_STRICT_FDIV
    { 271,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #271 = G_STRICT_FMUL
    { 270,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #270 = G_STRICT_FSUB
    { 269,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayRaiseFPException)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #269 = G_STRICT_FADD
    { 268,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #268 = G_STACKRESTORE
    { 267,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #267 = G_STACKSAVE
    { 266,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	69,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #266 = G_DYN_STACKALLOC
    { 265,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #265 = G_JUMP_TABLE
    { 264,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #264 = G_BLOCK_ADDR
    { 263,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #263 = G_ADDRSPACE_CAST
    { 262,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #262 = G_FNEARBYINT
    { 261,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #261 = G_FRINT
    { 260,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #260 = G_FFLOOR
    { 259,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #259 = G_FSQRT
    { 258,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #258 = G_FTANH
    { 257,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #257 = G_FSINH
    { 256,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #256 = G_FCOSH
    { 255,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #255 = G_FATAN2
    { 254,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #254 = G_FATAN
    { 253,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #253 = G_FASIN
    { 252,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #252 = G_FACOS
    { 251,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #251 = G_FTAN
    { 250,	3,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #250 = G_FSINCOS
    { 249,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #249 = G_FSIN
    { 248,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #248 = G_FCOS
    { 247,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #247 = G_FCEIL
    { 246,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #246 = G_BITREVERSE
    { 245,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #245 = G_BSWAP
    { 244,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #244 = G_CTPOP
    { 243,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #243 = G_CTLZ_ZERO_UNDEF
    { 242,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #242 = G_CTLZ
    { 241,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #241 = G_CTTZ_ZERO_UNDEF
    { 240,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #240 = G_CTTZ
    { 239,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	138,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #239 = G_VECTOR_COMPRESS
    { 238,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #238 = G_STEP_VECTOR
    { 237,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #237 = G_SPLAT_VECTOR
    { 236,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	134,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #236 = G_SHUFFLE_VECTOR
    { 235,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	131,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #235 = G_EXTRACT_VECTOR_ELT
    { 234,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	127,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #234 = G_INSERT_VECTOR_ELT
    { 233,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	58,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #233 = G_EXTRACT_SUBVECTOR
    { 232,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	63,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #232 = G_INSERT_SUBVECTOR
    { 231,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #231 = G_VSCALE
    { 230,	3,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	124,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Branch)|(1ULL<<MCID::IndirectBranch)|(1ULL<<MCID::Barrier)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #230 = G_BRJT
    { 229,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Branch)|(1ULL<<MCID::Barrier)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #229 = G_BR
    { 228,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #228 = G_LLROUND
    { 227,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #227 = G_LROUND
    { 226,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #226 = G_ABS
    { 225,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #225 = G_UMAX
    { 224,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #224 = G_UMIN
    { 223,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #223 = G_SMAX
    { 222,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #222 = G_SMIN
    { 221,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #221 = G_PTRMASK
    { 220,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #220 = G_PTR_ADD
    { 219,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #219 = G_RESET_FPMODE
    { 218,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #218 = G_SET_FPMODE
    { 217,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #217 = G_GET_FPMODE
    { 216,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #216 = G_RESET_FPENV
    { 215,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #215 = G_SET_FPENV
    { 214,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #214 = G_GET_FPENV
    { 213,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #213 = G_FMAXIMUM
    { 212,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #212 = G_FMINIMUM
    { 211,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #211 = G_FMAXNUM_IEEE
    { 210,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #210 = G_FMINNUM_IEEE
    { 209,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #209 = G_FMAXNUM
    { 208,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #208 = G_FMINNUM
    { 207,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #207 = G_FCANONICALIZE
    { 206,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	98,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #206 = G_IS_FPCLASS
    { 205,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #205 = G_FCOPYSIGN
    { 204,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #204 = G_FABS
    { 203,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #203 = G_FPTOUI_SAT
    { 202,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #202 = G_FPTOSI_SAT
    { 201,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #201 = G_UITOFP
    { 200,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #200 = G_SITOFP
    { 199,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #199 = G_FPTOUI
    { 198,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #198 = G_FPTOSI
    { 197,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #197 = G_FPTRUNC
    { 196,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #196 = G_FPEXT
    { 195,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #195 = G_FNEG
    { 194,	3,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #194 = G_FFREXP
    { 193,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #193 = G_FLDEXP
    { 192,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #192 = G_FLOG10
    { 191,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #191 = G_FLOG2
    { 190,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #190 = G_FLOG
    { 189,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #189 = G_FEXP10
    { 188,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #188 = G_FEXP2
    { 187,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #187 = G_FEXP
    { 186,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #186 = G_FPOWI
    { 185,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #185 = G_FPOW
    { 184,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #184 = G_FREM
    { 183,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #183 = G_FDIV
    { 182,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	46,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #182 = G_FMAD
    { 181,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	46,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #181 = G_FMA
    { 180,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #180 = G_FMUL
    { 179,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #179 = G_FSUB
    { 178,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #178 = G_FADD
    { 177,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #177 = G_UDIVFIXSAT
    { 176,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #176 = G_SDIVFIXSAT
    { 175,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #175 = G_UDIVFIX
    { 174,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #174 = G_SDIVFIX
    { 173,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #173 = G_UMULFIXSAT
    { 172,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #172 = G_SMULFIXSAT
    { 171,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #171 = G_UMULFIX
    { 170,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	120,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #170 = G_SMULFIX
    { 169,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #169 = G_SSHLSAT
    { 168,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #168 = G_USHLSAT
    { 167,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #167 = G_SSUBSAT
    { 166,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #166 = G_USUBSAT
    { 165,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #165 = G_SADDSAT
    { 164,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #164 = G_UADDSAT
    { 163,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #163 = G_SMULH
    { 162,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #162 = G_UMULH
    { 161,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #161 = G_SMULO
    { 160,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #160 = G_UMULO
    { 159,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	115,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #159 = G_SSUBE
    { 158,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #158 = G_SSUBO
    { 157,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	115,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #157 = G_SADDE
    { 156,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #156 = G_SADDO
    { 155,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	115,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #155 = G_USUBE
    { 154,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #154 = G_USUBO
    { 153,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	115,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #153 = G_UADDE
    { 152,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #152 = G_UADDO
    { 151,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #151 = G_SELECT
    { 150,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	112,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #150 = G_UCMP
    { 149,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	112,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #149 = G_SCMP
    { 148,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	108,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #148 = G_FCMP
    { 147,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	108,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #147 = G_ICMP
    { 146,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #146 = G_ROTL
    { 145,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #145 = G_ROTR
    { 144,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	104,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #144 = G_FSHR
    { 143,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	104,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #143 = G_FSHL
    { 142,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #142 = G_ASHR
    { 141,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #141 = G_LSHR
    { 140,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	101,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #140 = G_SHL
    { 139,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #139 = G_ZEXT
    { 138,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	40,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #138 = G_SEXT_INREG
    { 137,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #137 = G_SEXT
    { 136,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	98,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #136 = G_VAARG
    { 135,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #135 = G_VASTART
    { 134,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #134 = G_FCONSTANT
    { 133,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #133 = G_CONSTANT
    { 132,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #132 = G_TRUNC
    { 131,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #131 = G_ANYEXT
    { 130,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #130 = G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS
    { 129,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #129 = G_INTRINSIC_CONVERGENT
    { 128,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #128 = G_INTRINSIC_W_SIDE_EFFECTS
    { 127,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #127 = G_INTRINSIC
    { 126,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #126 = G_INVOKE_REGION_START
    { 125,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Branch)|(1ULL<<MCID::IndirectBranch)|(1ULL<<MCID::Barrier)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #125 = G_BRINDIRECT
    { 124,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Branch)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #124 = G_BRCOND
    { 123,	4,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	94,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #123 = G_PREFETCH
    { 122,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	21,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #122 = G_FENCE
    { 121,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #121 = G_ATOMICRMW_USUB_SAT
    { 120,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #120 = G_ATOMICRMW_USUB_COND
    { 119,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #119 = G_ATOMICRMW_UDEC_WRAP
    { 118,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #118 = G_ATOMICRMW_UINC_WRAP
    { 117,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #117 = G_ATOMICRMW_FMIN
    { 116,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #116 = G_ATOMICRMW_FMAX
    { 115,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #115 = G_ATOMICRMW_FSUB
    { 114,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #114 = G_ATOMICRMW_FADD
    { 113,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #113 = G_ATOMICRMW_UMIN
    { 112,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #112 = G_ATOMICRMW_UMAX
    { 111,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #111 = G_ATOMICRMW_MIN
    { 110,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #110 = G_ATOMICRMW_MAX
    { 109,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #109 = G_ATOMICRMW_XOR
    { 108,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #108 = G_ATOMICRMW_OR
    { 107,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #107 = G_ATOMICRMW_NAND
    { 106,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #106 = G_ATOMICRMW_AND
    { 105,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #105 = G_ATOMICRMW_SUB
    { 104,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #104 = G_ATOMICRMW_ADD
    { 103,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	91,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #103 = G_ATOMICRMW_XCHG
    { 102,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	87,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #102 = G_ATOMIC_CMPXCHG
    { 101,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	82,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #101 = G_ATOMIC_CMPXCHG_WITH_SUCCESS
    { 100,	5,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	77,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #100 = G_INDEXED_STORE
    { 99,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #99 = G_STORE
    { 98,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	72,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #98 = G_INDEXED_ZEXTLOAD
    { 97,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	72,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #97 = G_INDEXED_SEXTLOAD
    { 96,	5,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	72,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #96 = G_INDEXED_LOAD
    { 95,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #95 = G_ZEXTLOAD
    { 94,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #94 = G_SEXTLOAD
    { 93,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #93 = G_LOAD
    { 92,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #92 = G_READSTEADYCOUNTER
    { 91,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #91 = G_READCYCLECOUNTER
    { 90,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #90 = G_INTRINSIC_ROUNDEVEN
    { 89,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #89 = G_INTRINSIC_LLRINT
    { 88,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #88 = G_INTRINSIC_LRINT
    { 87,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #87 = G_INTRINSIC_ROUND
    { 86,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #86 = G_INTRINSIC_TRUNC
    { 85,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	69,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #85 = G_INTRINSIC_FPTRUNC_ROUND
    { 84,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #84 = G_CONSTANT_FOLD_BARRIER
    { 83,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	67,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #83 = G_FREEZE
    { 82,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #82 = G_BITCAST
    { 81,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #81 = G_INTTOPTR
    { 80,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #80 = G_PTRTOINT
    { 79,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #79 = G_CONCAT_VECTORS
    { 78,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #78 = G_BUILD_VECTOR_TRUNC
    { 77,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #77 = G_BUILD_VECTOR
    { 76,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #76 = G_MERGE_VALUES
    { 75,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	63,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #75 = G_INSERT
    { 74,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	61,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #74 = G_UNMERGE_VALUES
    { 73,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	58,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #73 = G_EXTRACT
    { 72,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #72 = G_CONSTANT_POOL
    { 71,	5,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	53,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #71 = G_PTRAUTH_GLOBAL_VALUE
    { 70,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #70 = G_GLOBAL_VALUE
    { 69,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	51,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #69 = G_FRAME_INDEX
    { 68,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #68 = G_PHI
    { 67,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	50,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #67 = G_IMPLICIT_DEF
    { 66,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #66 = G_ABDU
    { 65,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #65 = G_ABDS
    { 64,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #64 = G_XOR
    { 63,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #63 = G_OR
    { 62,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #62 = G_AND
    { 61,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	46,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #61 = G_UDIVREM
    { 60,	4,	2,	0,	0,	0,	0,	SimImpOpBase + 0,	46,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #60 = G_SDIVREM
    { 59,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #59 = G_UREM
    { 58,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #58 = G_SREM
    { 57,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #57 = G_UDIV
    { 56,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #56 = G_SDIV
    { 55,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #55 = G_MUL
    { 54,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #54 = G_SUB
    { 53,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	43,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Commutable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #53 = G_ADD
    { 52,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	40,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #52 = G_ASSERT_ALIGN
    { 51,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	40,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #51 = G_ASSERT_ZEXT
    { 50,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	40,	0|(1ULL<<MCID::PreISelOpcode)|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #50 = G_ASSERT_SEXT
    { 49,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #49 = CONVERGENCECTRL_GLUE
    { 48,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	13,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #48 = CONVERGENCECTRL_LOOP
    { 47,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #47 = CONVERGENCECTRL_ANCHOR
    { 46,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq)|(1ULL<<MCID::Convergent), 0x0ULL },  // Inst #46 = CONVERGENCECTRL_ENTRY
    { 45,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #45 = JUMP_TABLE_DEBUG_INFO
    { 44,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #44 = MEMBARRIER
    { 43,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #43 = FAKE_USE
    { 42,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #42 = ICALL_BRANCH_FUNNEL
    { 41,	3,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	37,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #41 = PATCHABLE_TYPED_EVENT_CALL
    { 40,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	35,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #40 = PATCHABLE_EVENT_CALL
    { 39,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Return)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #39 = PATCHABLE_TAIL_CALL
    { 38,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #38 = PATCHABLE_FUNCTION_EXIT
    { 37,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Return)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #37 = PATCHABLE_RET
    { 36,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #36 = PATCHABLE_FUNCTION_ENTER
    { 35,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #35 = PATCHABLE_OP
    { 34,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Branch)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::Terminator)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #34 = FAULTING_OP
    { 33,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	33,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #33 = LOCAL_ESCAPE
    { 32,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #32 = STATEPOINT
    { 31,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	30,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #31 = PREALLOCATED_ARG
    { 30,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #30 = PREALLOCATED_SETUP
    { 29,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	29,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::Rematerializable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #29 = LOAD_STACK_GUARD
    { 28,	6,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	23,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #28 = PATCHPOINT
    { 27,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::MayStore)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #27 = FENTRY_CALL
    { 26,	2,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	21,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Call)|(1ULL<<MCID::MayLoad)|(1ULL<<MCID::UsesCustomInserter)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #26 = STACKMAP
    { 25,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	19,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #25 = ARITH_FENCE
    { 24,	4,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	15,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #24 = PSEUDO_PROBE
    { 23,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #23 = LIFETIME_END
    { 22,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #22 = LIFETIME_START
    { 21,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #21 = BUNDLE
    { 20,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	13,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::CheapAsAMove)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #20 = COPY
    { 19,	2,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	13,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::CheapAsAMove)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #19 = REG_SEQUENCE
    { 18,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #18 = DBG_LABEL
    { 17,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #17 = DBG_PHI
    { 16,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #16 = DBG_INSTR_REF
    { 15,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #15 = DBG_VALUE_LIST
    { 14,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #14 = DBG_VALUE
    { 13,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	2,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::CheapAsAMove)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #13 = COPY_TO_REGCLASS
    { 12,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	9,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #12 = SUBREG_TO_REG
    { 11,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #11 = INIT_UNDEF
    { 10,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Rematerializable)|(1ULL<<MCID::CheapAsAMove)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #10 = IMPLICIT_DEF
    { 9,	4,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	5,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #9 = INSERT_SUBREG
    { 8,	3,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	2,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #8 = EXTRACT_SUBREG
    { 7,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #7 = KILL
    { 6,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::NotDuplicable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #6 = ANNOTATION_LABEL
    { 5,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::NotDuplicable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #5 = GC_LABEL
    { 4,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::NotDuplicable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #4 = EH_LABEL
    { 3,	1,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Meta)|(1ULL<<MCID::NotDuplicable)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #3 = CFI_INSTRUCTION
    { 2,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::UnmodeledSideEffects)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #2 = INLINEASM_BR
    { 1,	0,	0,	0,	0,	0,	0,	SimImpOpBase + 0,	1,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #1 = INLINEASM
    { 0,	1,	1,	0,	0,	0,	0,	SimImpOpBase + 0,	0,	0|(1ULL<<MCID::Pseudo)|(1ULL<<MCID::Variadic)|(1ULL<<MCID::ExtraSrcRegAllocReq)|(1ULL<<MCID::ExtraDefRegAllocReq), 0x0ULL },  // Inst #0 = PHI
  }, {
    /* 0 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 1 */
    /* 1 */ { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 2 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 5 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, MCOI_TIED_TO(0) }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 9 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 13 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 15 */ { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 19 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, MCOI_TIED_TO(0) },
    /* 21 */ { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 23 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 29 */ { 0, 0|(1<<MCOI::LookupPtrRegClass), MCOI::OPERAND_UNKNOWN, 0 },
    /* 30 */ { 0, 0|(1<<MCOI::LookupPtrRegClass), MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 33 */ { 0, 0|(1<<MCOI::LookupPtrRegClass), MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 35 */ { 0, 0|(1<<MCOI::LookupPtrRegClass), MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 37 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { 0, 0|(1<<MCOI::LookupPtrRegClass), MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 40 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_IMM_0, 0 },
    /* 43 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 46 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 50 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 51 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 53 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 58 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_IMM_0, 0 },
    /* 61 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 63 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_IMM_0, 0 },
    /* 67 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 69 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 72 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 77 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 82 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 87 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 91 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 94 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 }, { -1, 0, MCOI::OPERAND_IMMEDIATE, 0 },
    /* 98 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 101 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 104 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 108 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 112 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 115 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 120 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_IMM_0, 0 },
    /* 124 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 127 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 },
    /* 131 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 },
    /* 134 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_UNKNOWN, 0 },
    /* 138 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 142 */ { -1, 0, MCOI::OPERAND_UNKNOWN, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 },
    /* 144 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_2, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_IMM_0, 0 },
    /* 148 */ { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_0, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 }, { -1, 0, MCOI::OPERAND_GENERIC_1, 0 },
    /* 152 */ { Sim::GPRRegClassID, 0, MCOI::OPERAND_REGISTER, 0 }, { Sim::GPRRegClassID, 0, MCOI::OPERAND_REGISTER, 0 }, { Sim::GPRRegClassID, 0, MCOI::OPERAND_REGISTER, 0 },
  }, {
    /* 0 */
  }
};


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif
extern const char SimInstrNameData[] = {
  /* 0 */ "G_FLOG10\000"
  /* 9 */ "G_FEXP10\000"
  /* 18 */ "G_FLOG2\000"
  /* 26 */ "G_FATAN2\000"
  /* 35 */ "G_FEXP2\000"
  /* 43 */ "G_FMA\000"
  /* 49 */ "G_STRICT_FMA\000"
  /* 62 */ "G_FSUB\000"
  /* 69 */ "G_STRICT_FSUB\000"
  /* 83 */ "G_ATOMICRMW_FSUB\000"
  /* 100 */ "G_SUB\000"
  /* 106 */ "G_ATOMICRMW_SUB\000"
  /* 122 */ "G_INTRINSIC\000"
  /* 134 */ "G_FPTRUNC\000"
  /* 144 */ "G_INTRINSIC_TRUNC\000"
  /* 162 */ "G_TRUNC\000"
  /* 170 */ "G_BUILD_VECTOR_TRUNC\000"
  /* 191 */ "G_DYN_STACKALLOC\000"
  /* 208 */ "G_FMAD\000"
  /* 215 */ "G_INDEXED_SEXTLOAD\000"
  /* 234 */ "G_SEXTLOAD\000"
  /* 245 */ "G_INDEXED_ZEXTLOAD\000"
  /* 264 */ "G_ZEXTLOAD\000"
  /* 275 */ "G_INDEXED_LOAD\000"
  /* 290 */ "G_LOAD\000"
  /* 297 */ "G_VECREDUCE_FADD\000"
  /* 314 */ "G_FADD\000"
  /* 321 */ "G_VECREDUCE_SEQ_FADD\000"
  /* 342 */ "G_STRICT_FADD\000"
  /* 356 */ "G_ATOMICRMW_FADD\000"
  /* 373 */ "G_VECREDUCE_ADD\000"
  /* 389 */ "G_ADD\000"
  /* 395 */ "G_PTR_ADD\000"
  /* 405 */ "G_ATOMICRMW_ADD\000"
  /* 421 */ "G_ATOMICRMW_NAND\000"
  /* 438 */ "G_VECREDUCE_AND\000"
  /* 454 */ "G_AND\000"
  /* 460 */ "G_ATOMICRMW_AND\000"
  /* 476 */ "LIFETIME_END\000"
  /* 489 */ "G_BRCOND\000"
  /* 498 */ "G_ATOMICRMW_USUB_COND\000"
  /* 520 */ "G_LLROUND\000"
  /* 530 */ "G_LROUND\000"
  /* 539 */ "G_INTRINSIC_ROUND\000"
  /* 557 */ "G_INTRINSIC_FPTRUNC_ROUND\000"
  /* 583 */ "LOAD_STACK_GUARD\000"
  /* 600 */ "PSEUDO_PROBE\000"
  /* 613 */ "G_SSUBE\000"
  /* 621 */ "G_USUBE\000"
  /* 629 */ "G_FENCE\000"
  /* 637 */ "ARITH_FENCE\000"
  /* 649 */ "REG_SEQUENCE\000"
  /* 662 */ "G_SADDE\000"
  /* 670 */ "G_UADDE\000"
  /* 678 */ "G_GET_FPMODE\000"
  /* 691 */ "G_RESET_FPMODE\000"
  /* 706 */ "G_SET_FPMODE\000"
  /* 719 */ "G_FMINNUM_IEEE\000"
  /* 734 */ "G_FMAXNUM_IEEE\000"
  /* 749 */ "G_VSCALE\000"
  /* 758 */ "G_JUMP_TABLE\000"
  /* 771 */ "BUNDLE\000"
  /* 778 */ "G_MEMCPY_INLINE\000"
  /* 794 */ "LOCAL_ESCAPE\000"
  /* 807 */ "G_STACKRESTORE\000"
  /* 822 */ "G_INDEXED_STORE\000"
  /* 838 */ "G_STORE\000"
  /* 846 */ "G_BITREVERSE\000"
  /* 859 */ "FAKE_USE\000"
  /* 868 */ "DBG_VALUE\000"
  /* 878 */ "G_GLOBAL_VALUE\000"
  /* 893 */ "G_PTRAUTH_GLOBAL_VALUE\000"
  /* 916 */ "CONVERGENCECTRL_GLUE\000"
  /* 937 */ "G_STACKSAVE\000"
  /* 949 */ "G_MEMMOVE\000"
  /* 959 */ "G_FREEZE\000"
  /* 968 */ "G_FCANONICALIZE\000"
  /* 984 */ "G_CTLZ_ZERO_UNDEF\000"
  /* 1002 */ "G_CTTZ_ZERO_UNDEF\000"
  /* 1020 */ "INIT_UNDEF\000"
  /* 1031 */ "G_IMPLICIT_DEF\000"
  /* 1046 */ "DBG_INSTR_REF\000"
  /* 1060 */ "G_FNEG\000"
  /* 1067 */ "EXTRACT_SUBREG\000"
  /* 1082 */ "INSERT_SUBREG\000"
  /* 1096 */ "G_SEXT_INREG\000"
  /* 1109 */ "SUBREG_TO_REG\000"
  /* 1123 */ "G_ATOMIC_CMPXCHG\000"
  /* 1140 */ "G_ATOMICRMW_XCHG\000"
  /* 1157 */ "G_FLOG\000"
  /* 1164 */ "G_VAARG\000"
  /* 1172 */ "PREALLOCATED_ARG\000"
  /* 1189 */ "G_PREFETCH\000"
  /* 1200 */ "G_SMULH\000"
  /* 1208 */ "G_UMULH\000"
  /* 1216 */ "G_FTANH\000"
  /* 1224 */ "G_FSINH\000"
  /* 1232 */ "G_FCOSH\000"
  /* 1240 */ "DBG_PHI\000"
  /* 1248 */ "G_FPTOSI\000"
  /* 1257 */ "G_FPTOUI\000"
  /* 1266 */ "G_FPOWI\000"
  /* 1274 */ "G_PTRMASK\000"
  /* 1284 */ "GC_LABEL\000"
  /* 1293 */ "DBG_LABEL\000"
  /* 1303 */ "EH_LABEL\000"
  /* 1312 */ "ANNOTATION_LABEL\000"
  /* 1329 */ "ICALL_BRANCH_FUNNEL\000"
  /* 1349 */ "G_FSHL\000"
  /* 1356 */ "G_SHL\000"
  /* 1362 */ "G_FCEIL\000"
  /* 1370 */ "PATCHABLE_TAIL_CALL\000"
  /* 1390 */ "PATCHABLE_TYPED_EVENT_CALL\000"
  /* 1417 */ "PATCHABLE_EVENT_CALL\000"
  /* 1438 */ "FENTRY_CALL\000"
  /* 1450 */ "KILL\000"
  /* 1455 */ "G_CONSTANT_POOL\000"
  /* 1471 */ "G_ROTL\000"
  /* 1478 */ "G_VECREDUCE_FMUL\000"
  /* 1495 */ "G_FMUL\000"
  /* 1502 */ "G_VECREDUCE_SEQ_FMUL\000"
  /* 1523 */ "G_STRICT_FMUL\000"
  /* 1537 */ "G_VECREDUCE_MUL\000"
  /* 1553 */ "G_MUL\000"
  /* 1559 */ "G_FREM\000"
  /* 1566 */ "G_STRICT_FREM\000"
  /* 1580 */ "G_SREM\000"
  /* 1587 */ "G_UREM\000"
  /* 1594 */ "G_SDIVREM\000"
  /* 1604 */ "G_UDIVREM\000"
  /* 1614 */ "INLINEASM\000"
  /* 1624 */ "G_VECREDUCE_FMINIMUM\000"
  /* 1645 */ "G_FMINIMUM\000"
  /* 1656 */ "G_VECREDUCE_FMAXIMUM\000"
  /* 1677 */ "G_FMAXIMUM\000"
  /* 1688 */ "G_FMINNUM\000"
  /* 1698 */ "G_FMAXNUM\000"
  /* 1708 */ "G_FATAN\000"
  /* 1716 */ "G_FTAN\000"
  /* 1723 */ "G_INTRINSIC_ROUNDEVEN\000"
  /* 1745 */ "G_ASSERT_ALIGN\000"
  /* 1760 */ "G_FCOPYSIGN\000"
  /* 1772 */ "G_VECREDUCE_FMIN\000"
  /* 1789 */ "G_ATOMICRMW_FMIN\000"
  /* 1806 */ "G_VECREDUCE_SMIN\000"
  /* 1823 */ "G_SMIN\000"
  /* 1830 */ "G_VECREDUCE_UMIN\000"
  /* 1847 */ "G_UMIN\000"
  /* 1854 */ "G_ATOMICRMW_UMIN\000"
  /* 1871 */ "G_ATOMICRMW_MIN\000"
  /* 1887 */ "G_FASIN\000"
  /* 1895 */ "G_FSIN\000"
  /* 1902 */ "CFI_INSTRUCTION\000"
  /* 1918 */ "G_SSUBO\000"
  /* 1926 */ "G_USUBO\000"
  /* 1934 */ "G_SADDO\000"
  /* 1942 */ "G_UADDO\000"
  /* 1950 */ "JUMP_TABLE_DEBUG_INFO\000"
  /* 1972 */ "G_SMULO\000"
  /* 1980 */ "G_UMULO\000"
  /* 1988 */ "G_BZERO\000"
  /* 1996 */ "STACKMAP\000"
  /* 2005 */ "G_DEBUGTRAP\000"
  /* 2017 */ "G_UBSANTRAP\000"
  /* 2029 */ "G_TRAP\000"
  /* 2036 */ "G_ATOMICRMW_UDEC_WRAP\000"
  /* 2058 */ "G_ATOMICRMW_UINC_WRAP\000"
  /* 2080 */ "G_BSWAP\000"
  /* 2088 */ "G_SITOFP\000"
  /* 2097 */ "G_UITOFP\000"
  /* 2106 */ "G_FCMP\000"
  /* 2113 */ "G_ICMP\000"
  /* 2120 */ "G_SCMP\000"
  /* 2127 */ "G_UCMP\000"
  /* 2134 */ "CONVERGENCECTRL_LOOP\000"
  /* 2155 */ "G_CTPOP\000"
  /* 2163 */ "PATCHABLE_OP\000"
  /* 2176 */ "FAULTING_OP\000"
  /* 2188 */ "PREALLOCATED_SETUP\000"
  /* 2207 */ "G_FLDEXP\000"
  /* 2216 */ "G_STRICT_FLDEXP\000"
  /* 2232 */ "G_FEXP\000"
  /* 2239 */ "G_FFREXP\000"
  /* 2248 */ "G_BR\000"
  /* 2253 */ "INLINEASM_BR\000"
  /* 2266 */ "G_BLOCK_ADDR\000"
  /* 2279 */ "MEMBARRIER\000"
  /* 2290 */ "G_CONSTANT_FOLD_BARRIER\000"
  /* 2314 */ "PATCHABLE_FUNCTION_ENTER\000"
  /* 2339 */ "G_READCYCLECOUNTER\000"
  /* 2358 */ "G_READSTEADYCOUNTER\000"
  /* 2378 */ "G_READ_REGISTER\000"
  /* 2394 */ "G_WRITE_REGISTER\000"
  /* 2411 */ "G_ASHR\000"
  /* 2418 */ "G_FSHR\000"
  /* 2425 */ "G_LSHR\000"
  /* 2432 */ "CONVERGENCECTRL_ANCHOR\000"
  /* 2455 */ "G_FFLOOR\000"
  /* 2464 */ "G_EXTRACT_SUBVECTOR\000"
  /* 2484 */ "G_INSERT_SUBVECTOR\000"
  /* 2503 */ "G_BUILD_VECTOR\000"
  /* 2518 */ "G_SHUFFLE_VECTOR\000"
  /* 2535 */ "G_STEP_VECTOR\000"
  /* 2549 */ "G_SPLAT_VECTOR\000"
  /* 2564 */ "G_VECREDUCE_XOR\000"
  /* 2580 */ "G_XOR\000"
  /* 2586 */ "G_ATOMICRMW_XOR\000"
  /* 2602 */ "G_VECREDUCE_OR\000"
  /* 2617 */ "G_OR\000"
  /* 2622 */ "G_ATOMICRMW_OR\000"
  /* 2637 */ "G_ROTR\000"
  /* 2644 */ "G_INTTOPTR\000"
  /* 2655 */ "G_FABS\000"
  /* 2662 */ "G_ABS\000"
  /* 2668 */ "G_ABDS\000"
  /* 2675 */ "G_UNMERGE_VALUES\000"
  /* 2692 */ "G_MERGE_VALUES\000"
  /* 2707 */ "G_FACOS\000"
  /* 2715 */ "G_FCOS\000"
  /* 2722 */ "G_FSINCOS\000"
  /* 2732 */ "G_CONCAT_VECTORS\000"
  /* 2749 */ "COPY_TO_REGCLASS\000"
  /* 2766 */ "G_IS_FPCLASS\000"
  /* 2779 */ "G_ATOMIC_CMPXCHG_WITH_SUCCESS\000"
  /* 2809 */ "G_VECTOR_COMPRESS\000"
  /* 2827 */ "G_INTRINSIC_W_SIDE_EFFECTS\000"
  /* 2854 */ "G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS\000"
  /* 2892 */ "G_SSUBSAT\000"
  /* 2902 */ "G_USUBSAT\000"
  /* 2912 */ "G_SADDSAT\000"
  /* 2922 */ "G_UADDSAT\000"
  /* 2932 */ "G_SSHLSAT\000"
  /* 2942 */ "G_USHLSAT\000"
  /* 2952 */ "G_SMULFIXSAT\000"
  /* 2965 */ "G_UMULFIXSAT\000"
  /* 2978 */ "G_SDIVFIXSAT\000"
  /* 2991 */ "G_UDIVFIXSAT\000"
  /* 3004 */ "G_ATOMICRMW_USUB_SAT\000"
  /* 3025 */ "G_FPTOSI_SAT\000"
  /* 3038 */ "G_FPTOUI_SAT\000"
  /* 3051 */ "G_EXTRACT\000"
  /* 3061 */ "G_SELECT\000"
  /* 3070 */ "G_BRINDIRECT\000"
  /* 3083 */ "PATCHABLE_RET\000"
  /* 3097 */ "G_MEMSET\000"
  /* 3106 */ "PATCHABLE_FUNCTION_EXIT\000"
  /* 3130 */ "G_BRJT\000"
  /* 3137 */ "G_EXTRACT_VECTOR_ELT\000"
  /* 3158 */ "G_INSERT_VECTOR_ELT\000"
  /* 3178 */ "G_FCONSTANT\000"
  /* 3190 */ "G_CONSTANT\000"
  /* 3201 */ "G_INTRINSIC_CONVERGENT\000"
  /* 3224 */ "STATEPOINT\000"
  /* 3235 */ "PATCHPOINT\000"
  /* 3246 */ "G_PTRTOINT\000"
  /* 3257 */ "G_FRINT\000"
  /* 3265 */ "G_INTRINSIC_LLRINT\000"
  /* 3284 */ "G_INTRINSIC_LRINT\000"
  /* 3302 */ "G_FNEARBYINT\000"
  /* 3315 */ "G_VASTART\000"
  /* 3325 */ "LIFETIME_START\000"
  /* 3340 */ "G_INVOKE_REGION_START\000"
  /* 3362 */ "G_INSERT\000"
  /* 3371 */ "G_FSQRT\000"
  /* 3379 */ "G_STRICT_FSQRT\000"
  /* 3394 */ "G_BITCAST\000"
  /* 3404 */ "G_ADDRSPACE_CAST\000"
  /* 3421 */ "DBG_VALUE_LIST\000"
  /* 3436 */ "G_FPEXT\000"
  /* 3444 */ "G_SEXT\000"
  /* 3451 */ "G_ASSERT_SEXT\000"
  /* 3465 */ "G_ANYEXT\000"
  /* 3474 */ "G_ZEXT\000"
  /* 3481 */ "G_ASSERT_ZEXT\000"
  /* 3495 */ "G_ABDU\000"
  /* 3502 */ "G_FDIV\000"
  /* 3509 */ "G_STRICT_FDIV\000"
  /* 3523 */ "G_SDIV\000"
  /* 3530 */ "G_UDIV\000"
  /* 3537 */ "G_GET_FPENV\000"
  /* 3549 */ "G_RESET_FPENV\000"
  /* 3563 */ "G_SET_FPENV\000"
  /* 3575 */ "G_FPOW\000"
  /* 3582 */ "G_VECREDUCE_FMAX\000"
  /* 3599 */ "G_ATOMICRMW_FMAX\000"
  /* 3616 */ "G_VECREDUCE_SMAX\000"
  /* 3633 */ "G_SMAX\000"
  /* 3640 */ "G_VECREDUCE_UMAX\000"
  /* 3657 */ "G_UMAX\000"
  /* 3664 */ "G_ATOMICRMW_UMAX\000"
  /* 3681 */ "G_ATOMICRMW_MAX\000"
  /* 3697 */ "G_FRAME_INDEX\000"
  /* 3711 */ "G_SBFX\000"
  /* 3718 */ "G_UBFX\000"
  /* 3725 */ "G_SMULFIX\000"
  /* 3735 */ "G_UMULFIX\000"
  /* 3745 */ "G_SDIVFIX\000"
  /* 3755 */ "G_UDIVFIX\000"
  /* 3765 */ "G_MEMCPY\000"
  /* 3774 */ "COPY\000"
  /* 3779 */ "CONVERGENCECTRL_ENTRY\000"
  /* 3801 */ "G_CTLZ\000"
  /* 3808 */ "G_CTTZ\000"
};
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

extern const unsigned SimInstrNameIndices[] = {
    1244U, 1614U, 2253U, 1902U, 1303U, 1284U, 1312U, 1450U, 
    1067U, 1082U, 1033U, 1020U, 1109U, 2749U, 868U, 3421U, 
    1046U, 1240U, 1293U, 649U, 3774U, 771U, 3325U, 476U, 
    600U, 637U, 1996U, 1438U, 3235U, 583U, 2188U, 1172U, 
    3224U, 794U, 2176U, 2163U, 2314U, 3083U, 3106U, 1370U, 
    1417U, 1390U, 1329U, 859U, 2279U, 1950U, 3779U, 2432U, 
    2134U, 916U, 3451U, 3481U, 1745U, 389U, 100U, 1553U, 
    3523U, 3530U, 1580U, 1587U, 1594U, 1604U, 454U, 2617U, 
    2580U, 2668U, 3495U, 1031U, 1242U, 3697U, 878U, 893U, 
    1455U, 3051U, 2675U, 3362U, 2692U, 2503U, 170U, 2732U, 
    3246U, 2644U, 3394U, 959U, 2290U, 557U, 144U, 539U, 
    3284U, 3265U, 1723U, 2339U, 2358U, 290U, 234U, 264U, 
    275U, 215U, 245U, 838U, 822U, 2779U, 1123U, 1140U, 
    405U, 106U, 460U, 421U, 2622U, 2586U, 3681U, 1871U, 
    3664U, 1854U, 356U, 83U, 3599U, 1789U, 2058U, 2036U, 
    498U, 3004U, 629U, 1189U, 489U, 3070U, 3340U, 122U, 
    2827U, 3201U, 2854U, 3465U, 162U, 3190U, 3178U, 3315U, 
    1164U, 3444U, 1096U, 3474U, 1356U, 2425U, 2411U, 1349U, 
    2418U, 2637U, 1471U, 2113U, 2106U, 2120U, 2127U, 3061U, 
    1942U, 670U, 1926U, 621U, 1934U, 662U, 1918U, 613U, 
    1980U, 1972U, 1208U, 1200U, 2922U, 2912U, 2902U, 2892U, 
    2942U, 2932U, 3725U, 3735U, 2952U, 2965U, 3745U, 3755U, 
    2978U, 2991U, 314U, 62U, 1495U, 43U, 208U, 3502U, 
    1559U, 3575U, 1266U, 2232U, 35U, 9U, 1157U, 18U, 
    0U, 2207U, 2239U, 1060U, 3436U, 134U, 1248U, 1257U, 
    2088U, 2097U, 3025U, 3038U, 2655U, 1760U, 2766U, 968U, 
    1688U, 1698U, 719U, 734U, 1645U, 1677U, 3537U, 3563U, 
    3549U, 678U, 706U, 691U, 395U, 1274U, 1823U, 3633U, 
    1847U, 3657U, 2662U, 530U, 520U, 2248U, 3130U, 749U, 
    2484U, 2464U, 3158U, 3137U, 2518U, 2549U, 2535U, 2809U, 
    3808U, 1002U, 3801U, 984U, 2155U, 2080U, 846U, 1362U, 
    2715U, 1895U, 2722U, 1716U, 2707U, 1887U, 1708U, 26U, 
    1232U, 1224U, 1216U, 3371U, 2455U, 3257U, 3302U, 3404U, 
    2266U, 758U, 191U, 937U, 807U, 342U, 69U, 1523U, 
    3509U, 1566U, 49U, 3379U, 2216U, 2378U, 2394U, 3765U, 
    778U, 949U, 3097U, 1988U, 2029U, 2005U, 2017U, 321U, 
    1502U, 297U, 1478U, 3582U, 1772U, 1656U, 1624U, 373U, 
    1537U, 438U, 2602U, 2564U, 3616U, 1806U, 3640U, 1830U, 
    3711U, 3718U, 310U, 
};

static inline void InitSimMCInstrInfo(MCInstrInfo *II) {
  II->InitMCInstrInfo(SimDescs.Insts, SimInstrNameIndices, SimInstrNameData, nullptr, nullptr, 307);
}

} // end namespace llvm
#endif // GET_INSTRINFO_MC_DESC

#ifdef GET_INSTRINFO_HEADER
#undef GET_INSTRINFO_HEADER
namespace llvm {
struct SimGenInstrInfo : public TargetInstrInfo {
  explicit SimGenInstrInfo(unsigned CFSetupOpcode = ~0u, unsigned CFDestroyOpcode = ~0u, unsigned CatchRetOpcode = ~0u, unsigned ReturnOpcode = ~0u);
  ~SimGenInstrInfo() override = default;

};
} // end namespace llvm
#endif // GET_INSTRINFO_HEADER

#ifdef GET_INSTRINFO_HELPER_DECLS
#undef GET_INSTRINFO_HELPER_DECLS


#endif // GET_INSTRINFO_HELPER_DECLS

#ifdef GET_INSTRINFO_HELPERS
#undef GET_INSTRINFO_HELPERS

#endif // GET_INSTRINFO_HELPERS

#ifdef GET_INSTRINFO_CTOR_DTOR
#undef GET_INSTRINFO_CTOR_DTOR
namespace llvm {
extern const SimInstrTable SimDescs;
extern const unsigned SimInstrNameIndices[];
extern const char SimInstrNameData[];
SimGenInstrInfo::SimGenInstrInfo(unsigned CFSetupOpcode, unsigned CFDestroyOpcode, unsigned CatchRetOpcode, unsigned ReturnOpcode)
  : TargetInstrInfo(CFSetupOpcode, CFDestroyOpcode, CatchRetOpcode, ReturnOpcode) {
  InitMCInstrInfo(SimDescs.Insts, SimInstrNameIndices, SimInstrNameData, nullptr, nullptr, 307);
}
} // end namespace llvm
#endif // GET_INSTRINFO_CTOR_DTOR

#ifdef GET_INSTRINFO_OPERAND_ENUM
#undef GET_INSTRINFO_OPERAND_ENUM
namespace llvm::Sim::OpName {
enum {
  OPERAND_LAST
};
} // end namespace llvm::Sim::OpName
#endif //GET_INSTRINFO_OPERAND_ENUM

#ifdef GET_INSTRINFO_NAMED_OPS
#undef GET_INSTRINFO_NAMED_OPS
namespace llvm::Sim {
LLVM_READONLY
int16_t getNamedOperandIdx(uint16_t Opcode, uint16_t NamedIdx) {
  return -1;
}
} // end namespace llvm::Sim
#endif //GET_INSTRINFO_NAMED_OPS

#ifdef GET_INSTRINFO_OPERAND_TYPES_ENUM
#undef GET_INSTRINFO_OPERAND_TYPES_ENUM
namespace llvm::Sim::OpTypes {
enum OperandType {
  f32imm = 0,
  f64imm = 1,
  i1imm = 2,
  i8imm = 3,
  i16imm = 4,
  i32imm = 5,
  i64imm = 6,
  ptype0 = 7,
  ptype1 = 8,
  ptype2 = 9,
  ptype3 = 10,
  ptype4 = 11,
  ptype5 = 12,
  type0 = 13,
  type1 = 14,
  type2 = 15,
  type3 = 16,
  type4 = 17,
  type5 = 18,
  untyped_imm_0 = 19,
  GPR = 20,
  OPERAND_TYPE_LIST_END
};
} // end namespace llvm::Sim::OpTypes
#endif // GET_INSTRINFO_OPERAND_TYPES_ENUM

#ifdef GET_INSTRINFO_OPERAND_TYPE
#undef GET_INSTRINFO_OPERAND_TYPE
namespace llvm::Sim {
LLVM_READONLY
static int getOperandType(uint16_t Opcode, uint16_t OpIdx) {
  static const uint16_t Offsets[] = {
    /* PHI */
    0,
    /* INLINEASM */
    1,
    /* INLINEASM_BR */
    1,
    /* CFI_INSTRUCTION */
    1,
    /* EH_LABEL */
    2,
    /* GC_LABEL */
    3,
    /* ANNOTATION_LABEL */
    4,
    /* KILL */
    5,
    /* EXTRACT_SUBREG */
    5,
    /* INSERT_SUBREG */
    8,
    /* IMPLICIT_DEF */
    12,
    /* INIT_UNDEF */
    13,
    /* SUBREG_TO_REG */
    14,
    /* COPY_TO_REGCLASS */
    18,
    /* DBG_VALUE */
    21,
    /* DBG_VALUE_LIST */
    21,
    /* DBG_INSTR_REF */
    21,
    /* DBG_PHI */
    21,
    /* DBG_LABEL */
    21,
    /* REG_SEQUENCE */
    22,
    /* COPY */
    24,
    /* BUNDLE */
    26,
    /* LIFETIME_START */
    26,
    /* LIFETIME_END */
    27,
    /* PSEUDO_PROBE */
    28,
    /* ARITH_FENCE */
    32,
    /* STACKMAP */
    34,
    /* FENTRY_CALL */
    36,
    /* PATCHPOINT */
    36,
    /* LOAD_STACK_GUARD */
    42,
    /* PREALLOCATED_SETUP */
    43,
    /* PREALLOCATED_ARG */
    44,
    /* STATEPOINT */
    47,
    /* LOCAL_ESCAPE */
    47,
    /* FAULTING_OP */
    49,
    /* PATCHABLE_OP */
    50,
    /* PATCHABLE_FUNCTION_ENTER */
    50,
    /* PATCHABLE_RET */
    50,
    /* PATCHABLE_FUNCTION_EXIT */
    50,
    /* PATCHABLE_TAIL_CALL */
    50,
    /* PATCHABLE_EVENT_CALL */
    50,
    /* PATCHABLE_TYPED_EVENT_CALL */
    52,
    /* ICALL_BRANCH_FUNNEL */
    55,
    /* FAKE_USE */
    55,
    /* MEMBARRIER */
    55,
    /* JUMP_TABLE_DEBUG_INFO */
    55,
    /* CONVERGENCECTRL_ENTRY */
    56,
    /* CONVERGENCECTRL_ANCHOR */
    57,
    /* CONVERGENCECTRL_LOOP */
    58,
    /* CONVERGENCECTRL_GLUE */
    60,
    /* G_ASSERT_SEXT */
    61,
    /* G_ASSERT_ZEXT */
    64,
    /* G_ASSERT_ALIGN */
    67,
    /* G_ADD */
    70,
    /* G_SUB */
    73,
    /* G_MUL */
    76,
    /* G_SDIV */
    79,
    /* G_UDIV */
    82,
    /* G_SREM */
    85,
    /* G_UREM */
    88,
    /* G_SDIVREM */
    91,
    /* G_UDIVREM */
    95,
    /* G_AND */
    99,
    /* G_OR */
    102,
    /* G_XOR */
    105,
    /* G_ABDS */
    108,
    /* G_ABDU */
    111,
    /* G_IMPLICIT_DEF */
    114,
    /* G_PHI */
    115,
    /* G_FRAME_INDEX */
    116,
    /* G_GLOBAL_VALUE */
    118,
    /* G_PTRAUTH_GLOBAL_VALUE */
    120,
    /* G_CONSTANT_POOL */
    125,
    /* G_EXTRACT */
    127,
    /* G_UNMERGE_VALUES */
    130,
    /* G_INSERT */
    132,
    /* G_MERGE_VALUES */
    136,
    /* G_BUILD_VECTOR */
    138,
    /* G_BUILD_VECTOR_TRUNC */
    140,
    /* G_CONCAT_VECTORS */
    142,
    /* G_PTRTOINT */
    144,
    /* G_INTTOPTR */
    146,
    /* G_BITCAST */
    148,
    /* G_FREEZE */
    150,
    /* G_CONSTANT_FOLD_BARRIER */
    152,
    /* G_INTRINSIC_FPTRUNC_ROUND */
    154,
    /* G_INTRINSIC_TRUNC */
    157,
    /* G_INTRINSIC_ROUND */
    159,
    /* G_INTRINSIC_LRINT */
    161,
    /* G_INTRINSIC_LLRINT */
    163,
    /* G_INTRINSIC_ROUNDEVEN */
    165,
    /* G_READCYCLECOUNTER */
    167,
    /* G_READSTEADYCOUNTER */
    168,
    /* G_LOAD */
    169,
    /* G_SEXTLOAD */
    171,
    /* G_ZEXTLOAD */
    173,
    /* G_INDEXED_LOAD */
    175,
    /* G_INDEXED_SEXTLOAD */
    180,
    /* G_INDEXED_ZEXTLOAD */
    185,
    /* G_STORE */
    190,
    /* G_INDEXED_STORE */
    192,
    /* G_ATOMIC_CMPXCHG_WITH_SUCCESS */
    197,
    /* G_ATOMIC_CMPXCHG */
    202,
    /* G_ATOMICRMW_XCHG */
    206,
    /* G_ATOMICRMW_ADD */
    209,
    /* G_ATOMICRMW_SUB */
    212,
    /* G_ATOMICRMW_AND */
    215,
    /* G_ATOMICRMW_NAND */
    218,
    /* G_ATOMICRMW_OR */
    221,
    /* G_ATOMICRMW_XOR */
    224,
    /* G_ATOMICRMW_MAX */
    227,
    /* G_ATOMICRMW_MIN */
    230,
    /* G_ATOMICRMW_UMAX */
    233,
    /* G_ATOMICRMW_UMIN */
    236,
    /* G_ATOMICRMW_FADD */
    239,
    /* G_ATOMICRMW_FSUB */
    242,
    /* G_ATOMICRMW_FMAX */
    245,
    /* G_ATOMICRMW_FMIN */
    248,
    /* G_ATOMICRMW_UINC_WRAP */
    251,
    /* G_ATOMICRMW_UDEC_WRAP */
    254,
    /* G_ATOMICRMW_USUB_COND */
    257,
    /* G_ATOMICRMW_USUB_SAT */
    260,
    /* G_FENCE */
    263,
    /* G_PREFETCH */
    265,
    /* G_BRCOND */
    269,
    /* G_BRINDIRECT */
    271,
    /* G_INVOKE_REGION_START */
    272,
    /* G_INTRINSIC */
    272,
    /* G_INTRINSIC_W_SIDE_EFFECTS */
    273,
    /* G_INTRINSIC_CONVERGENT */
    274,
    /* G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS */
    275,
    /* G_ANYEXT */
    276,
    /* G_TRUNC */
    278,
    /* G_CONSTANT */
    280,
    /* G_FCONSTANT */
    282,
    /* G_VASTART */
    284,
    /* G_VAARG */
    285,
    /* G_SEXT */
    288,
    /* G_SEXT_INREG */
    290,
    /* G_ZEXT */
    293,
    /* G_SHL */
    295,
    /* G_LSHR */
    298,
    /* G_ASHR */
    301,
    /* G_FSHL */
    304,
    /* G_FSHR */
    308,
    /* G_ROTR */
    312,
    /* G_ROTL */
    315,
    /* G_ICMP */
    318,
    /* G_FCMP */
    322,
    /* G_SCMP */
    326,
    /* G_UCMP */
    329,
    /* G_SELECT */
    332,
    /* G_UADDO */
    336,
    /* G_UADDE */
    340,
    /* G_USUBO */
    345,
    /* G_USUBE */
    349,
    /* G_SADDO */
    354,
    /* G_SADDE */
    358,
    /* G_SSUBO */
    363,
    /* G_SSUBE */
    367,
    /* G_UMULO */
    372,
    /* G_SMULO */
    376,
    /* G_UMULH */
    380,
    /* G_SMULH */
    383,
    /* G_UADDSAT */
    386,
    /* G_SADDSAT */
    389,
    /* G_USUBSAT */
    392,
    /* G_SSUBSAT */
    395,
    /* G_USHLSAT */
    398,
    /* G_SSHLSAT */
    401,
    /* G_SMULFIX */
    404,
    /* G_UMULFIX */
    408,
    /* G_SMULFIXSAT */
    412,
    /* G_UMULFIXSAT */
    416,
    /* G_SDIVFIX */
    420,
    /* G_UDIVFIX */
    424,
    /* G_SDIVFIXSAT */
    428,
    /* G_UDIVFIXSAT */
    432,
    /* G_FADD */
    436,
    /* G_FSUB */
    439,
    /* G_FMUL */
    442,
    /* G_FMA */
    445,
    /* G_FMAD */
    449,
    /* G_FDIV */
    453,
    /* G_FREM */
    456,
    /* G_FPOW */
    459,
    /* G_FPOWI */
    462,
    /* G_FEXP */
    465,
    /* G_FEXP2 */
    467,
    /* G_FEXP10 */
    469,
    /* G_FLOG */
    471,
    /* G_FLOG2 */
    473,
    /* G_FLOG10 */
    475,
    /* G_FLDEXP */
    477,
    /* G_FFREXP */
    480,
    /* G_FNEG */
    483,
    /* G_FPEXT */
    485,
    /* G_FPTRUNC */
    487,
    /* G_FPTOSI */
    489,
    /* G_FPTOUI */
    491,
    /* G_SITOFP */
    493,
    /* G_UITOFP */
    495,
    /* G_FPTOSI_SAT */
    497,
    /* G_FPTOUI_SAT */
    499,
    /* G_FABS */
    501,
    /* G_FCOPYSIGN */
    503,
    /* G_IS_FPCLASS */
    506,
    /* G_FCANONICALIZE */
    509,
    /* G_FMINNUM */
    511,
    /* G_FMAXNUM */
    514,
    /* G_FMINNUM_IEEE */
    517,
    /* G_FMAXNUM_IEEE */
    520,
    /* G_FMINIMUM */
    523,
    /* G_FMAXIMUM */
    526,
    /* G_GET_FPENV */
    529,
    /* G_SET_FPENV */
    530,
    /* G_RESET_FPENV */
    531,
    /* G_GET_FPMODE */
    531,
    /* G_SET_FPMODE */
    532,
    /* G_RESET_FPMODE */
    533,
    /* G_PTR_ADD */
    533,
    /* G_PTRMASK */
    536,
    /* G_SMIN */
    539,
    /* G_SMAX */
    542,
    /* G_UMIN */
    545,
    /* G_UMAX */
    548,
    /* G_ABS */
    551,
    /* G_LROUND */
    553,
    /* G_LLROUND */
    555,
    /* G_BR */
    557,
    /* G_BRJT */
    558,
    /* G_VSCALE */
    561,
    /* G_INSERT_SUBVECTOR */
    563,
    /* G_EXTRACT_SUBVECTOR */
    567,
    /* G_INSERT_VECTOR_ELT */
    570,
    /* G_EXTRACT_VECTOR_ELT */
    574,
    /* G_SHUFFLE_VECTOR */
    577,
    /* G_SPLAT_VECTOR */
    581,
    /* G_STEP_VECTOR */
    583,
    /* G_VECTOR_COMPRESS */
    585,
    /* G_CTTZ */
    589,
    /* G_CTTZ_ZERO_UNDEF */
    591,
    /* G_CTLZ */
    593,
    /* G_CTLZ_ZERO_UNDEF */
    595,
    /* G_CTPOP */
    597,
    /* G_BSWAP */
    599,
    /* G_BITREVERSE */
    601,
    /* G_FCEIL */
    603,
    /* G_FCOS */
    605,
    /* G_FSIN */
    607,
    /* G_FSINCOS */
    609,
    /* G_FTAN */
    612,
    /* G_FACOS */
    614,
    /* G_FASIN */
    616,
    /* G_FATAN */
    618,
    /* G_FATAN2 */
    620,
    /* G_FCOSH */
    623,
    /* G_FSINH */
    625,
    /* G_FTANH */
    627,
    /* G_FSQRT */
    629,
    /* G_FFLOOR */
    631,
    /* G_FRINT */
    633,
    /* G_FNEARBYINT */
    635,
    /* G_ADDRSPACE_CAST */
    637,
    /* G_BLOCK_ADDR */
    639,
    /* G_JUMP_TABLE */
    641,
    /* G_DYN_STACKALLOC */
    643,
    /* G_STACKSAVE */
    646,
    /* G_STACKRESTORE */
    647,
    /* G_STRICT_FADD */
    648,
    /* G_STRICT_FSUB */
    651,
    /* G_STRICT_FMUL */
    654,
    /* G_STRICT_FDIV */
    657,
    /* G_STRICT_FREM */
    660,
    /* G_STRICT_FMA */
    663,
    /* G_STRICT_FSQRT */
    667,
    /* G_STRICT_FLDEXP */
    669,
    /* G_READ_REGISTER */
    672,
    /* G_WRITE_REGISTER */
    674,
    /* G_MEMCPY */
    676,
    /* G_MEMCPY_INLINE */
    680,
    /* G_MEMMOVE */
    683,
    /* G_MEMSET */
    687,
    /* G_BZERO */
    691,
    /* G_TRAP */
    694,
    /* G_DEBUGTRAP */
    694,
    /* G_UBSANTRAP */
    694,
    /* G_VECREDUCE_SEQ_FADD */
    695,
    /* G_VECREDUCE_SEQ_FMUL */
    698,
    /* G_VECREDUCE_FADD */
    701,
    /* G_VECREDUCE_FMUL */
    703,
    /* G_VECREDUCE_FMAX */
    705,
    /* G_VECREDUCE_FMIN */
    707,
    /* G_VECREDUCE_FMAXIMUM */
    709,
    /* G_VECREDUCE_FMINIMUM */
    711,
    /* G_VECREDUCE_ADD */
    713,
    /* G_VECREDUCE_MUL */
    715,
    /* G_VECREDUCE_AND */
    717,
    /* G_VECREDUCE_OR */
    719,
    /* G_VECREDUCE_XOR */
    721,
    /* G_VECREDUCE_SMAX */
    723,
    /* G_VECREDUCE_SMIN */
    725,
    /* G_VECREDUCE_UMAX */
    727,
    /* G_VECREDUCE_UMIN */
    729,
    /* G_SBFX */
    731,
    /* G_UBFX */
    735,
    /* ADD */
    739,
  };

  using namespace OpTypes;
  static const int8_t OpcodeOperandTypes[] = {
    
    /* PHI */
    -1, 
    /* INLINEASM */
    /* INLINEASM_BR */
    /* CFI_INSTRUCTION */
    i32imm, 
    /* EH_LABEL */
    i32imm, 
    /* GC_LABEL */
    i32imm, 
    /* ANNOTATION_LABEL */
    i32imm, 
    /* KILL */
    /* EXTRACT_SUBREG */
    -1, -1, i32imm, 
    /* INSERT_SUBREG */
    -1, -1, -1, i32imm, 
    /* IMPLICIT_DEF */
    -1, 
    /* INIT_UNDEF */
    -1, 
    /* SUBREG_TO_REG */
    -1, -1, -1, i32imm, 
    /* COPY_TO_REGCLASS */
    -1, -1, i32imm, 
    /* DBG_VALUE */
    /* DBG_VALUE_LIST */
    /* DBG_INSTR_REF */
    /* DBG_PHI */
    /* DBG_LABEL */
    -1, 
    /* REG_SEQUENCE */
    -1, -1, 
    /* COPY */
    -1, -1, 
    /* BUNDLE */
    /* LIFETIME_START */
    i32imm, 
    /* LIFETIME_END */
    i32imm, 
    /* PSEUDO_PROBE */
    i64imm, i64imm, i8imm, i32imm, 
    /* ARITH_FENCE */
    -1, -1, 
    /* STACKMAP */
    i64imm, i32imm, 
    /* FENTRY_CALL */
    /* PATCHPOINT */
    -1, i64imm, i32imm, -1, i32imm, i32imm, 
    /* LOAD_STACK_GUARD */
    -1, 
    /* PREALLOCATED_SETUP */
    i32imm, 
    /* PREALLOCATED_ARG */
    -1, i32imm, i32imm, 
    /* STATEPOINT */
    /* LOCAL_ESCAPE */
    -1, i32imm, 
    /* FAULTING_OP */
    -1, 
    /* PATCHABLE_OP */
    /* PATCHABLE_FUNCTION_ENTER */
    /* PATCHABLE_RET */
    /* PATCHABLE_FUNCTION_EXIT */
    /* PATCHABLE_TAIL_CALL */
    /* PATCHABLE_EVENT_CALL */
    -1, -1, 
    /* PATCHABLE_TYPED_EVENT_CALL */
    -1, -1, -1, 
    /* ICALL_BRANCH_FUNNEL */
    /* FAKE_USE */
    /* MEMBARRIER */
    /* JUMP_TABLE_DEBUG_INFO */
    i64imm, 
    /* CONVERGENCECTRL_ENTRY */
    -1, 
    /* CONVERGENCECTRL_ANCHOR */
    -1, 
    /* CONVERGENCECTRL_LOOP */
    -1, -1, 
    /* CONVERGENCECTRL_GLUE */
    -1, 
    /* G_ASSERT_SEXT */
    type0, type0, untyped_imm_0, 
    /* G_ASSERT_ZEXT */
    type0, type0, untyped_imm_0, 
    /* G_ASSERT_ALIGN */
    type0, type0, untyped_imm_0, 
    /* G_ADD */
    type0, type0, type0, 
    /* G_SUB */
    type0, type0, type0, 
    /* G_MUL */
    type0, type0, type0, 
    /* G_SDIV */
    type0, type0, type0, 
    /* G_UDIV */
    type0, type0, type0, 
    /* G_SREM */
    type0, type0, type0, 
    /* G_UREM */
    type0, type0, type0, 
    /* G_SDIVREM */
    type0, type0, type0, type0, 
    /* G_UDIVREM */
    type0, type0, type0, type0, 
    /* G_AND */
    type0, type0, type0, 
    /* G_OR */
    type0, type0, type0, 
    /* G_XOR */
    type0, type0, type0, 
    /* G_ABDS */
    type0, type0, type0, 
    /* G_ABDU */
    type0, type0, type0, 
    /* G_IMPLICIT_DEF */
    type0, 
    /* G_PHI */
    type0, 
    /* G_FRAME_INDEX */
    ptype0, -1, 
    /* G_GLOBAL_VALUE */
    type0, -1, 
    /* G_PTRAUTH_GLOBAL_VALUE */
    type0, -1, i32imm, type1, i64imm, 
    /* G_CONSTANT_POOL */
    type0, -1, 
    /* G_EXTRACT */
    type0, type1, untyped_imm_0, 
    /* G_UNMERGE_VALUES */
    type0, type1, 
    /* G_INSERT */
    type0, type0, type1, untyped_imm_0, 
    /* G_MERGE_VALUES */
    type0, type1, 
    /* G_BUILD_VECTOR */
    type0, type1, 
    /* G_BUILD_VECTOR_TRUNC */
    type0, type1, 
    /* G_CONCAT_VECTORS */
    type0, type1, 
    /* G_PTRTOINT */
    type0, type1, 
    /* G_INTTOPTR */
    type0, type1, 
    /* G_BITCAST */
    type0, type1, 
    /* G_FREEZE */
    type0, type0, 
    /* G_CONSTANT_FOLD_BARRIER */
    type0, type0, 
    /* G_INTRINSIC_FPTRUNC_ROUND */
    type0, type1, i32imm, 
    /* G_INTRINSIC_TRUNC */
    type0, type0, 
    /* G_INTRINSIC_ROUND */
    type0, type0, 
    /* G_INTRINSIC_LRINT */
    type0, type1, 
    /* G_INTRINSIC_LLRINT */
    type0, type1, 
    /* G_INTRINSIC_ROUNDEVEN */
    type0, type0, 
    /* G_READCYCLECOUNTER */
    type0, 
    /* G_READSTEADYCOUNTER */
    type0, 
    /* G_LOAD */
    type0, ptype1, 
    /* G_SEXTLOAD */
    type0, ptype1, 
    /* G_ZEXTLOAD */
    type0, ptype1, 
    /* G_INDEXED_LOAD */
    type0, ptype1, ptype1, type2, -1, 
    /* G_INDEXED_SEXTLOAD */
    type0, ptype1, ptype1, type2, -1, 
    /* G_INDEXED_ZEXTLOAD */
    type0, ptype1, ptype1, type2, -1, 
    /* G_STORE */
    type0, ptype1, 
    /* G_INDEXED_STORE */
    ptype0, type1, ptype0, ptype2, -1, 
    /* G_ATOMIC_CMPXCHG_WITH_SUCCESS */
    type0, type1, type2, type0, type0, 
    /* G_ATOMIC_CMPXCHG */
    type0, ptype1, type0, type0, 
    /* G_ATOMICRMW_XCHG */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_ADD */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_SUB */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_AND */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_NAND */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_OR */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_XOR */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_MAX */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_MIN */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_UMAX */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_UMIN */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_FADD */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_FSUB */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_FMAX */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_FMIN */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_UINC_WRAP */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_UDEC_WRAP */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_USUB_COND */
    type0, ptype1, type0, 
    /* G_ATOMICRMW_USUB_SAT */
    type0, ptype1, type0, 
    /* G_FENCE */
    i32imm, i32imm, 
    /* G_PREFETCH */
    ptype0, i32imm, i32imm, i32imm, 
    /* G_BRCOND */
    type0, -1, 
    /* G_BRINDIRECT */
    type0, 
    /* G_INVOKE_REGION_START */
    /* G_INTRINSIC */
    -1, 
    /* G_INTRINSIC_W_SIDE_EFFECTS */
    -1, 
    /* G_INTRINSIC_CONVERGENT */
    -1, 
    /* G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS */
    -1, 
    /* G_ANYEXT */
    type0, type1, 
    /* G_TRUNC */
    type0, type1, 
    /* G_CONSTANT */
    type0, -1, 
    /* G_FCONSTANT */
    type0, -1, 
    /* G_VASTART */
    type0, 
    /* G_VAARG */
    type0, type1, -1, 
    /* G_SEXT */
    type0, type1, 
    /* G_SEXT_INREG */
    type0, type0, untyped_imm_0, 
    /* G_ZEXT */
    type0, type1, 
    /* G_SHL */
    type0, type0, type1, 
    /* G_LSHR */
    type0, type0, type1, 
    /* G_ASHR */
    type0, type0, type1, 
    /* G_FSHL */
    type0, type0, type0, type1, 
    /* G_FSHR */
    type0, type0, type0, type1, 
    /* G_ROTR */
    type0, type0, type1, 
    /* G_ROTL */
    type0, type0, type1, 
    /* G_ICMP */
    type0, -1, type1, type1, 
    /* G_FCMP */
    type0, -1, type1, type1, 
    /* G_SCMP */
    type0, type1, type1, 
    /* G_UCMP */
    type0, type1, type1, 
    /* G_SELECT */
    type0, type1, type0, type0, 
    /* G_UADDO */
    type0, type1, type0, type0, 
    /* G_UADDE */
    type0, type1, type0, type0, type1, 
    /* G_USUBO */
    type0, type1, type0, type0, 
    /* G_USUBE */
    type0, type1, type0, type0, type1, 
    /* G_SADDO */
    type0, type1, type0, type0, 
    /* G_SADDE */
    type0, type1, type0, type0, type1, 
    /* G_SSUBO */
    type0, type1, type0, type0, 
    /* G_SSUBE */
    type0, type1, type0, type0, type1, 
    /* G_UMULO */
    type0, type1, type0, type0, 
    /* G_SMULO */
    type0, type1, type0, type0, 
    /* G_UMULH */
    type0, type0, type0, 
    /* G_SMULH */
    type0, type0, type0, 
    /* G_UADDSAT */
    type0, type0, type0, 
    /* G_SADDSAT */
    type0, type0, type0, 
    /* G_USUBSAT */
    type0, type0, type0, 
    /* G_SSUBSAT */
    type0, type0, type0, 
    /* G_USHLSAT */
    type0, type0, type1, 
    /* G_SSHLSAT */
    type0, type0, type1, 
    /* G_SMULFIX */
    type0, type0, type0, untyped_imm_0, 
    /* G_UMULFIX */
    type0, type0, type0, untyped_imm_0, 
    /* G_SMULFIXSAT */
    type0, type0, type0, untyped_imm_0, 
    /* G_UMULFIXSAT */
    type0, type0, type0, untyped_imm_0, 
    /* G_SDIVFIX */
    type0, type0, type0, untyped_imm_0, 
    /* G_UDIVFIX */
    type0, type0, type0, untyped_imm_0, 
    /* G_SDIVFIXSAT */
    type0, type0, type0, untyped_imm_0, 
    /* G_UDIVFIXSAT */
    type0, type0, type0, untyped_imm_0, 
    /* G_FADD */
    type0, type0, type0, 
    /* G_FSUB */
    type0, type0, type0, 
    /* G_FMUL */
    type0, type0, type0, 
    /* G_FMA */
    type0, type0, type0, type0, 
    /* G_FMAD */
    type0, type0, type0, type0, 
    /* G_FDIV */
    type0, type0, type0, 
    /* G_FREM */
    type0, type0, type0, 
    /* G_FPOW */
    type0, type0, type0, 
    /* G_FPOWI */
    type0, type0, type1, 
    /* G_FEXP */
    type0, type0, 
    /* G_FEXP2 */
    type0, type0, 
    /* G_FEXP10 */
    type0, type0, 
    /* G_FLOG */
    type0, type0, 
    /* G_FLOG2 */
    type0, type0, 
    /* G_FLOG10 */
    type0, type0, 
    /* G_FLDEXP */
    type0, type0, type1, 
    /* G_FFREXP */
    type0, type1, type0, 
    /* G_FNEG */
    type0, type0, 
    /* G_FPEXT */
    type0, type1, 
    /* G_FPTRUNC */
    type0, type1, 
    /* G_FPTOSI */
    type0, type1, 
    /* G_FPTOUI */
    type0, type1, 
    /* G_SITOFP */
    type0, type1, 
    /* G_UITOFP */
    type0, type1, 
    /* G_FPTOSI_SAT */
    type0, type1, 
    /* G_FPTOUI_SAT */
    type0, type1, 
    /* G_FABS */
    type0, type0, 
    /* G_FCOPYSIGN */
    type0, type0, type1, 
    /* G_IS_FPCLASS */
    type0, type1, -1, 
    /* G_FCANONICALIZE */
    type0, type0, 
    /* G_FMINNUM */
    type0, type0, type0, 
    /* G_FMAXNUM */
    type0, type0, type0, 
    /* G_FMINNUM_IEEE */
    type0, type0, type0, 
    /* G_FMAXNUM_IEEE */
    type0, type0, type0, 
    /* G_FMINIMUM */
    type0, type0, type0, 
    /* G_FMAXIMUM */
    type0, type0, type0, 
    /* G_GET_FPENV */
    type0, 
    /* G_SET_FPENV */
    type0, 
    /* G_RESET_FPENV */
    /* G_GET_FPMODE */
    type0, 
    /* G_SET_FPMODE */
    type0, 
    /* G_RESET_FPMODE */
    /* G_PTR_ADD */
    ptype0, ptype0, type1, 
    /* G_PTRMASK */
    ptype0, ptype0, type1, 
    /* G_SMIN */
    type0, type0, type0, 
    /* G_SMAX */
    type0, type0, type0, 
    /* G_UMIN */
    type0, type0, type0, 
    /* G_UMAX */
    type0, type0, type0, 
    /* G_ABS */
    type0, type0, 
    /* G_LROUND */
    type0, type1, 
    /* G_LLROUND */
    type0, type1, 
    /* G_BR */
    -1, 
    /* G_BRJT */
    ptype0, -1, type1, 
    /* G_VSCALE */
    type0, -1, 
    /* G_INSERT_SUBVECTOR */
    type0, type0, type1, untyped_imm_0, 
    /* G_EXTRACT_SUBVECTOR */
    type0, type1, untyped_imm_0, 
    /* G_INSERT_VECTOR_ELT */
    type0, type0, type1, type2, 
    /* G_EXTRACT_VECTOR_ELT */
    type0, type1, type2, 
    /* G_SHUFFLE_VECTOR */
    type0, type1, type1, -1, 
    /* G_SPLAT_VECTOR */
    type0, type1, 
    /* G_STEP_VECTOR */
    type0, -1, 
    /* G_VECTOR_COMPRESS */
    type0, type0, type1, type0, 
    /* G_CTTZ */
    type0, type1, 
    /* G_CTTZ_ZERO_UNDEF */
    type0, type1, 
    /* G_CTLZ */
    type0, type1, 
    /* G_CTLZ_ZERO_UNDEF */
    type0, type1, 
    /* G_CTPOP */
    type0, type1, 
    /* G_BSWAP */
    type0, type0, 
    /* G_BITREVERSE */
    type0, type0, 
    /* G_FCEIL */
    type0, type0, 
    /* G_FCOS */
    type0, type0, 
    /* G_FSIN */
    type0, type0, 
    /* G_FSINCOS */
    type0, type0, type0, 
    /* G_FTAN */
    type0, type0, 
    /* G_FACOS */
    type0, type0, 
    /* G_FASIN */
    type0, type0, 
    /* G_FATAN */
    type0, type0, 
    /* G_FATAN2 */
    type0, type0, type0, 
    /* G_FCOSH */
    type0, type0, 
    /* G_FSINH */
    type0, type0, 
    /* G_FTANH */
    type0, type0, 
    /* G_FSQRT */
    type0, type0, 
    /* G_FFLOOR */
    type0, type0, 
    /* G_FRINT */
    type0, type0, 
    /* G_FNEARBYINT */
    type0, type0, 
    /* G_ADDRSPACE_CAST */
    type0, type1, 
    /* G_BLOCK_ADDR */
    type0, -1, 
    /* G_JUMP_TABLE */
    type0, -1, 
    /* G_DYN_STACKALLOC */
    ptype0, type1, i32imm, 
    /* G_STACKSAVE */
    ptype0, 
    /* G_STACKRESTORE */
    ptype0, 
    /* G_STRICT_FADD */
    type0, type0, type0, 
    /* G_STRICT_FSUB */
    type0, type0, type0, 
    /* G_STRICT_FMUL */
    type0, type0, type0, 
    /* G_STRICT_FDIV */
    type0, type0, type0, 
    /* G_STRICT_FREM */
    type0, type0, type0, 
    /* G_STRICT_FMA */
    type0, type0, type0, type0, 
    /* G_STRICT_FSQRT */
    type0, type0, 
    /* G_STRICT_FLDEXP */
    type0, type0, type1, 
    /* G_READ_REGISTER */
    type0, -1, 
    /* G_WRITE_REGISTER */
    -1, type0, 
    /* G_MEMCPY */
    ptype0, ptype1, type2, untyped_imm_0, 
    /* G_MEMCPY_INLINE */
    ptype0, ptype1, type2, 
    /* G_MEMMOVE */
    ptype0, ptype1, type2, untyped_imm_0, 
    /* G_MEMSET */
    ptype0, type1, type2, untyped_imm_0, 
    /* G_BZERO */
    ptype0, type1, untyped_imm_0, 
    /* G_TRAP */
    /* G_DEBUGTRAP */
    /* G_UBSANTRAP */
    i8imm, 
    /* G_VECREDUCE_SEQ_FADD */
    type0, type1, type2, 
    /* G_VECREDUCE_SEQ_FMUL */
    type0, type1, type2, 
    /* G_VECREDUCE_FADD */
    type0, type1, 
    /* G_VECREDUCE_FMUL */
    type0, type1, 
    /* G_VECREDUCE_FMAX */
    type0, type1, 
    /* G_VECREDUCE_FMIN */
    type0, type1, 
    /* G_VECREDUCE_FMAXIMUM */
    type0, type1, 
    /* G_VECREDUCE_FMINIMUM */
    type0, type1, 
    /* G_VECREDUCE_ADD */
    type0, type1, 
    /* G_VECREDUCE_MUL */
    type0, type1, 
    /* G_VECREDUCE_AND */
    type0, type1, 
    /* G_VECREDUCE_OR */
    type0, type1, 
    /* G_VECREDUCE_XOR */
    type0, type1, 
    /* G_VECREDUCE_SMAX */
    type0, type1, 
    /* G_VECREDUCE_SMIN */
    type0, type1, 
    /* G_VECREDUCE_UMAX */
    type0, type1, 
    /* G_VECREDUCE_UMIN */
    type0, type1, 
    /* G_SBFX */
    type0, type0, type1, type1, 
    /* G_UBFX */
    type0, type0, type1, type1, 
    /* ADD */
    GPR, GPR, GPR, 
  };
  return OpcodeOperandTypes[Offsets[Opcode] + OpIdx];
}
} // end namespace llvm::Sim
#endif // GET_INSTRINFO_OPERAND_TYPE

#ifdef GET_INSTRINFO_MEM_OPERAND_SIZE
#undef GET_INSTRINFO_MEM_OPERAND_SIZE
namespace llvm::Sim {
LLVM_READONLY
static int getMemOperandSize(int OpType) {
  switch (OpType) {
  default: return 0;
  }
}
} // end namespace llvm::Sim
#endif // GET_INSTRINFO_MEM_OPERAND_SIZE

#ifdef GET_INSTRINFO_LOGICAL_OPERAND_SIZE_MAP
#undef GET_INSTRINFO_LOGICAL_OPERAND_SIZE_MAP
namespace llvm::Sim {
LLVM_READONLY static unsigned
getLogicalOperandSize(uint16_t Opcode, uint16_t LogicalOpIdx) {
  return LogicalOpIdx;
}
LLVM_READONLY static inline unsigned
getLogicalOperandIdx(uint16_t Opcode, uint16_t LogicalOpIdx) {
  auto S = 0U;
  for (auto i = 0U; i < LogicalOpIdx; ++i)
    S += getLogicalOperandSize(Opcode, i);
  return S;
}
} // end namespace llvm::Sim
#endif // GET_INSTRINFO_LOGICAL_OPERAND_SIZE_MAP

#ifdef GET_INSTRINFO_LOGICAL_OPERAND_TYPE_MAP
#undef GET_INSTRINFO_LOGICAL_OPERAND_TYPE_MAP
namespace llvm::Sim {
LLVM_READONLY static int
getLogicalOperandType(uint16_t Opcode, uint16_t LogicalOpIdx) {
  return -1;
}
} // end namespace llvm::Sim
#endif // GET_INSTRINFO_LOGICAL_OPERAND_TYPE_MAP

#ifdef GET_INSTRINFO_MC_HELPER_DECLS
#undef GET_INSTRINFO_MC_HELPER_DECLS

namespace llvm {
class MCInst;
class FeatureBitset;

namespace Sim_MC {

void verifyInstructionPredicates(unsigned Opcode, const FeatureBitset &Features);

} // end namespace Sim_MC
} // end namespace llvm

#endif // GET_INSTRINFO_MC_HELPER_DECLS

#ifdef GET_INSTRINFO_MC_HELPERS
#undef GET_INSTRINFO_MC_HELPERS

namespace llvm::Sim_MC {
} // end namespace llvm::Sim_MC
#endif // GET_GENISTRINFO_MC_HELPERS

#if (defined(ENABLE_INSTR_PREDICATE_VERIFIER) && !defined(NDEBUG)) ||\
    defined(GET_AVAILABLE_OPCODE_CHECKER)
#define GET_COMPUTE_FEATURES
#endif
#ifdef GET_COMPUTE_FEATURES
#undef GET_COMPUTE_FEATURES
namespace llvm::Sim_MC {
// Bits for subtarget features that participate in instruction matching.
enum SubtargetFeatureBits : uint8_t {
};

inline FeatureBitset computeAvailableFeatures(const FeatureBitset &FB) {
  FeatureBitset Features;
  return Features;
}

inline FeatureBitset computeRequiredFeatures(unsigned Opcode) {
  enum : uint8_t {
    CEFBS_None,
  };

  static constexpr FeatureBitset FeatureBitsets[] = {
    {}, // CEFBS_None
  };
  static constexpr uint8_t RequiredFeaturesRefs[] = {
    CEFBS_None, // PHI = 0
    CEFBS_None, // INLINEASM = 1
    CEFBS_None, // INLINEASM_BR = 2
    CEFBS_None, // CFI_INSTRUCTION = 3
    CEFBS_None, // EH_LABEL = 4
    CEFBS_None, // GC_LABEL = 5
    CEFBS_None, // ANNOTATION_LABEL = 6
    CEFBS_None, // KILL = 7
    CEFBS_None, // EXTRACT_SUBREG = 8
    CEFBS_None, // INSERT_SUBREG = 9
    CEFBS_None, // IMPLICIT_DEF = 10
    CEFBS_None, // INIT_UNDEF = 11
    CEFBS_None, // SUBREG_TO_REG = 12
    CEFBS_None, // COPY_TO_REGCLASS = 13
    CEFBS_None, // DBG_VALUE = 14
    CEFBS_None, // DBG_VALUE_LIST = 15
    CEFBS_None, // DBG_INSTR_REF = 16
    CEFBS_None, // DBG_PHI = 17
    CEFBS_None, // DBG_LABEL = 18
    CEFBS_None, // REG_SEQUENCE = 19
    CEFBS_None, // COPY = 20
    CEFBS_None, // BUNDLE = 21
    CEFBS_None, // LIFETIME_START = 22
    CEFBS_None, // LIFETIME_END = 23
    CEFBS_None, // PSEUDO_PROBE = 24
    CEFBS_None, // ARITH_FENCE = 25
    CEFBS_None, // STACKMAP = 26
    CEFBS_None, // FENTRY_CALL = 27
    CEFBS_None, // PATCHPOINT = 28
    CEFBS_None, // LOAD_STACK_GUARD = 29
    CEFBS_None, // PREALLOCATED_SETUP = 30
    CEFBS_None, // PREALLOCATED_ARG = 31
    CEFBS_None, // STATEPOINT = 32
    CEFBS_None, // LOCAL_ESCAPE = 33
    CEFBS_None, // FAULTING_OP = 34
    CEFBS_None, // PATCHABLE_OP = 35
    CEFBS_None, // PATCHABLE_FUNCTION_ENTER = 36
    CEFBS_None, // PATCHABLE_RET = 37
    CEFBS_None, // PATCHABLE_FUNCTION_EXIT = 38
    CEFBS_None, // PATCHABLE_TAIL_CALL = 39
    CEFBS_None, // PATCHABLE_EVENT_CALL = 40
    CEFBS_None, // PATCHABLE_TYPED_EVENT_CALL = 41
    CEFBS_None, // ICALL_BRANCH_FUNNEL = 42
    CEFBS_None, // FAKE_USE = 43
    CEFBS_None, // MEMBARRIER = 44
    CEFBS_None, // JUMP_TABLE_DEBUG_INFO = 45
    CEFBS_None, // CONVERGENCECTRL_ENTRY = 46
    CEFBS_None, // CONVERGENCECTRL_ANCHOR = 47
    CEFBS_None, // CONVERGENCECTRL_LOOP = 48
    CEFBS_None, // CONVERGENCECTRL_GLUE = 49
    CEFBS_None, // G_ASSERT_SEXT = 50
    CEFBS_None, // G_ASSERT_ZEXT = 51
    CEFBS_None, // G_ASSERT_ALIGN = 52
    CEFBS_None, // G_ADD = 53
    CEFBS_None, // G_SUB = 54
    CEFBS_None, // G_MUL = 55
    CEFBS_None, // G_SDIV = 56
    CEFBS_None, // G_UDIV = 57
    CEFBS_None, // G_SREM = 58
    CEFBS_None, // G_UREM = 59
    CEFBS_None, // G_SDIVREM = 60
    CEFBS_None, // G_UDIVREM = 61
    CEFBS_None, // G_AND = 62
    CEFBS_None, // G_OR = 63
    CEFBS_None, // G_XOR = 64
    CEFBS_None, // G_ABDS = 65
    CEFBS_None, // G_ABDU = 66
    CEFBS_None, // G_IMPLICIT_DEF = 67
    CEFBS_None, // G_PHI = 68
    CEFBS_None, // G_FRAME_INDEX = 69
    CEFBS_None, // G_GLOBAL_VALUE = 70
    CEFBS_None, // G_PTRAUTH_GLOBAL_VALUE = 71
    CEFBS_None, // G_CONSTANT_POOL = 72
    CEFBS_None, // G_EXTRACT = 73
    CEFBS_None, // G_UNMERGE_VALUES = 74
    CEFBS_None, // G_INSERT = 75
    CEFBS_None, // G_MERGE_VALUES = 76
    CEFBS_None, // G_BUILD_VECTOR = 77
    CEFBS_None, // G_BUILD_VECTOR_TRUNC = 78
    CEFBS_None, // G_CONCAT_VECTORS = 79
    CEFBS_None, // G_PTRTOINT = 80
    CEFBS_None, // G_INTTOPTR = 81
    CEFBS_None, // G_BITCAST = 82
    CEFBS_None, // G_FREEZE = 83
    CEFBS_None, // G_CONSTANT_FOLD_BARRIER = 84
    CEFBS_None, // G_INTRINSIC_FPTRUNC_ROUND = 85
    CEFBS_None, // G_INTRINSIC_TRUNC = 86
    CEFBS_None, // G_INTRINSIC_ROUND = 87
    CEFBS_None, // G_INTRINSIC_LRINT = 88
    CEFBS_None, // G_INTRINSIC_LLRINT = 89
    CEFBS_None, // G_INTRINSIC_ROUNDEVEN = 90
    CEFBS_None, // G_READCYCLECOUNTER = 91
    CEFBS_None, // G_READSTEADYCOUNTER = 92
    CEFBS_None, // G_LOAD = 93
    CEFBS_None, // G_SEXTLOAD = 94
    CEFBS_None, // G_ZEXTLOAD = 95
    CEFBS_None, // G_INDEXED_LOAD = 96
    CEFBS_None, // G_INDEXED_SEXTLOAD = 97
    CEFBS_None, // G_INDEXED_ZEXTLOAD = 98
    CEFBS_None, // G_STORE = 99
    CEFBS_None, // G_INDEXED_STORE = 100
    CEFBS_None, // G_ATOMIC_CMPXCHG_WITH_SUCCESS = 101
    CEFBS_None, // G_ATOMIC_CMPXCHG = 102
    CEFBS_None, // G_ATOMICRMW_XCHG = 103
    CEFBS_None, // G_ATOMICRMW_ADD = 104
    CEFBS_None, // G_ATOMICRMW_SUB = 105
    CEFBS_None, // G_ATOMICRMW_AND = 106
    CEFBS_None, // G_ATOMICRMW_NAND = 107
    CEFBS_None, // G_ATOMICRMW_OR = 108
    CEFBS_None, // G_ATOMICRMW_XOR = 109
    CEFBS_None, // G_ATOMICRMW_MAX = 110
    CEFBS_None, // G_ATOMICRMW_MIN = 111
    CEFBS_None, // G_ATOMICRMW_UMAX = 112
    CEFBS_None, // G_ATOMICRMW_UMIN = 113
    CEFBS_None, // G_ATOMICRMW_FADD = 114
    CEFBS_None, // G_ATOMICRMW_FSUB = 115
    CEFBS_None, // G_ATOMICRMW_FMAX = 116
    CEFBS_None, // G_ATOMICRMW_FMIN = 117
    CEFBS_None, // G_ATOMICRMW_UINC_WRAP = 118
    CEFBS_None, // G_ATOMICRMW_UDEC_WRAP = 119
    CEFBS_None, // G_ATOMICRMW_USUB_COND = 120
    CEFBS_None, // G_ATOMICRMW_USUB_SAT = 121
    CEFBS_None, // G_FENCE = 122
    CEFBS_None, // G_PREFETCH = 123
    CEFBS_None, // G_BRCOND = 124
    CEFBS_None, // G_BRINDIRECT = 125
    CEFBS_None, // G_INVOKE_REGION_START = 126
    CEFBS_None, // G_INTRINSIC = 127
    CEFBS_None, // G_INTRINSIC_W_SIDE_EFFECTS = 128
    CEFBS_None, // G_INTRINSIC_CONVERGENT = 129
    CEFBS_None, // G_INTRINSIC_CONVERGENT_W_SIDE_EFFECTS = 130
    CEFBS_None, // G_ANYEXT = 131
    CEFBS_None, // G_TRUNC = 132
    CEFBS_None, // G_CONSTANT = 133
    CEFBS_None, // G_FCONSTANT = 134
    CEFBS_None, // G_VASTART = 135
    CEFBS_None, // G_VAARG = 136
    CEFBS_None, // G_SEXT = 137
    CEFBS_None, // G_SEXT_INREG = 138
    CEFBS_None, // G_ZEXT = 139
    CEFBS_None, // G_SHL = 140
    CEFBS_None, // G_LSHR = 141
    CEFBS_None, // G_ASHR = 142
    CEFBS_None, // G_FSHL = 143
    CEFBS_None, // G_FSHR = 144
    CEFBS_None, // G_ROTR = 145
    CEFBS_None, // G_ROTL = 146
    CEFBS_None, // G_ICMP = 147
    CEFBS_None, // G_FCMP = 148
    CEFBS_None, // G_SCMP = 149
    CEFBS_None, // G_UCMP = 150
    CEFBS_None, // G_SELECT = 151
    CEFBS_None, // G_UADDO = 152
    CEFBS_None, // G_UADDE = 153
    CEFBS_None, // G_USUBO = 154
    CEFBS_None, // G_USUBE = 155
    CEFBS_None, // G_SADDO = 156
    CEFBS_None, // G_SADDE = 157
    CEFBS_None, // G_SSUBO = 158
    CEFBS_None, // G_SSUBE = 159
    CEFBS_None, // G_UMULO = 160
    CEFBS_None, // G_SMULO = 161
    CEFBS_None, // G_UMULH = 162
    CEFBS_None, // G_SMULH = 163
    CEFBS_None, // G_UADDSAT = 164
    CEFBS_None, // G_SADDSAT = 165
    CEFBS_None, // G_USUBSAT = 166
    CEFBS_None, // G_SSUBSAT = 167
    CEFBS_None, // G_USHLSAT = 168
    CEFBS_None, // G_SSHLSAT = 169
    CEFBS_None, // G_SMULFIX = 170
    CEFBS_None, // G_UMULFIX = 171
    CEFBS_None, // G_SMULFIXSAT = 172
    CEFBS_None, // G_UMULFIXSAT = 173
    CEFBS_None, // G_SDIVFIX = 174
    CEFBS_None, // G_UDIVFIX = 175
    CEFBS_None, // G_SDIVFIXSAT = 176
    CEFBS_None, // G_UDIVFIXSAT = 177
    CEFBS_None, // G_FADD = 178
    CEFBS_None, // G_FSUB = 179
    CEFBS_None, // G_FMUL = 180
    CEFBS_None, // G_FMA = 181
    CEFBS_None, // G_FMAD = 182
    CEFBS_None, // G_FDIV = 183
    CEFBS_None, // G_FREM = 184
    CEFBS_None, // G_FPOW = 185
    CEFBS_None, // G_FPOWI = 186
    CEFBS_None, // G_FEXP = 187
    CEFBS_None, // G_FEXP2 = 188
    CEFBS_None, // G_FEXP10 = 189
    CEFBS_None, // G_FLOG = 190
    CEFBS_None, // G_FLOG2 = 191
    CEFBS_None, // G_FLOG10 = 192
    CEFBS_None, // G_FLDEXP = 193
    CEFBS_None, // G_FFREXP = 194
    CEFBS_None, // G_FNEG = 195
    CEFBS_None, // G_FPEXT = 196
    CEFBS_None, // G_FPTRUNC = 197
    CEFBS_None, // G_FPTOSI = 198
    CEFBS_None, // G_FPTOUI = 199
    CEFBS_None, // G_SITOFP = 200
    CEFBS_None, // G_UITOFP = 201
    CEFBS_None, // G_FPTOSI_SAT = 202
    CEFBS_None, // G_FPTOUI_SAT = 203
    CEFBS_None, // G_FABS = 204
    CEFBS_None, // G_FCOPYSIGN = 205
    CEFBS_None, // G_IS_FPCLASS = 206
    CEFBS_None, // G_FCANONICALIZE = 207
    CEFBS_None, // G_FMINNUM = 208
    CEFBS_None, // G_FMAXNUM = 209
    CEFBS_None, // G_FMINNUM_IEEE = 210
    CEFBS_None, // G_FMAXNUM_IEEE = 211
    CEFBS_None, // G_FMINIMUM = 212
    CEFBS_None, // G_FMAXIMUM = 213
    CEFBS_None, // G_GET_FPENV = 214
    CEFBS_None, // G_SET_FPENV = 215
    CEFBS_None, // G_RESET_FPENV = 216
    CEFBS_None, // G_GET_FPMODE = 217
    CEFBS_None, // G_SET_FPMODE = 218
    CEFBS_None, // G_RESET_FPMODE = 219
    CEFBS_None, // G_PTR_ADD = 220
    CEFBS_None, // G_PTRMASK = 221
    CEFBS_None, // G_SMIN = 222
    CEFBS_None, // G_SMAX = 223
    CEFBS_None, // G_UMIN = 224
    CEFBS_None, // G_UMAX = 225
    CEFBS_None, // G_ABS = 226
    CEFBS_None, // G_LROUND = 227
    CEFBS_None, // G_LLROUND = 228
    CEFBS_None, // G_BR = 229
    CEFBS_None, // G_BRJT = 230
    CEFBS_None, // G_VSCALE = 231
    CEFBS_None, // G_INSERT_SUBVECTOR = 232
    CEFBS_None, // G_EXTRACT_SUBVECTOR = 233
    CEFBS_None, // G_INSERT_VECTOR_ELT = 234
    CEFBS_None, // G_EXTRACT_VECTOR_ELT = 235
    CEFBS_None, // G_SHUFFLE_VECTOR = 236
    CEFBS_None, // G_SPLAT_VECTOR = 237
    CEFBS_None, // G_STEP_VECTOR = 238
    CEFBS_None, // G_VECTOR_COMPRESS = 239
    CEFBS_None, // G_CTTZ = 240
    CEFBS_None, // G_CTTZ_ZERO_UNDEF = 241
    CEFBS_None, // G_CTLZ = 242
    CEFBS_None, // G_CTLZ_ZERO_UNDEF = 243
    CEFBS_None, // G_CTPOP = 244
    CEFBS_None, // G_BSWAP = 245
    CEFBS_None, // G_BITREVERSE = 246
    CEFBS_None, // G_FCEIL = 247
    CEFBS_None, // G_FCOS = 248
    CEFBS_None, // G_FSIN = 249
    CEFBS_None, // G_FSINCOS = 250
    CEFBS_None, // G_FTAN = 251
    CEFBS_None, // G_FACOS = 252
    CEFBS_None, // G_FASIN = 253
    CEFBS_None, // G_FATAN = 254
    CEFBS_None, // G_FATAN2 = 255
    CEFBS_None, // G_FCOSH = 256
    CEFBS_None, // G_FSINH = 257
    CEFBS_None, // G_FTANH = 258
    CEFBS_None, // G_FSQRT = 259
    CEFBS_None, // G_FFLOOR = 260
    CEFBS_None, // G_FRINT = 261
    CEFBS_None, // G_FNEARBYINT = 262
    CEFBS_None, // G_ADDRSPACE_CAST = 263
    CEFBS_None, // G_BLOCK_ADDR = 264
    CEFBS_None, // G_JUMP_TABLE = 265
    CEFBS_None, // G_DYN_STACKALLOC = 266
    CEFBS_None, // G_STACKSAVE = 267
    CEFBS_None, // G_STACKRESTORE = 268
    CEFBS_None, // G_STRICT_FADD = 269
    CEFBS_None, // G_STRICT_FSUB = 270
    CEFBS_None, // G_STRICT_FMUL = 271
    CEFBS_None, // G_STRICT_FDIV = 272
    CEFBS_None, // G_STRICT_FREM = 273
    CEFBS_None, // G_STRICT_FMA = 274
    CEFBS_None, // G_STRICT_FSQRT = 275
    CEFBS_None, // G_STRICT_FLDEXP = 276
    CEFBS_None, // G_READ_REGISTER = 277
    CEFBS_None, // G_WRITE_REGISTER = 278
    CEFBS_None, // G_MEMCPY = 279
    CEFBS_None, // G_MEMCPY_INLINE = 280
    CEFBS_None, // G_MEMMOVE = 281
    CEFBS_None, // G_MEMSET = 282
    CEFBS_None, // G_BZERO = 283
    CEFBS_None, // G_TRAP = 284
    CEFBS_None, // G_DEBUGTRAP = 285
    CEFBS_None, // G_UBSANTRAP = 286
    CEFBS_None, // G_VECREDUCE_SEQ_FADD = 287
    CEFBS_None, // G_VECREDUCE_SEQ_FMUL = 288
    CEFBS_None, // G_VECREDUCE_FADD = 289
    CEFBS_None, // G_VECREDUCE_FMUL = 290
    CEFBS_None, // G_VECREDUCE_FMAX = 291
    CEFBS_None, // G_VECREDUCE_FMIN = 292
    CEFBS_None, // G_VECREDUCE_FMAXIMUM = 293
    CEFBS_None, // G_VECREDUCE_FMINIMUM = 294
    CEFBS_None, // G_VECREDUCE_ADD = 295
    CEFBS_None, // G_VECREDUCE_MUL = 296
    CEFBS_None, // G_VECREDUCE_AND = 297
    CEFBS_None, // G_VECREDUCE_OR = 298
    CEFBS_None, // G_VECREDUCE_XOR = 299
    CEFBS_None, // G_VECREDUCE_SMAX = 300
    CEFBS_None, // G_VECREDUCE_SMIN = 301
    CEFBS_None, // G_VECREDUCE_UMAX = 302
    CEFBS_None, // G_VECREDUCE_UMIN = 303
    CEFBS_None, // G_SBFX = 304
    CEFBS_None, // G_UBFX = 305
    CEFBS_None, // ADD = 306
  };

  assert(Opcode < 307);
  return FeatureBitsets[RequiredFeaturesRefs[Opcode]];
}

} // end namespace llvm::Sim_MC
#endif // GET_COMPUTE_FEATURES

#ifdef GET_AVAILABLE_OPCODE_CHECKER
#undef GET_AVAILABLE_OPCODE_CHECKER
namespace llvm::Sim_MC {
bool isOpcodeAvailable(unsigned Opcode, const FeatureBitset &Features) {
  FeatureBitset AvailableFeatures = computeAvailableFeatures(Features);
  FeatureBitset RequiredFeatures = computeRequiredFeatures(Opcode);
  FeatureBitset MissingFeatures =
      (AvailableFeatures & RequiredFeatures) ^
      RequiredFeatures;
  return !MissingFeatures.any();
}
} // end namespace llvm::Sim_MC
#endif // GET_AVAILABLE_OPCODE_CHECKER

#ifdef ENABLE_INSTR_PREDICATE_VERIFIER
#undef ENABLE_INSTR_PREDICATE_VERIFIER
#include <sstream>

namespace llvm::Sim_MC {
#ifndef NDEBUG
static const char *SubtargetFeatureNames[] = {
  nullptr
};

#endif // NDEBUG

void verifyInstructionPredicates(
    unsigned Opcode, const FeatureBitset &Features) {
#ifndef NDEBUG
  FeatureBitset AvailableFeatures = computeAvailableFeatures(Features);
  FeatureBitset RequiredFeatures = computeRequiredFeatures(Opcode);
  FeatureBitset MissingFeatures =
      (AvailableFeatures & RequiredFeatures) ^
      RequiredFeatures;
  if (MissingFeatures.any()) {
    std::ostringstream Msg;
    Msg << "Attempting to emit " << &SimInstrNameData[SimInstrNameIndices[Opcode]]
        << " instruction but the ";
    for (unsigned i = 0, e = MissingFeatures.size(); i != e; ++i)
      if (MissingFeatures.test(i))
        Msg << SubtargetFeatureNames[i] << " ";
    Msg << "predicate(s) are not met";
    report_fatal_error(Msg.str().c_str());
  }
#endif // NDEBUG
}
} // end namespace llvm::Sim_MC
#endif // ENABLE_INSTR_PREDICATE_VERIFIER

