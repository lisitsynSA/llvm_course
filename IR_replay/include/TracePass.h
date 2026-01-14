#ifndef TRACE_PASS_H
#define TRACE_PASS_H
// LLVM Pass для инструментации модуля с целью сбора runtime IR трассы

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace {
struct TraceInstrumentationPass
    : public llvm::PassInfoMixin<TraceInstrumentationPass> {
  // Указатели на часто используемые типы
  llvm::Type *VoidTy;
  llvm::IntegerType *Int8Ty;
  llvm::IntegerType *Int64Ty;
  llvm::PointerType *Int64PtrTy;
  llvm::PointerType *Int8PtrTy;
  llvm::FunctionType *TraceCallFnTy;
  llvm::FunctionType *TraceReturnFnTy;
  llvm::FunctionType *TraceExternalCallFnTy;
  llvm::FunctionType *TraceMemFnTy;

  // Указатели на вставляемые функции трассировки
  llvm::FunctionCallee TraceCallFn;
  llvm::FunctionCallee TraceReturnFn;
  llvm::FunctionCallee TraceExternalCallFn;
  llvm::FunctionCallee TraceMemFn;
  std::unordered_map<std::string, uint64_t> FuncIdMap;

  static int MemId;
  std::set<llvm::Value *> InsertedInstrs;

  bool isInstrInserted(llvm::Value *I) {
    return InsertedInstrs.find(I) != InsertedInstrs.end();
  }

  bool isFuncLogger(llvm::StringRef name) {
    return name == "trace_called" || name == "trace_external_call" ||
           name == "trace_return" || name == "trace_memory";
  }

  // Инициализация типов и функций трассировки
  void initTracingFunctions(llvm::Module &M);

  // Генерация уникального ID для функции
  uint64_t getFunctionId(const llvm::Function &F);

  llvm::Value *valueToI64(llvm::IRBuilder<> &Builder, llvm::Value *V);

  void instrumentCall(llvm::IRBuilder<> &Builder, llvm::CallInst *Call);

  void addMemoryTrace(llvm::IRBuilder<> &Builder, llvm::Value *V,
                      llvm::Value *A, llvm::Instruction *I, uint64_t type);

  void addGepTrace(llvm::IRBuilder<> &Builder, llvm::GetElementPtrInst *Gep);

  void instrumentFuncStart(llvm::IRBuilder<> &Builder, llvm::Function &F);

  // Инструментация тела функции: запись вызова и возврата
  void instrumentFunction(llvm::Function &F, llvm::Module &M);

  void dumpFuncIdMap();

  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &MAM);
};

} // namespace
#endif