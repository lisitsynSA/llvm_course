#ifndef TRACE_INFO_H
#define TRACE_INFO_H

#include <vector>
#include <string>
class ModuleInfo;
class TraceRecord;

class TraceInfo {
    std::vector<TraceRecord> Trace;
public:
    TraceInfo(std::string path);
    void dump(ModuleInfo *M = nullptr);
};

#endif // TRACE_INFO_H
