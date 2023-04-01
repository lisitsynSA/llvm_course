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

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE];

void INSTR_sort() { std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE); }

void INSTR_dump(uint32_t reg) {
  std::cout << "[" << reg << "] = " << REG_FILE[reg] << "\n";
}

void INSTR_read(uint32_t reg) {
  std::cout << "[" << reg << "] = ";
  std::cin >> REG_FILE[reg];
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "[ERROR] Need 1 argument: file with RISC-V assembler\n";
    return 1;
  }
  std::ifstream input;
  input.open(argv[1]);
  if (!input.is_open()) {
    std::cout << "[ERROR] Can't open " << argv[1] << "\n";
    return 1;
  }

  for (int i = 0; i < REG_FILE_SIZE; i++) {
    REG_FILE[i] = 0;
  }

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  llvm::LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  llvm::Module *module = new llvm::Module("top", context);
  llvm::IRBuilder<> builder(context);

  //[32 x i32] regFile = {0, 0, 0, 0}
  llvm::ArrayType *regFileType =
      llvm::ArrayType::get(builder.getInt32Ty(), REG_FILE_SIZE);
  module->getOrInsertGlobal("regFile", regFileType);
  llvm::GlobalVariable *regFile = module->getNamedGlobal("regFile");

  // declare void @main()
  llvm::FunctionType *funcType =
      llvm::FunctionType::get(builder.getVoidTy(), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module);

  std::string name;
  std::string arg;
  std::unordered_map<std::string, llvm::BasicBlock *> BBMap;

  std::cout << "\n#[FILE]:\nBBs:";

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

    std::cout << " " << name;
    BBMap[name] = llvm::BasicBlock::Create(context, name, mainFunc);
  }
  std::cout << "\n";
  input.close();
  input.open(argv[1]);

  while (input >> name) {

    if (!name.compare("dump")) {
      input >> arg;
      std::cout << "\tdump x" << arg << "\n";
      llvm::Function *CalleeF = llvm::Function::Create(
          llvm::FunctionType::get(
              builder.getVoidTy(),
              llvm::ArrayRef<llvm::Type *>(builder.getInt32Ty()), false),
          llvm::Function::ExternalLinkage, "INSTR_dump", module);
      builder.CreateCall(CalleeF,
                         llvm::ArrayRef<llvm::Value *>(llvm::ConstantInt::get(
                             builder.getInt32Ty(), std::stoi(arg.substr(1)))));
      continue;
    }

    if (!name.compare("read")) {
      input >> arg;
      std::cout << "\tread x" << arg << "\n";
      llvm::Function *CalleeF = llvm::Function::Create(
          llvm::FunctionType::get(
              builder.getVoidTy(),
              llvm::ArrayRef<llvm::Type *>(builder.getInt32Ty()), false),
          llvm::Function::ExternalLinkage, "INSTR_read", module);
      builder.CreateCall(CalleeF,
                         llvm::ArrayRef<llvm::Value *>(llvm::ConstantInt::get(
                             builder.getInt32Ty(), std::stoi(arg.substr(1)))));
      continue;
    }
    if (!name.compare("sort")) {
      std::cout << "\tsort\n";
      llvm::Function *CalleeF = llvm::Function::Create(
          llvm::FunctionType::get(builder.getVoidTy(), false),
          llvm::Function::ExternalLinkage, "INSTR_sort", module);
      builder.CreateCall(CalleeF);
      continue;
    }
    if (!name.compare("add")) {
      input >> arg;
      std::cout << "\t" << arg;
      // res
      llvm::Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " = " << arg;
      // arg1
      llvm::Value *arg1_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " + " << arg << "\n";
      // arg2
      llvm::Value *arg2_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      llvm::Value *add_arg1_arg2 = builder.CreateAdd(
          builder.CreateLoad(arg1_p), builder.CreateLoad(arg2_p));
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("addi")) {
      input >> arg;
      std::cout << "\t" << arg;
      // res
      llvm::Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " = " << arg;
      // arg1
      llvm::Value *arg1_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " + " << arg << "\n";
      // arg2
      llvm::Value *arg2 =
          llvm::ConstantInt::get(builder.getInt32Ty(), std::stoi(arg));
      llvm::Value *add_arg1_arg2 =
          builder.CreateAdd(builder.CreateLoad(arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }

    if (!name.compare("mul")) {
      input >> arg;
      std::cout << "\t" << arg;
      // res
      llvm::Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " = " << arg;
      // arg1
      llvm::Value *arg1_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " * " << arg << "\n";
      // arg2
      llvm::Value *arg2_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      llvm::Value *add_arg1_arg2 = builder.CreateMul(
          builder.CreateLoad(arg1_p), builder.CreateLoad(arg2_p));
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("muli")) {
      input >> arg;
      std::cout << "\t" << arg;
      // res
      llvm::Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " = " << arg;
      // arg1
      llvm::Value *arg1_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " * " << arg << "\n";
      // arg2
      llvm::Value *arg2 =
          llvm::ConstantInt::get(builder.getInt32Ty(), std::stoi(arg));
      llvm::Value *add_arg1_arg2 =
          builder.CreateMul(builder.CreateLoad(arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("exit")) {
      std::cout << "\texit" << std::endl;
      builder.CreateRetVoid();
      if (input >> name) {
        std::cout << "BB " << name << "\n";
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    if (!name.compare("bne")) {
      input >> arg;
      std::cout << "\tif (" << arg;
      // reg1
      llvm::Value *reg1_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " != " << arg;
      // reg2
      llvm::Value *reg2_p = builder.CreateConstGEP2_32(
          regFileType, regFile, 0, std::stoi(arg.substr(1)));
      input >> arg;
      std::cout << " ) then BB:" << arg;
      input >> name;
      std::cout << " else BB:" << name << std::endl;
      std::cout << "BB " << name << "\n";

      llvm::Value *cond = builder.CreateICmpNE(builder.CreateLoad(reg1_p),
                                               builder.CreateLoad(reg2_p));
      builder.CreateCondBr(cond, BBMap[arg], BBMap[name]);
      builder.SetInsertPoint(BBMap[name]);
      continue;
    }
    if (!name.compare("b")) {
      // name
      input >> arg;
      std::cout << "\tb BB:" << arg << std::endl;
      builder.CreateBr(BBMap[arg]);
      if (input >> name) {
        std::cout << "BB " << name << "\n";
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    std::cout << "BB " << name << "\n";

    builder.CreateBr(BBMap[name]);
    builder.SetInsertPoint(BBMap[name]);
  }

  std::cout << "\n#[LLVM IR]:\n";
  std::string s;
  llvm::raw_string_ostream os(s);
  module->print(os, nullptr);
  os.flush();
  std::cout << s;

  llvm::verifyFunction(*mainFunc);
  std::cout << "\n#[Running code]\n";
  llvm::ExecutionEngine *ee =
      llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
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
  std::vector<llvm::GenericValue> noargs;
  ee->runFunction(mainFunc, noargs);
  std::cout << "#[Code was run]\n";

  for (int i = 0; i < REG_FILE_SIZE; i++) {
    std::cout << "[" << i << "] " << REG_FILE[i] << "\n";
  }

  return 0;
}
