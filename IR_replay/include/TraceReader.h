#ifndef TRACE_READER_H
#define TRACE_READER_H

#include "trace.h"
#include <fstream>
#include <map>
#include <stack>
#include <string>
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