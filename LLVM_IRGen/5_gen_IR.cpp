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

void INSTR_sort() { std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE); }

void INSTR_dump(uint32_t reg) {
  outs() << "[" << reg << "] = " << REG_FILE[reg] << "\n";
}

void INSTR_read(uint32_t reg) {
  outs() << "[" << reg << "] = ";
  std::cin >> REG_FILE[reg];
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    outs() << "[ERROR] Need 1 argument: file with RISC-V assembler\n";
    return 1;
  }
  std::ifstream input;
  input.open(argv[1]);
  if (!input.is_open()) {
    outs() << "[ERROR] Can't open " << argv[1] << "\n";
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

  //[32 x i32] regFile = {0, 0, 0, 0}
  ArrayType *regFileType = ArrayType::get(builder.getInt32Ty(), REG_FILE_SIZE);
  module->getOrInsertGlobal("regFile", regFileType);
  GlobalVariable *regFile = module->getNamedGlobal("regFile");

  // declare void @main()
  FunctionType *funcType = FunctionType::get(builder.getVoidTy(), false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);

  std::string name;
  std::string arg;
  std::unordered_map<std::string, BasicBlock *> BBMap;

  outs() << "\n#[FILE]:\nBBs:";

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
  outs() << "\n";
  input.close();
  input.open(argv[1]);

  while (input >> name) {

    if (!name.compare("dump")) {
      input >> arg;
      outs() << "\tdump x" << arg << "\n";
      Function *CalleeF = Function::Create(
          FunctionType::get(builder.getVoidTy(),
                            ArrayRef<Type *>(builder.getInt32Ty()), false),
          Function::ExternalLinkage, "INSTR_dump", module);
      builder.CreateCall(CalleeF,
                         ArrayRef<Value *>(ConstantInt::get(
                             builder.getInt32Ty(), std::stoi(arg.substr(1)))));
      continue;
    }

    if (!name.compare("read")) {
      input >> arg;
      outs() << "\tread x" << arg << "\n";
      Function *CalleeF = Function::Create(
          FunctionType::get(builder.getVoidTy(),
                            ArrayRef<Type *>(builder.getInt32Ty()), false),
          Function::ExternalLinkage, "INSTR_read", module);
      builder.CreateCall(CalleeF,
                         ArrayRef<Value *>(ConstantInt::get(
                             builder.getInt32Ty(), std::stoi(arg.substr(1)))));
      continue;
    }
    if (!name.compare("sort")) {
      outs() << "\tsort\n";
      Function *CalleeF =
          Function::Create(FunctionType::get(builder.getVoidTy(), false),
                           Function::ExternalLinkage, "INSTR_sort", module);
      builder.CreateCall(CalleeF);
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
      outs() << " + " << arg << "\n";
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *add_arg1_arg2 =
          builder.CreateAdd(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.CreateLoad(builder.getInt32Ty(), arg2_p));
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
      outs() << " + " << arg << "\n";
      // arg2
      Value *arg2 = ConstantInt::get(builder.getInt32Ty(), std::stoi(arg));
      Value *add_arg1_arg2 = builder.CreateAdd(
          builder.CreateLoad(builder.getInt32Ty(), arg1_p), arg2);
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
      outs() << " * " << arg << "\n";
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *add_arg1_arg2 =
          builder.CreateMul(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.CreateLoad(builder.getInt32Ty(), arg2_p));
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
      outs() << " * " << arg << "\n";
      // arg2
      Value *arg2 = ConstantInt::get(builder.getInt32Ty(), std::stoi(arg));
      Value *add_arg1_arg2 = builder.CreateMul(
          builder.CreateLoad(builder.getInt32Ty(), arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("exit")) {
      outs() << "\texit\n";
      builder.CreateRetVoid();
      if (input >> name) {
        outs() << "BB " << name << "\n";
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
      outs() << " else BB:" << name << "\n";
      outs() << "BB " << name << "\n";

      Value *cond = builder.CreateICmpNE(
          builder.CreateLoad(builder.getInt32Ty(), reg1_p),
          builder.CreateLoad(builder.getInt32Ty(), reg2_p));
      builder.CreateCondBr(cond, BBMap[arg], BBMap[name]);
      builder.SetInsertPoint(BBMap[name]);
      continue;
    }
    if (!name.compare("b")) {
      // name
      input >> arg;
      outs() << "\tb BB:" << arg << "\n";
      builder.CreateBr(BBMap[arg]);
      if (input >> name) {
        outs() << "BB " << name << "\n";
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    outs() << "BB " << name << "\n";

    builder.CreateBr(BBMap[name]);
    builder.SetInsertPoint(BBMap[name]);
  }

  outs() << "\n#[LLVM IR]:\n";
  module->print(outs(), nullptr);

  verifyFunction(*mainFunc);
  outs() << "\n#[Running code]\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
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
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  for (int i = 0; i < REG_FILE_SIZE; i++) {
    outs() << "[" << i << "] " << REG_FILE[i] << "\n";
  }

  return 0;
}
