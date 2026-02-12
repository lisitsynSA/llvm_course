/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Target Register Enum Values                                                *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


#ifdef GET_REGINFO_ENUM
#undef GET_REGINFO_ENUM

namespace llvm {

class MCRegisterClass;
extern const MCRegisterClass SimMCRegisterClasses[];

namespace Sim {
enum : unsigned {
  NoRegister,
  R0 = 1,
  R1 = 2,
  R2 = 3,
  R3 = 4,
  R4 = 5,
  R5 = 6,
  R6 = 7,
  R7 = 8,
  R8 = 9,
  R9 = 10,
  R10 = 11,
  R11 = 12,
  R12 = 13,
  R13 = 14,
  R14 = 15,
  R15 = 16,
  NUM_TARGET_REGS // 17
};
} // end namespace Sim

// Register classes

namespace Sim {
enum {
  GPRRegClassID = 0,

};
} // end namespace Sim

// Register pressure sets enum.
namespace Sim {
enum RegisterPressureSets {
  GPR = 0,
};
} // end namespace Sim

} // end namespace llvm

#endif // GET_REGINFO_ENUM

/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* MC Register Information                                                    *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


#ifdef GET_REGINFO_MC_DESC
#undef GET_REGINFO_MC_DESC

namespace llvm {

extern const int16_t SimRegDiffLists[] = {
  /* 0 */ 0,
};

extern const LaneBitmask SimLaneMaskLists[] = {
  /* 0 */ LaneBitmask(0xFFFFFFFFFFFFFFFF), 
};

extern const uint16_t SimSubRegIdxLists[] = {
  /* 0 */ 
  /* dummy */ 0
};


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif
extern const char SimRegStrings[] = {
  /* 0 */ "R10\000"
  /* 4 */ "R0\000"
  /* 7 */ "R11\000"
  /* 11 */ "R1\000"
  /* 14 */ "R12\000"
  /* 18 */ "R2\000"
  /* 21 */ "R13\000"
  /* 25 */ "R3\000"
  /* 28 */ "R14\000"
  /* 32 */ "R4\000"
  /* 35 */ "R15\000"
  /* 39 */ "R5\000"
  /* 42 */ "R6\000"
  /* 45 */ "R7\000"
  /* 48 */ "R8\000"
  /* 51 */ "R9\000"
};
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

extern const MCRegisterDesc SimRegDesc[] = { // Descriptors
  { 3, 0, 0, 0, 0, 0, 0, 0 },
  { 4, 0, 0, 0, 0, 0, 0, 0 },
  { 11, 0, 0, 0, 1, 0, 0, 0 },
  { 18, 0, 0, 0, 2, 0, 0, 0 },
  { 25, 0, 0, 0, 3, 0, 0, 0 },
  { 32, 0, 0, 0, 4, 0, 0, 0 },
  { 39, 0, 0, 0, 5, 0, 0, 0 },
  { 42, 0, 0, 0, 6, 0, 0, 0 },
  { 45, 0, 0, 0, 7, 0, 0, 0 },
  { 48, 0, 0, 0, 8, 0, 0, 0 },
  { 51, 0, 0, 0, 9, 0, 0, 0 },
  { 0, 0, 0, 0, 10, 0, 0, 0 },
  { 7, 0, 0, 0, 11, 0, 0, 0 },
  { 14, 0, 0, 0, 12, 0, 0, 0 },
  { 21, 0, 0, 0, 13, 0, 0, 0 },
  { 28, 0, 0, 0, 14, 0, 0, 0 },
  { 35, 0, 0, 0, 15, 0, 0, 0 },
};

extern const MCPhysReg SimRegUnitRoots[][2] = {
  { Sim::R0 },
  { Sim::R1 },
  { Sim::R2 },
  { Sim::R3 },
  { Sim::R4 },
  { Sim::R5 },
  { Sim::R6 },
  { Sim::R7 },
  { Sim::R8 },
  { Sim::R9 },
  { Sim::R10 },
  { Sim::R11 },
  { Sim::R12 },
  { Sim::R13 },
  { Sim::R14 },
  { Sim::R15 },
};

namespace {     // Register classes...
  // GPR Register Class...
  const MCPhysReg GPR[] = {
    Sim::R0, Sim::R1, Sim::R2, Sim::R3, Sim::R4, Sim::R5, Sim::R6, Sim::R7, Sim::R8, Sim::R9, Sim::R10, Sim::R11, Sim::R12, Sim::R13, Sim::R14, Sim::R15, 
  };

