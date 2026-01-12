#include "../include/TraceReader.h"
#include "iostream"

using namespace std;

bool TraceReader::loadFuncMap(const std::string &traceFuncPath) {
  std::ifstream file(traceFuncPath);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << traceFuncPath << '\n';
    return false;
  }
  std::string name;
  uint64_t id = 0;
  while(!file.eof()) {
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

bool TraceReader::parse(const std::string &tracePath) {
  std::ifstream file(tracePath, ios::binary);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << tracePath << '\n';
    return false;
  }

  TraceHeader hdr;
  MemoryEvent memEvent;
  while (file.read(reinterpret_cast<char *>(&hdr), sizeof(hdr))) {
    cout << hdr.timestamp << " ";
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
        for (uint64_t &arg: call.args) {
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

      cout << " (ret " << ret_value << ')';
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
      cout << " (" << num_args << " arg:";
      if (num_args > 0) {
        if (!file.read(reinterpret_cast<char *>(call.args.data()),
                       sizeof(uint64_t) * num_args))
          break;
        for (uint64_t &arg: call.args) {
          cout << ' ' << arg;
        }
      }
      cout << ')';

      if (!file.read(reinterpret_cast<char *>(&call.return_value),
                     sizeof(call.return_value)))
        break;
      cout << " (ret " << call.return_value << ')';

      callSequence.push_back(call);
    } else if (hdr.type == EVENT_MEMOP) {
      cout << "[MEMOP] ";
      if (!file.read(reinterpret_cast<char *>(&memEvent), sizeof(memEvent)))
        break;
      cout << memEvent.memop_id << " " << memEvent.size << " " << memEvent.address;
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
    cout << "; call " << funcIdToName[ev.func_id] << " with " << ev.args.size() << " args";
    if (ev.is_external)
      cout << " [external]";
    cout << '\n';
  }
}
