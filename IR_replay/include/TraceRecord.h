#ifndef TRACE_RECORD_H
#define TRACE_RECORD_H

#include "trace.h"
#include <string>
#include <vector>

class ModuleInfo;

class TraceRecord {
public:
  TraceHeader Hdr;
  std::vector<uint64_t> Args;
  uint64_t Ret;
  MemoryEvent Mem;

private:
  bool readArray(std::ifstream &file);
  void printArgs(std::string name);
  std::string printFuncName(ModuleInfo *M);
  void printFuncEvent(ModuleInfo *M);
  void printRetEvent(ModuleInfo *M);
  void printCallEvent(ModuleInfo *M);
  void printMemEvent(ModuleInfo *M);

public:
  TraceRecord(TraceHeader &hdr, std::ifstream &file);
  void dump(ModuleInfo *M = nullptr);
};

#endif // TRACE_RECORD_H
