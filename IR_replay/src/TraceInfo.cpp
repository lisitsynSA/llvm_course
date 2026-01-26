#include "../include/TraceInfo.h"
#include "../include/TraceRecord.h"
#include "../include/trace.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/time.h>

using namespace std;

static void printTime(uint64_t tv_sec) {
  const uint64_t SEC_PER_DAY = 86400;
  const uint64_t SEC_PER_HOUR = 3600;
  const uint64_t SEC_PER_MIN = 60;
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  long hms = tv_sec % SEC_PER_DAY;
  hms += tz.tz_dsttime * SEC_PER_HOUR;
  hms -= tz.tz_minuteswest * SEC_PER_MIN;
  hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
  int hour = hms / SEC_PER_HOUR;
  int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
  int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
  printf("TIME: %02d:%02d:%02d\n", hour, min, sec);
}

void TraceInfo::parseFile(ifstream &file) {
  TraceHeader hdr;
  MemoryEvent memEvent;
  uint64_t tv_sec = 0;
  while (file.read(reinterpret_cast<char *>(&hdr), sizeof(hdr))) {
    Trace.push_back(TraceRecord(hdr, file));
  }
}

TraceInfo::TraceInfo(string path) {
  cout << "[UNITOOL] Load trace " << path << "\n";
  ifstream file(path, ios::binary);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << path << '\n';
    return;
  }

  parseFile(file);

  if (file.bad()) {
    cerr << "Error reading trace file: " << path << '\n';
  }

  file.close();
}

void TraceInfo::dump(ModuleInfo *M) {
  for (auto &Rec : Trace) {
    Rec.dump(M);
  }
}