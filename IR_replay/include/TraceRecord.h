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
  void printArgs(std::string name) const;
  std::string printFuncName(ModuleInfo *M) const;
  void printFuncEvent(ModuleInfo *M) const;
  void printRetEvent(ModuleInfo *M) const;
  void printCallEvent(ModuleInfo *M) const;
  void printMemEvent(ModuleInfo *M) const;

public:
  TraceRecord(TraceHeader &hdr, std::ifstream &file);
  void dump(ModuleInfo *M = nullptr) const;
};

#endif // TRACE_RECORD_H
