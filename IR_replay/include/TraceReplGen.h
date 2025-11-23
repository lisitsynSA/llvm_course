#ifndef TRACE_REPLGEN_H
#define TRACE_REPLGEN_H
#include "trace.h"
#include "TraceReader.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <variant>
#include <vector>

class TraceReplayGenerator {
  llvm::LLVMContext &Context;
  std::unique_ptr<llvm::Module> OriginalModule;

  std::map<std::string, std::vector<uint64_t>> MockReturns;
  std::map<std::string, std::vector<std::vector<uint64_t>>>
      MockArgs; // для отладки
  std::map<std::string, llvm::FunctionType *> FuncNameToType;

  const std::vector<CallEvent> *CallSequence = nullptr;

public:
  TraceReplayGenerator(llvm::LLVMContext &C) : Context(C) {}

  bool loadOriginalModule(const std::string &llPath);

  void populateMocks(const std::vector<CallEvent> &calls);

  llvm::Function *createMockFunction(const std::string &Name, llvm::FunctionType *FT);

  llvm::Value *createValueFromBits(llvm::IRBuilder<> &Builder, llvm::Type *Ty, uint64_t bits);

  bool generate();

  void saveToFile(const std::string &outputPath);
};

#endif