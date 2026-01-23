#ifndef MODULE_INSTRUMENT_H
#define MODULE_INSTRUMENT_H

#include "ModuleInfo.h"
#include "TraceInfo.h"
#include "llvm/IR/IRBuilder.h"

class ModuleInstrument : public ModuleInfo {
  // Types
  llvm::Type *VoidTy;
  llvm::IntegerType *Int8Ty;
  llvm::IntegerType *Int64Ty;
  llvm::PointerType *Int64PtrTy;
  llvm::PointerType *Int8PtrTy;
  llvm::FunctionType *TraceCallFnTy;
  llvm::FunctionType *TraceReturnFnTy;
  llvm::FunctionType *TraceExternalCallFnTy;
  llvm::FunctionType *TraceMemFnTy;

  // Instrumentation functions
  llvm::FunctionCallee TraceCallFn;
  llvm::FunctionCallee TraceReturnFn;
  llvm::FunctionCallee TraceExternalCallFn;
  llvm::FunctionCallee TraceMemFn;

  // Intrumentation
  bool isFuncLogger(llvm::StringRef name);
  void initTracingFunctions();
  llvm::Value *getTypeSize(llvm::IRBuilder<> &Builder, llvm::Type *Ty) {
    if (Ty->isPointerTy()) {
      return Builder.getInt64(64);
    } else {
      return Builder.getInt64(Ty->getScalarSizeInBits());
    }
  }
  llvm::Value *valueToI64(llvm::IRBuilder<> &Builder, llvm::Value *V);
  llvm::Value *instrumentArray(llvm::IRBuilder<> &Builder,
                               std::vector<llvm::Value *> &Arr);

  void instrumentCall(llvm::CallInst *Call, uint64_t Id);
  void instrumentRet(llvm::ReturnInst *Ret, uint64_t Id);
  void instrumentMem(llvm::Value *V, llvm::Value *A, llvm::Instruction *I,
                     uint64_t type, uint64_t Id);
  void instrumentGep(llvm::GetElementPtrInst *Gep, uint64_t Id);
  void instrumentFuncStart(llvm::Function *F, uint64_t Id);

public:
  ModuleInstrument(std::string path, llvm::LLVMContext &C);
  void InstrumentModule();
  // bool ReplayGen(TraceInfo &T, ModuleInfo &M);
  // bool ExtReplayGen(TraceInfo &T, ModuleInfo &M);
};

#endif // MODULE_INSTRUMENT_H
