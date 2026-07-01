#include "../include/ReplayGen.h"
#include <utility>

using namespace llvm;

void ReplayGen::handleMem(TraceRecord &Rec) {
  outs() << "# MEM " << Rec.Mem.type << " " << Rec.Mem.size << "bit ["
         << Rec.Mem.address << "]: ";
  if (Rec.Mem.type == MEM_LOAD) {
    handleLoad(Rec);
  } else if (Rec.Mem.type == MEM_STORE) {
    handleStore(Rec);
  } else {
    handleGEP(Rec);
  }
}

void ReplayGen::handleLoad(TraceRecord &Rec) {
  MemMap[Rec.Mem.address] = Rec.Mem.value;
  outs() << Rec.Mem.value << '\n';
}

void ReplayGen::handleStore(TraceRecord &Rec) {
  outs() << Rec.Mem.value << '\n';
}

void ReplayGen::handleGEP(TraceRecord &Rec) {
  for (uint64_t i = 0; i < Rec.Args.size(); i += 2) {
    outs() << "\n\t" << Rec.Args[i] << " " << Rec.Args[i + 1];
    for (uint64_t adr = Rec.Args[i]; adr <= Rec.Args[i + 1]; adr += BYTE_SIZE) {
      // TODO: Check no rewrite
      MemMap[adr] = 0;
    }
    if (i != 0) {
      outs() << "\n#  [" << Rec.Args[i - 1] << "]: " << Rec.Args[i];
      MemMap[Rec.Args[i - 1]] = Rec.Args[i];
    }
  }
  outs() << '\n';
}

void ReplayGen::AddArray(uint64_t Addr, uint64_t Size) {
  if (Addr == 0)
    return;
  outs() << "# MEM ARRAY [" << Size << " x i64] at " << Addr << '\n';
  ArrayType *ArrayTy = ArrayType::get(Int64Ty, Size);
  GlobalVariable *Array = new GlobalVariable(*ExtMod, ArrayTy, false,
                                             GlobalValue::PrivateLinkage, 0);
  Array->setInitializer(ConstantAggregateZero::get(ArrayTy));
  for (uint64_t i = 0; i < Size; i++) {
    AllocMap[Addr + i * BYTE_SIZE] = std::make_pair(Array, i);
  }
}

void ReplayGen::prepareArrays() {
  uint64_t CurPtr = 0;
  uint64_t CurSize = 0;
  for (auto [Addr, Value] : MemMap) {
    if (CurPtr + CurSize != Addr) {
      AddArray(CurPtr, CurSize / BYTE_SIZE);
      CurPtr = Addr;
      CurSize = BYTE_SIZE;
    } else {
      CurSize += BYTE_SIZE;
    }
  }
  AddArray(CurPtr, CurSize / BYTE_SIZE);
}

Value *ReplayGen::getMem(IRBuilder<> &Builder, uint64_t Addr) {
  auto &[Array, Offset] = AllocMap[Addr];
  Value *GEP = Builder.CreateConstGEP2_64(Int64PtrTy, Array, 0, Offset);
  outs() << "# MEM USE " << Addr << "[" << Offset << "]\n";
  return GEP;
}