  // GPR Bit set.
  const uint8_t GPRBits[] = {
    0xfe, 0xff, 0x01, 
  };

} // end anonymous namespace


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif
extern const char SimRegClassStrings[] = {
  /* 0 */ "GPR\000"
};
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

extern const MCRegisterClass SimMCRegisterClasses[] = {
  { GPR, GPRBits, 0, 16, sizeof(GPRBits), Sim::GPRRegClassID, 32, 1, true, false },
};

extern const uint16_t SimRegEncodingTable[] = {
  0,
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
};
static inline void InitSimMCRegisterInfo(MCRegisterInfo *RI, unsigned RA, unsigned DwarfFlavour = 0, unsigned EHFlavour = 0, unsigned PC = 0) {
  RI->InitMCRegisterInfo(SimRegDesc, 17, RA, PC, SimMCRegisterClasses, 1, SimRegUnitRoots, 16, SimRegDiffLists, SimLaneMaskLists, SimRegStrings, SimRegClassStrings, SimSubRegIdxLists, 1,
SimRegEncodingTable);

}

} // end namespace llvm

#endif // GET_REGINFO_MC_DESC

/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Register Information Header Fragment                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


#ifdef GET_REGINFO_HEADER
#undef GET_REGINFO_HEADER

#include "llvm/CodeGen/TargetRegisterInfo.h"

namespace llvm {

class SimFrameLowering;

struct SimGenRegisterInfo : public TargetRegisterInfo {
  explicit SimGenRegisterInfo(unsigned RA, unsigned D = 0, unsigned E = 0,
      unsigned PC = 0, unsigned HwMode = 0);
  const RegClassWeight &getRegClassWeight(const TargetRegisterClass *RC) const override;
  unsigned getRegUnitWeight(unsigned RegUnit) const override;
  unsigned getNumRegPressureSets() const override;
  const char *getRegPressureSetName(unsigned Idx) const override;
  unsigned getRegPressureSetLimit(const MachineFunction &MF, unsigned Idx) const override;
  const int *getRegClassPressureSets(const TargetRegisterClass *RC) const override;
  const int *getRegUnitPressureSets(unsigned RegUnit) const override;
  ArrayRef<const char *> getRegMaskNames() const override;
  ArrayRef<const uint32_t *> getRegMasks() const override;
  bool isGeneralPurposeRegister(const MachineFunction &, MCRegister) const override;
  bool isGeneralPurposeRegisterClass(const TargetRegisterClass *RC) const override;
  bool isFixedRegister(const MachineFunction &, MCRegister) const override;
  bool isArgumentRegister(const MachineFunction &, MCRegister) const override;
  bool isConstantPhysReg(MCRegister PhysReg) const override final;
  /// Devirtualized TargetFrameLowering.
  static const SimFrameLowering *getFrameLowering(
      const MachineFunction &MF);
};

namespace Sim { // Register classes
  extern const TargetRegisterClass GPRRegClass;
} // end namespace Sim

} // end namespace llvm

#endif // GET_REGINFO_HEADER

/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Target Register and Register Classes Information                           *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


#ifdef GET_REGINFO_TARGET_DESC
#undef GET_REGINFO_TARGET_DESC

