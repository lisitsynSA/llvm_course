#ifndef TRACE_INFO_H
#define TRACE_INFO_H

#include "../include/TraceRecord.h"
#include <string>
#include <vector>
class ModuleInfo;

class TraceInfo {
  std::vector<TraceRecord> Trace;
  void parseFile(std::ifstream &file);

public:
  TraceInfo(std::string path);
  void dump(ModuleInfo *M = nullptr);
};

#endif // TRACE_INFO_H
