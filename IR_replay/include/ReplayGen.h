#ifndef REPLAY_GEN_H
#define REPLAY_GEN_H

#include "ModuleInstrument.h"
#include "TraceInfo.h"
#include <cstdint>
#include <llvm/IR/DerivedTypes.h>
#include <map>
#include <memory>

class ReplayGen : public ModuleInstrument {
  std::unordered_map<llvm::Function *, llvm::FunctionCallee> MocksMap;
  std::vector<TraceRecord *> ReplayEntryPoints;
  std::unordered_map<llvm::Function *, std::vector<TraceRecord *>>
      ExtFuncsCalls;
  llvm::Function *LastExtFunc = nullptr;
  std::unique_ptr<llvm::Module> ExtMod;

  void collectInfo(TraceInfo &trace);
  void removeOptnoneAttrs();
  llvm::Value *createValueFromBits(llvm::IRBuilder<> &Builder, llvm::Type *Ty,
                                   uint64_t bits);
  llvm::Function *createMockFunction(llvm::Function *F, bool isAllow);
  void createMocks(std::string &AllowFunsFile);
  void createOrigCall(llvm::IRBuilder<> &Builder, TraceRecord *Rec);
  void replayChain();

  // Memory Image Part
  std::map<uint64_t, uint8_t> MemMap;
  std::vector<std::unordered_map<uint64_t, uint8_t>> MemSnapshots;
  std::unordered_map<uint64_t, std::pair<llvm::Value *, uint64_t>> AllocMap;
  void handleMem(TraceRecord &Rec);
  void handleLoad(TraceRecord &Rec);
  void handleStore(TraceRecord &Rec);
  void handleGEP(TraceRecord &Rec);
  void AddArray(uint64_t Addr, uint64_t Size);
  void prepareArrays();
  llvm::Value *getMem(llvm::IRBuilder<> &Builder, uint64_t Addr);
  bool inMem(uint64_t Addr) { return MemMap.find(Addr) != MemMap.end(); }

public:
  ReplayGen(std::string path, llvm::LLVMContext &C)
      : ModuleInstrument(path, C) {
    ExtMod = std::make_unique<llvm::Module>("Compensation", C);
    ExtMod->setTargetTriple(M->getTargetTriple());
  }
  void replayGeneration(TraceInfo &trace, std::string &AllowFunsFile,
                        bool Debug = false);
  void addPrepCall();
  void dumpModules(std::string path, std::string extPath) const {
    dumpModule(path);
    dumpModule(extPath, ExtMod.get());
  }
};

#endif // REPLAY_GEN_H
