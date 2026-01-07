#include "../include/TraceReader.h"
#include "iostream"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <trace_func_file> <trace_file>\n";
    return 1;
  }
  TraceReader Reader;

  if (!Reader.loadFuncMap(argv[1]))
    return 1;
  if (!Reader.parse(argv[2]))
    return 1;
  return 0;
}
