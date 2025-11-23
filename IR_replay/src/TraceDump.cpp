#include "../include/TraceReader.h"
#include "iostream"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <trace_file>\n";
    return 1;
  }
  TraceReader Reader;

  if (!Reader.parse(argv[1]))
    return 1;
  return 0;
}
