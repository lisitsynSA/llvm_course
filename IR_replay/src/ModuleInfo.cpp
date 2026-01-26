#include "../include/ModuleInfo.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"

using namespace llvm;

uint64_t ModuleInfo::OpID = 0;

ModuleInfo::ModuleInfo(std::string path, LLVMContext &C) : Ctx(C) {
  outs() << "[UNITOOL] Load module " << path << "\n";
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
  FuncsMap[OpID] = &F;
  Id2FuncName[OpID] = F.getName().str();
  OpID++;

  for (auto &BB : F) {
    for (auto &I : BB) {
      PrepareInstrInfo(I, F.getName());
    }
  }
}

void ModuleInfo::PrepareInstrInfo(Instruction &I, StringRef FuncName) {
  Id2FuncName[OpID] = FuncName.str();
  if (auto *Call = dyn_cast<CallInst>(&I)) {
    CallsMap[OpID++] = Call;
  }
  if (auto *RetInst = dyn_cast<ReturnInst>(&I)) {
    RetsMap[OpID++] = RetInst;
  }
  if (auto *Load = dyn_cast<LoadInst>(&I)) {
    LoadsMap[OpID++] = Load;
  }
  if (auto *Store = dyn_cast<StoreInst>(&I)) {
    StoresMap[OpID++] = Store;
  }
  if (auto *Gep = dyn_cast<GetElementPtrInst>(&I)) {
    GepsMap[OpID++] = Gep;
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
