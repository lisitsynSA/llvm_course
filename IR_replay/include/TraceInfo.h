#ifndef TRACE_INFO_H
#define TRACE_INFO_H

#include "../include/TraceRecord.h"
#include <string>
#include <vector>
class ModuleInfo;

class TraceInfo {
  void parseFile(std::ifstream &file);

public:
  TraceInfo(std::string path);
  void dump(ModuleInfo *M = nullptr);
  std::vector<TraceRecord> Trace;
};

#endif // TRACE_INFO_H
