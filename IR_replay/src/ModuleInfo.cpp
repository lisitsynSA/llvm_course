#include "../include/ModuleInfo.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"

using namespace llvm;

ModuleInfo::ModuleInfo(std::string path, LLVMContext &C) : Ctx(C) {
  outs() << "[UNITOOL] Load " << path << "\n";
  // Read IR file
  SMDiagnostic Err;
  M = parseIRFile(path, Err, Ctx);
  if (!M) {
    errs() << "Cannot open inpult file: " << path << '\n';
    Err.print("ModuleInfo", errs());
    return;
  }

  // Prepare Function Info
  for (auto &F : *M) {
    PrepareFuncInfo(F);
  }
}

void ModuleInfo::PrepareFuncInfo(Function &F) {
  static uint64_t FuncID = 0;
  FuncsMap[FuncID] = &F;
  FuncId2Name[FuncID] = F.getName().str();
  FuncID++;

  for (auto &BB : F) {
    for (auto &I : BB) {
      PrepareInstrInfo(I);
    }
  }
}

void ModuleInfo::PrepareInstrInfo(Instruction &I) {
  static uint64_t InstrID = 0;
  if (auto *Call = dyn_cast<CallInst>(&I)) {
    CallsMap[InstrID++] = Call;
  }
  if (auto *RetInst = dyn_cast<ReturnInst>(&I)) {
    RetsMap[InstrID++] = RetInst;
  }
  if (auto *Load = dyn_cast<LoadInst>(&I)) {
    LoadsMap[InstrID++] = Load;
  }
  if (auto *Store = dyn_cast<StoreInst>(&I)) {
    StoresMap[InstrID++] = Store;
  }
  if (auto *Gep = dyn_cast<GetElementPtrInst>(&I)) {
    GepsMap[InstrID++] = Gep;
  }
}

void ModuleInfo::dumpModule(std::string path) {
  std::error_code EC;
  raw_fd_ostream OS(path, EC);
  if (EC) {
    errs() << "Cannot open output file: " << path << "\n"
           << EC.message() << '\n';
    return;
  }
  outs() << "[UNITOOL] Dump " << path << "\n";
  M->print(OS, nullptr);
  OS.close();
}
