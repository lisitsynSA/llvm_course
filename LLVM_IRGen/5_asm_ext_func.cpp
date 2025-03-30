#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
using namespace llvm;

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE] = {};

void dumpRegFile() {
  outs() << "[REG FILE]:\n";
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    outs() << "[" << i << "] " << REG_FILE[i] << '\n';
  }
}

void INSTR_sort() {
  outs() << "SORT is called\n";
  std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE);
}

void INSTR_add(uint32_t reg1, uint32_t reg2, uint32_t reg3) {
  outs() << "ADD  is called\n";
  REG_FILE[reg1] = REG_FILE[reg2] + REG_FILE[reg3];
}

void INSTR_addi(uint32_t reg1, uint32_t reg2, uint32_t imm3) {
  outs() << "ADDi is called\n";
  REG_FILE[reg1] = REG_FILE[reg2] + imm3;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    outs() << "[ERROR] Need 1 argument: file with assembler\n";
    return 1;
  }
  std::ifstream input;
  input.open(argv[1]);
  if (!input.is_open()) {
    outs() << "[ERROR] Can't open " << argv[1] << '\n';
    return 1;
  }

  LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);
  Type *voidType = builder.getVoidTy();
  Type *int32Type = builder.getInt32Ty();

  // declare void @INSTR_sort(void)
  Function *CalleeINSTR_sort =
      Function::Create(FunctionType::get(voidType, false),
                       Function::ExternalLinkage, "INSTR_sort", module);
  // declare void @INSTR_add(i32, i32, i32)
  Function *CalleeINSTR_add = Function::Create(
      FunctionType::get(
          voidType, ArrayRef<Type *>{int32Type, int32Type, int32Type}, false),
      Function::ExternalLinkage, "INSTR_add", module);
  // declare void @INSTR_addi(i32, i32, i32)
  Function *CalleeINSTR_addi = Function::Create(
      FunctionType::get(
          voidType, ArrayRef<Type *>{int32Type, int32Type, int32Type}, false),
      Function::ExternalLinkage, "INSTR_addi", module);

  // declare void @main()
  FunctionType *funcType = FunctionType::get(int32Type, false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);

  // entrypoint:
  BasicBlock *entry = BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  std::string name;
  std::string arg;
  while (input >> name) {
    if (!name.compare("sort")) {
      outs() << "sort \n";
      builder.CreateCall(CalleeINSTR_sort);
      continue;
    }
    if (!name.compare("add")) {
      // reg1
      input >> arg;
      outs() << arg;
      Value *reg1 = builder.getInt32(std::stoi(arg.substr(1)));
      // reg2
      input >> arg;
      outs() << " = " << arg;
      Value *reg2 = builder.getInt32(std::stoi(arg.substr(1)));
      // reg3
      input >> arg;
      outs() << " + " << arg << '\n';
      Value *reg3 = builder.getInt32(std::stoi(arg.substr(1)));

      ArrayRef<Value *> args = {reg1, reg2, reg3};
      builder.CreateCall(CalleeINSTR_add, args);
      continue;
    }
    if (!name.compare("addi")) {
      // reg1
      input >> arg;
      outs() << arg;
      Value *reg1 = builder.getInt32(std::stoi(arg.substr(1)));
      // reg2
      input >> arg;
      outs() << " = " << arg;
      Value *reg2 = builder.getInt32(std::stoi(arg.substr(1)));
      // imm3
      input >> arg;
      outs() << " + " << arg << '\n';
      Value *imm3 = builder.getInt32(std::stoi(arg));

      ArrayRef<Value *> args = {reg1, reg2, imm3};
      builder.CreateCall(CalleeINSTR_addi, args);
      continue;
    }
  }
  input.close();

  // ret i32 0
  builder.CreateRet(builder.getInt32(0));

  // Dump LLVM IR
  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  dumpRegFile();

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "INSTR_sort") {
      return reinterpret_cast<void *>(INSTR_sort);
    }
    if (fnName == "INSTR_add") {
      return reinterpret_cast<void *>(INSTR_add);
    }
    if (fnName == "INSTR_addi") {
      return reinterpret_cast<void *>(INSTR_addi);
    }
    return nullptr;
  });
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(mainFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << '\n';

  dumpRegFile();
  return 0;
}
