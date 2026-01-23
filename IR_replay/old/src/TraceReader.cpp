#include "../include/TraceReader.h"
#include <iomanip>
#include <iostream>
#include <sys/time.h>

using namespace std;

bool TraceReader::loadFuncMap(const std::string &traceFuncPath) {
  std::ifstream file(traceFuncPath);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << traceFuncPath << '\n';
    return false;
  }
  std::string name;
  uint64_t id = 0;
  while (!file.eof()) {
    file >> name >> id;
    funcIdToName[id] = name;
  }
  if (file.bad()) {
    cerr << "Error reading trace file\n";
    return false;
  }

  file.close();
  return true;
}

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

bool TraceReader::parse(const std::string &tracePath) {
  std::ifstream file(tracePath, ios::binary);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << tracePath << '\n';
    return false;
  }

  TraceHeader hdr;
  MemoryEvent memEvent;
  uint64_t tv_sec = 0;
  while (file.read(reinterpret_cast<char *>(&hdr), sizeof(hdr))) {
    if (hdr.timestamp / 1000000 != tv_sec) {
      tv_sec = hdr.timestamp / 1000000;
      printTime(tv_sec);
    }
    cout << setw(6) << hdr.timestamp % 1000000 << "u ";
    if (hdr.type == EVENT_CALL) {
      cout << "[CALL] ";
      CallEvent call;
      call.func_id = hdr.func_id;
      cout << funcIdToName[hdr.func_id];
      call.is_external = false;

      uint64_t num_args;
      if (!file.read(reinterpret_cast<char *>(&num_args), sizeof(num_args)))
        break;
      cout << " (" << num_args << " arg:";
      call.args.resize(num_args);
      if (num_args > 0) {
        if (!file.read(reinterpret_cast<char *>(call.args.data()),
                       sizeof(uint64_t) * num_args))
          break;
        for (uint64_t &arg : call.args) {
          cout << ' ' << arg;
        }
      }
      cout << ')';

      callSequence.push_back(call);
    } else if (hdr.type == EVENT_RETURN) {
      cout << "[RET] " << funcIdToName[hdr.func_id];
      uint64_t ret_value;
      if (!file.read(reinterpret_cast<char *>(&ret_value), sizeof(ret_value)))
        break;

      cout << " ret " << ret_value;
      // Можно закрыть CALL из стека, если нужно
      if (!callStack.empty()) {
        callStack.pop();
      }
    } else if (hdr.type == EVENT_EXTERNAL_CALL) {
      cout << "[EXTCALL] ";
      CallEvent call;
      call.func_id = hdr.func_id;
      call.is_external = true;
      cout << funcIdToName[hdr.func_id];

      uint64_t num_args;
      if (!file.read(reinterpret_cast<char *>(&num_args), sizeof(num_args)))
        break;
      call.args.resize(num_args);
      cout << " (" << num_args << " args:";
      if (num_args > 0) {
        if (!file.read(reinterpret_cast<char *>(call.args.data()),
                       sizeof(uint64_t) * num_args))
          break;
        for (uint64_t &arg : call.args) {
          cout << ' ' << arg;
        }
      }
      cout << ')';

      if (!file.read(reinterpret_cast<char *>(&call.return_value),
                     sizeof(call.return_value)))
        break;
      cout << " ret " << call.return_value;

      callSequence.push_back(call);
    } else if (hdr.type == EVENT_MEMOP) {
      cout << "[MEMOP] ";
      if (!file.read(reinterpret_cast<char *>(&memEvent), sizeof(memEvent)))
        break;
      cout << memEvent.type << " " << memEvent.memop_id << " " << memEvent.size
           << "bit [0x" << hex << memEvent.address << dec;
      if (memEvent.type == MEM_UPD) {
        cout << " = " << memEvent.address << "]";
      } else {
        cout << "]: " << memEvent.value;
      }
      if (memEvent.type == MEM_GEP) {
        std::vector<uint64_t> ptrs;
        if (memEvent.value > 0) {
          cout << "\n                [0x" << hex << memEvent.address << "]";
          ptrs.resize(memEvent.value);
          if (!file.read(reinterpret_cast<char *>(ptrs.data()),
                         sizeof(uint64_t) * memEvent.value))
            break;
          for (uint64_t &ptr : ptrs) {
            cout << " -> [0x" << ptr << "]";
          }
          cout << dec;
        }
      }
    } else {
      cerr << "Unknown event type: " << (int)hdr.type << '\n';
      return false;
    }
    cout << '\n';
  }

  if (file.bad()) {
    cerr << "Error reading trace file\n";
    return false;
  }

  file.close();
  return true;
}

void TraceReader::dumpSequence() {
  cout << "; Call sequence:\n";
  for (auto &ev : callSequence) {
    cout << "; call " << funcIdToName[ev.func_id] << " with " << ev.args.size()
         << " args";
    if (ev.is_external)
      cout << " [external]";
    cout << '\n';
  }
}
