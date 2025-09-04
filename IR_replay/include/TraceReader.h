#ifndef TRACE_READER_H
#define TRACE_READER_H
#include "trace.h"
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

// Запись о вызове функции
struct CallEvent {
  uint64_t func_id;
  std::string func_name;
  std::vector<uint64_t> args;
  bool is_external;
  uint64_t return_value; // для RETURN и EXTERNAL_CALL
};

class TraceReader {
  std::ifstream file;
  std::vector<CallEvent> callSequence; // Полная последовательность вызовов
  std::stack<CallEvent> callStack;     // Для сопоставления CALL и RETURN

  std::map<uint64_t, std::string> funcIdToName; // ID → имя

public:
  bool parse(const std::string &tracePath);

  const std::vector<CallEvent> &getCallSequence() const { return callSequence; }

  void dumpSequence() const;
};

#endif