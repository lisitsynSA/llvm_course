#include "TraceReader.h"

using namespace llvm;
// === Парсер трассы с восстановлением последовательности ===

bool TraceReader::parse(const std::string &tracePath) {
  file.open(tracePath, std::ios::binary);
  if (!file.is_open()) {
    errs() << "Cannot open trace file: " << tracePath << "\n";
    return false;
  }

  TraceHeader hdr;
  while (file.read(reinterpret_cast<char *>(&hdr), sizeof(hdr))) {
    outs() << "[READ]\n";
    std::vector<char> nameBuf(hdr.name_len + 1);
    if (!file.read(nameBuf.data(), hdr.name_len))
      break;
    nameBuf[hdr.name_len] = '\0';
    std::string name(nameBuf.data());

    if (hdr.type == EVENT_CALL) {
      outs() << "    EVENT_CALL\n";
      CallEvent call;
      call.func_id = hdr.func_id;
      call.func_name = name;
      outs() << "        func_name " << name << "\n";
      call.is_external = false;

      uint64_t num_args;
      if (!file.read(reinterpret_cast<char *>(&num_args), sizeof(num_args)))
        break;
      outs() << "        num_args " << num_args << "\n";
      call.args.resize(num_args);
      if (num_args > 0) {
        if (!file.read(reinterpret_cast<char *>(call.args.data()),
                       sizeof(uint64_t) * num_args))
          break;
      }

      callSequence.push_back(call);
    } else if (hdr.type == EVENT_RETURN) {
      outs() << "    EVENT_RETURN\n";
      outs() << "        func_name " << name << "\n";
      uint64_t ret_value;
      if (!file.read(reinterpret_cast<char *>(&ret_value), sizeof(ret_value)))
        break;

      outs() << "        ret_value " << ret_value << "\n";
      // Можно закрыть CALL из стека, если нужно
      if (!callStack.empty()) {
        callStack.pop();
      }
    } else if (hdr.type == EVENT_EXTERNAL_CALL) {
      outs() << "    EVENT_EXTERNAL_CALL\n";
      CallEvent call;
      call.func_id = hdr.func_id;
      call.func_name = name;
      call.is_external = true;
      outs() << "        func_name " << name << "\n";

      uint64_t num_args;
      if (!file.read(reinterpret_cast<char *>(&num_args), sizeof(num_args)))
        break;
      call.args.resize(num_args);
      outs() << "        num_args " << num_args << "\n";
      if (num_args > 0) {
        if (!file.read(reinterpret_cast<char *>(call.args.data()),
                       sizeof(uint64_t) * num_args))
          break;
      }

      if (!file.read(reinterpret_cast<char *>(&call.return_value),
                     sizeof(call.return_value)))
        break;
      outs() << "        return_value " << call.return_value << "\n";

      callSequence.push_back(call);
    } else {
      errs() << "Unknown event type: " << (int)hdr.type << "\n";
      return false;
    }
    outs() << "\n";
  }

  if (file.bad()) {
    errs() << "Error reading trace file\n";
    return false;
  }

  file.close();
  return true;
}

void TraceReader::dumpSequence() const {
  outs() << "; Call sequence:\n";
  for (const auto &ev : callSequence) {
    outs() << "; call " << ev.func_name << " with " << ev.args.size()
           << " args";
    if (ev.is_external)
      outs() << " [external]";
    outs() << "\n";
  }
}
