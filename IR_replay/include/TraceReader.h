#ifndef TRACE_READER_H
#define TRACE_READER_H

#include "trace.h"
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

// Запись о вызове функции
struct CallEvent {
  uint64_t func_id;
  std::vector<uint64_t> args;
  bool is_external;
  uint64_t return_value; // для RETURN и EXTERNAL_CALL
};

class TraceReader {
  std::vector<CallEvent> callSequence; // Полная последовательность вызовов
  std::stack<CallEvent> callStack;     // Для сопоставления CALL и RETURN

  std::unordered_map<uint64_t, std::string> funcIdToName; // ID → имя

public:
  bool loadFuncMap(const std::string &traceFuncPath);
  bool parse(const std::string &tracePath);
  std::unordered_map<uint64_t, std::string> &getFuncMap() {
    return funcIdToName;
  }

  const std::vector<CallEvent> &getCallSequence() const { return callSequence; }

  void dumpSequence();
};

#endif