#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <iostream>

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE] = {};

void INSTR_sort() { std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE); }

int main(int argc, char **argv) {
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
      llvm::FunctionType::get(builder.getInt32Ty(), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module);

  // entrypoint:
  llvm::BasicBlock *entry =
      llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  std::string name;
  std::string arg;
  while (input >> name) {
    if (!name.compare("add")) {
      input >> arg;
      std::cout << arg;
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
      std::cout << arg;
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
    if (!name.compare("sort")) {
      std::cout << "sort "
                << "\n";
      // arg1
      llvm::Function *CalleeF = llvm::Function::Create(
          llvm::FunctionType::get(
              builder.getVoidTy(),
              llvm::ArrayRef<llvm::Type *>(builder.getVoidTy()), false),
          llvm::Function::ExternalLinkage, "INSTR_sort", module);
      builder.CreateCall(CalleeF);
      continue;
    }
  }
  input.close();

  // ret i32 0
  builder.CreateRet(llvm::ConstantInt::get(builder.getInt32Ty(), 0));

  // Dump LLVM IR
  std::string s;
  llvm::raw_string_ostream os(s);
  module->print(os, nullptr);
  os.flush();
  std::cout << s;

  std::cout << "# [REG FILE]:\n";
  int i = 0;
  for (auto &reg : REG_FILE) {
    std::cout << "[" << i++ << "] " << reg << "\n";
  }

  // Interpreter of LLVM IR
  std::cout << "Running code...\n";
  llvm::ExecutionEngine *ee =
      llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
  ee->addGlobalMapping(regFile, (void *)REG_FILE);
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == "INSTR_sort") {
      return reinterpret_cast<void *>(INSTR_sort);
    }
    return nullptr;
  });
  ee->finalizeObject();
  std::vector<llvm::GenericValue> noargs;
  llvm::GenericValue v = ee->runFunction(mainFunc, noargs);
  std::cout << "Code was run.\n";

  i = 0;
  std::cout << "# [REG FILE]:\n";
  for (auto &reg : REG_FILE) {
    std::cout << "[" << i++ << "] " << reg << "\n";
  }

  return 0;
}