namespace llvm {

extern const MCRegisterClass SimMCRegisterClasses[];

static const MVT::SimpleValueType VTLists[] = {
  /* 0 */ MVT::i32, MVT::Other,
};

static const char *SubRegIndexNameTable[] = { "" };

static const TargetRegisterInfo::SubRegCoveredBits SubRegIdxRangeTable[] = {
  { 65535, 65535 },
};


static const LaneBitmask SubRegIndexLaneMaskTable[] = {
  LaneBitmask::getAll(),
 };



static const TargetRegisterInfo::RegClassInfo RegClassInfos[] = {
  // Mode = 0 (Default)
  { 32, 32, 32, /*VTLists+*/0 },    // GPR
};
static const uint32_t GPRSubClassMask[] = {
  0x00000001, 
};

static const uint16_t SuperRegIdxSeqs[] = {
  /* 0 */ 0,
};


namespace Sim {   // Register class instances
  extern const TargetRegisterClass GPRRegClass = {
    &SimMCRegisterClasses[GPRRegClassID],
    GPRSubClassMask,
    SuperRegIdxSeqs + 0,
    LaneBitmask(0x0000000000000001),
    0,
    false,
    0x00, /* TSFlags */
    false, /* HasDisjunctSubRegs */
    false, /* CoveredBySubRegs */
    nullptr, 0,
    nullptr
  };

} // end namespace Sim

namespace {
  const TargetRegisterClass *const RegisterClasses[] = {
    &Sim::GPRRegClass,
  };
} // end anonymous namespace

static const uint8_t CostPerUseTable[] = { 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };


static const bool InAllocatableClassTable[] = { 
false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, };


static const TargetRegisterInfoDesc SimRegInfoDesc = { // Extra Descriptors
CostPerUseTable, 1, InAllocatableClassTable};

/// Get the weight in units of pressure for this register class.
const RegClassWeight &SimGenRegisterInfo::
getRegClassWeight(const TargetRegisterClass *RC) const {
  static const RegClassWeight RCWeightTable[] = {
    {1, 16},  	// GPR
  };
  return RCWeightTable[RC->getID()];
}

/// Get the weight in units of pressure for this register unit.
unsigned SimGenRegisterInfo::
getRegUnitWeight(unsigned RegUnit) const {
  assert(RegUnit < 16 && "invalid register unit");
  // All register units have unit weight.
  return 1;
}


// Get the number of dimensions of register pressure.
unsigned SimGenRegisterInfo::getNumRegPressureSets() const {
  return 1;
}

// Get the name of this register unit pressure set.
const char *SimGenRegisterInfo::
getRegPressureSetName(unsigned Idx) const {
  static const char *PressureNameTable[] = {
    "GPR",
  };
  return PressureNameTable[Idx];
}

// Get the register unit pressure limit for this dimension.
// This limit must be adjusted dynamically for reserved registers.
unsigned SimGenRegisterInfo::
getRegPressureSetLimit(const MachineFunction &MF, unsigned Idx) const {
  static const uint8_t PressureLimitTable[] = {
    16,  	// 0: GPR
  };
  return PressureLimitTable[Idx];
}

/// Table of pressure sets per register class or unit.
static const int RCSetsTable[] = {
  /* 0 */ 0, -1,
};

/// Get the dimensions of register pressure impacted by this register class.
/// Returns a -1 terminated array of pressure set IDs
const int *SimGenRegisterInfo::
getRegClassPressureSets(const TargetRegisterClass *RC) const {
  static const uint8_t RCSetStartTable[] = {
    0,};
  return &RCSetsTable[RCSetStartTable[RC->getID()]];
}

/// Get the dimensions of register pressure impacted by this register unit.
/// Returns a -1 terminated array of pressure set IDs
const int *SimGenRegisterInfo::
getRegUnitPressureSets(unsigned RegUnit) const {
  assert(RegUnit < 16 && "invalid register unit");
  static const uint8_t RUSetStartTable[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
  return &RCSetsTable[RUSetStartTable[RegUnit]];
}

extern const MCRegisterDesc SimRegDesc[];
extern const int16_t SimRegDiffLists[];
extern const LaneBitmask SimLaneMaskLists[];
extern const char SimRegStrings[];
extern const char SimRegClassStrings[];
extern const MCPhysReg SimRegUnitRoots[][2];
extern const uint16_t SimSubRegIdxLists[];
extern const uint16_t SimRegEncodingTable[];
SimGenRegisterInfo::
SimGenRegisterInfo(unsigned RA, unsigned DwarfFlavour, unsigned EHFlavour,
      unsigned PC, unsigned HwMode)
  : TargetRegisterInfo(&SimRegInfoDesc, RegisterClasses, RegisterClasses+1,
             SubRegIndexNameTable, SubRegIdxRangeTable, SubRegIndexLaneMaskTable,
             LaneBitmask(0xFFFFFFFFFFFFFFFF), RegClassInfos, VTLists, HwMode) {
  InitMCRegisterInfo(SimRegDesc, 17, RA, PC,
                     SimMCRegisterClasses, 1,
                     SimRegUnitRoots,
                     16,
                     SimRegDiffLists,
                     SimLaneMaskLists,
                     SimRegStrings,
                     SimRegClassStrings,
                     SimSubRegIdxLists,
                     1,
                     SimRegEncodingTable);

}



ArrayRef<const uint32_t *> SimGenRegisterInfo::getRegMasks() const {
  return {};
}

bool SimGenRegisterInfo::
isGeneralPurposeRegister(const MachineFunction &MF, MCRegister PhysReg) const {
  return
      false;
}

bool SimGenRegisterInfo::
isGeneralPurposeRegisterClass(const TargetRegisterClass *RC) const {
  return
      false;
}

bool SimGenRegisterInfo::
isFixedRegister(const MachineFunction &MF, MCRegister PhysReg) const {
  return
      false;
}

bool SimGenRegisterInfo::
isArgumentRegister(const MachineFunction &MF, MCRegister PhysReg) const {
  return
      false;
}

bool SimGenRegisterInfo::
isConstantPhysReg(MCRegister PhysReg) const {
  return
      false;
}

ArrayRef<const char *> SimGenRegisterInfo::getRegMaskNames() const {
  return {};
}

const SimFrameLowering *
SimGenRegisterInfo::getFrameLowering(const MachineFunction &MF) {
  return static_cast<const SimFrameLowering *>(
      MF.getSubtarget().getFrameLowering());
}

} // end namespace llvm

#endif // GET_REGINFO_TARGET_DESC

