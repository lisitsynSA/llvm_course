#ifndef REPLAY_GEN_H
#define REPLAY_GEN_H

#include "ModuleInstrument.h"
#include "TraceInfo.h"

class ReplayGen : public ModuleInstrument {
  std::unordered_map<llvm::Function *, llvm::Function *> MocksMap;
  std::vector<TraceRecord *> ReplayRecs;
  std::unordered_map<llvm::Function *, std::vector<TraceRecord *>> ExtFuncsInfo;

  void collectInfo(TraceInfo &trace);
  llvm::Value *createValueFromBits(llvm::IRBuilder<> &Builder, llvm::Type *Ty,
                                   uint64_t bits);
  llvm::Function *createMockFunction(llvm::Function *F);
  void createMocks();
  void createOrigCall(llvm::IRBuilder<> &Builder, TraceRecord *Rec);
  void replayChain();

public:
  ReplayGen(std::string path, llvm::LLVMContext &C)
      : ModuleInstrument(path, C) {}
  void replayGeneration(TraceInfo &trace);
};

#endif // REPLAY_GEN_H
