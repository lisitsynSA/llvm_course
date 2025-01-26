#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace llvm;

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE];

void dumpRegFile() {
  outs() << "[REG FILE]:\n";
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    outs() << "[" << i << "] " << REG_FILE[i] << '\n';
  }
}

void INSTR_sort() { std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE); }

void INSTR_dump(uint32_t reg) {
  outs() << "[" << reg << "] = " << REG_FILE[reg] << '\n';
}

void INSTR_read(uint32_t reg) {
  outs() << "[" << reg << "] = ";
  std::cin >> REG_FILE[reg];
}

int main(int argc, char *argv[]) {
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

  for (int i = 0; i < REG_FILE_SIZE; i++) {
    REG_FILE[i] = 0;
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
  // declare void @INSTR_dump(i32)
  Function *CalleeINSTR_dump = Function::Create(
      FunctionType::get(voidType, ArrayRef<Type *>{int32Type}, false),
      Function::ExternalLinkage, "INSTR_dump", module);
  // declare void @INSTR_addi(i32)
  Function *CalleeINSTR_read = Function::Create(
      FunctionType::get(voidType, ArrayRef<Type *>{int32Type}, false),
      Function::ExternalLinkage, "INSTR_read", module);

  //[32 x i32] regFile = {0, 0, 0, 0}
  ArrayType *regFileType = ArrayType::get(int32Type, REG_FILE_SIZE);
  module->getOrInsertGlobal("regFile", regFileType);
  GlobalVariable *regFile = module->getNamedGlobal("regFile");

  // declare void @main()
  FunctionType *funcType = FunctionType::get(int32Type, false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);

  std::string name;
  std::string arg;
  std::unordered_map<std::string, BasicBlock *> BBMap;

  outs() << "\n[FILE]:\nBBs:";

  while (input >> name) {
    if (!name.compare("add") || !name.compare("addi") || !name.compare("mul") ||
        !name.compare("muli") || !name.compare("bne")) {
      input >> arg >> arg >> arg;
      continue;
    }
    if (!name.compare("b") || !name.compare("dump") || !name.compare("read")) {
      input >> arg;
      continue;
    }
    if (!name.compare("exit") || !name.compare("sort")) {
      continue;
    }

    outs() << " " << name;
    BBMap[name] = BasicBlock::Create(context, name, mainFunc);
  }
  outs() << '\n';
  input.close();
  input.open(argv[1]);

  while (input >> name) {
    if (!name.compare("sort")) {
      outs() << "\tsort\n";
      builder.CreateCall(CalleeINSTR_sort);
      continue;
    }

    if (!name.compare("dump")) {
      input >> arg;
      outs() << "\tdump x" << arg << '\n';
      Value *reg1 = builder.getInt32(std::stoi(arg.substr(1)));
      ArrayRef<Value *> args = {reg1};
      builder.CreateCall(CalleeINSTR_dump, args);
      continue;
    }

    if (!name.compare("read")) {
      input >> arg;
      outs() << "\tread x" << arg << '\n';
      Value *reg1 = builder.getInt32(std::stoi(arg.substr(1)));
      ArrayRef<Value *> args = {reg1};
      builder.CreateCall(CalleeINSTR_read, args);
      continue;
    }
    if (!name.compare("add")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " + " << arg << '\n';
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *add_arg1_arg2 =
          builder.CreateAdd(builder.CreateLoad(int32Type, arg1_p),
                            builder.CreateLoad(int32Type, arg2_p));
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("addi")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " + " << arg << '\n';
      // arg2
      Value *arg2 = builder.getInt32(std::stoi(arg));
      Value *add_arg1_arg2 =
          builder.CreateAdd(builder.CreateLoad(int32Type, arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }

    if (!name.compare("mul")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " * " << arg << '\n';
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *add_arg1_arg2 =
          builder.CreateMul(builder.CreateLoad(int32Type, arg1_p),
                            builder.CreateLoad(int32Type, arg2_p));
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("muli")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " * " << arg << '\n';
      // arg2
      Value *arg2 = builder.getInt32(std::stoi(arg));
      Value *add_arg1_arg2 =
          builder.CreateMul(builder.CreateLoad(int32Type, arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("exit")) {
      outs() << "\texit\n";
      builder.CreateRet(builder.getInt32(0));
      if (input >> name) {
        outs() << "BB " << name << '\n';
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    if (!name.compare("bne")) {
      input >> arg;
      outs() << "\tif (" << arg;
      // reg1
      Value *reg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " != " << arg;
      // reg2
      Value *reg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " ) then BB:" << arg;
      input >> name;
      outs() << " else BB:" << name << '\n';
      outs() << "BB " << name << '\n';

      Value *cond = builder.CreateICmpNE(builder.CreateLoad(int32Type, reg1_p),
                                         builder.CreateLoad(int32Type, reg2_p));
      builder.CreateCondBr(cond, BBMap[arg], BBMap[name]);
      builder.SetInsertPoint(BBMap[name]);
      continue;
    }
    if (!name.compare("b")) {
      // name
      input >> arg;
      outs() << "\tb BB:" << arg << '\n';
      builder.CreateBr(BBMap[arg]);
      if (input >> name) {
        outs() << "BB " << name << '\n';
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    outs() << "BB " << name << '\n';

    if (builder.GetInsertBlock()) {
      builder.CreateBr(BBMap[name]);
    }
    builder.SetInsertPoint(BBMap[name]);
  }

  // Dump LLVM IR
  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  // Interpreter of LLVM IR
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "INSTR_dump") {
      return reinterpret_cast<void *>(INSTR_dump);
    }
    if (fnName == "INSTR_sort") {
      return reinterpret_cast<void *>(INSTR_sort);
    }
    if (fnName == "INSTR_read") {
      return reinterpret_cast<void *>(INSTR_read);
    }
    return nullptr;
  });

  ee->addGlobalMapping(regFile, (void *)REG_FILE);
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(mainFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << '\n';

  dumpRegFile();
  return 0;
}
