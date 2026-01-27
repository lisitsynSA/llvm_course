#ifndef MODULE_INFO_H
#define MODULE_INFO_H

#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include <string>
#include <unordered_map>

class ModuleInfo {
protected:
  llvm::LLVMContext &Ctx;
  std::unique_ptr<llvm::Module> M;

public:
  // Functions Info
  std::unordered_map<uint64_t, llvm::Function *> FuncsMap;
  std::unordered_map<uint64_t, llvm::Function *> Id2Func;

  // Instructions Info
  std::unordered_map<uint64_t, llvm::CallInst *> CallsMap;
  std::unordered_map<uint64_t, llvm::ReturnInst *> RetsMap;
  std::unordered_map<uint64_t, llvm::LoadInst *> LoadsMap;
  std::unordered_map<uint64_t, llvm::StoreInst *> StoresMap;
  std::unordered_map<uint64_t, llvm::GetElementPtrInst *> GepsMap;

  ModuleInfo(std::string path, llvm::LLVMContext &C);
  void dumpModule(std::string path);
  llvm::Function *getCallee(uint64_t id);

private:
  void PrepareFuncInfo(llvm::Function &F);
  void PrepareInstrInfo(llvm::Instruction &I, llvm::Function &F);
  static uint64_t OpID;
};

#endif // MODULE_INFO_H
