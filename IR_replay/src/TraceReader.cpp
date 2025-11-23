#include "../include/TraceReader.h"
#include "iostream"

using namespace std;

bool TraceReader::parse(const string &tracePath) {
  file.open(tracePath, ios::binary);
  if (!file.is_open()) {
    cerr << "Cannot open trace file: " << tracePath << '\n';
    return false;
  }

  TraceHeader hdr;
  while (file.read(reinterpret_cast<char *>(&hdr), sizeof(hdr))) {
    vector<char> nameBuf(hdr.name_len + 1);
    if (!file.read(nameBuf.data(), hdr.name_len))
      break;
    nameBuf[hdr.name_len] = '\0';
    string name(nameBuf.data());

    if (hdr.type == EVENT_CALL) {
      cout << "[CALL] ";
      CallEvent call;
      call.func_id = hdr.func_id;
      call.func_name = name;
      cout << name;
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
      cout << "[RET] " << name;
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
      call.func_name = name;
      call.is_external = true;
      cout << name;

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

void TraceReader::dumpSequence() const {
  cout << "; Call sequence:\n";
  for (const auto &ev : callSequence) {
    cout << "; call " << ev.func_name << " with " << ev.args.size() << " args";
    if (ev.is_external)
      cout << " [external]";
    cout << '\n';
  }
}
