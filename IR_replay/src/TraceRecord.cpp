#include "../include/TraceRecord.h"
#include "../include/ModuleInfo.h"
#include <fstream>
#include <iostream>

using namespace std;

bool TraceRecord::readArray(ifstream &file) {
  uint64_t numArgs;
  if (!file.read(reinterpret_cast<char *>(&numArgs), sizeof(numArgs)))
    return false;
  if (numArgs > 0) {
    Args.resize(numArgs);
    if (!file.read(reinterpret_cast<char *>(Args.data()),
                   sizeof(uint64_t) * numArgs))
      return false;
  }
  return true;
}

TraceRecord::TraceRecord(TraceHeader &hdr, ifstream &file) : Hdr(hdr) {
  switch (Hdr.type) {
  default:
    cerr << "Unknown event type: " << (int)Hdr.type << '\n';
    break;
  case EVENT_FUNC_START:
    readArray(file);
    break;
  case EVENT_RETURN:
    file.read(reinterpret_cast<char *>(&Ret), sizeof(Ret));
    break;
  case EVENT_EXTERNAL_CALL:
    if (!readArray(file))
      return;
    file.read(reinterpret_cast<char *>(&Ret), sizeof(Ret));
    break;
  case EVENT_MEMOP:
    if (!file.read(reinterpret_cast<char *>(&Mem), sizeof(Mem)))
      return;
    if (Mem.type == MEM_GEP)
      readArray(file);
    break;
  }
}

void TraceRecord::printArgs(string name) {
  for (int i = 0; i < Args.size(); i++) {
    cout << "    " << name << i + 1 << ": " << Args[i] << '\n';
  }
}

string TraceRecord::printFuncName(ModuleInfo *M) {
  return M ? M->Id2FuncName[Hdr.op_id] : to_string(Hdr.op_id);
}

void TraceRecord::printFuncEvent(ModuleInfo *M) {
  cout << "[FUNC " << printFuncName(M) << "] " << Args.size() << " args\n";
  printArgs("arg");
}
void TraceRecord::printRetEvent(ModuleInfo *M) {
  cout << "[RET " << printFuncName(M) << "] ret " << Ret << '\n';
}
void TraceRecord::printCallEvent(ModuleInfo *M) {
  cout << "[EXTCALL " << printFuncName(M) << "] " << Args.size() << " args\n";
  printArgs("arg");
  cout << "    ret: " << Ret << '\n';
}
void TraceRecord::printMemEvent(ModuleInfo *M) {
  cout << "[MEM " << printFuncName(M) << "] " << Mem.type << " " << Mem.size
       << "bit [0x" << hex << Mem.address << "]: ";
  if (Mem.type == MEM_GEP) {
    cout << '\n';
    printArgs("ptr");
    cout << dec;
  } else {
    cout << dec << Mem.value << '\n';
  }
}

void TraceRecord::dump(ModuleInfo *M) {
  switch (Hdr.type) {
  default:
    cerr << "Unknown event type: " << Hdr.type << '\n';
    break;
  case EVENT_FUNC_START:
    printFuncEvent(M);
    break;
  case EVENT_RETURN:
    printRetEvent(M);
    break;
  case EVENT_EXTERNAL_CALL:
    printCallEvent(M);
    break;
  case EVENT_MEMOP:
    printMemEvent(M);
    break;
  }
}