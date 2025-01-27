#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
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
  printf("SORT is called\n");
  std::sort(REG_FILE, REG_FILE + REG_FILE_SIZE);
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

  //[8 x i32] regFile = {0, 0, 0, 0}
  ArrayType *regFileType = ArrayType::get(int32Type, REG_FILE_SIZE);
  module->getOrInsertGlobal("regFile", regFileType);
  GlobalVariable *regFile = module->getNamedGlobal("regFile");

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
      input >> arg;
      outs() << arg;
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
      outs() << arg;
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
  }
  input.close();

  // ret i32 0
  builder.CreateRet(builder.getInt32(0));

  // Dump LLVM IR
  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

  dumpRegFile();

  // Interpreter of LLVM IR
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->addGlobalMapping(regFile, (void *)REG_FILE);
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "INSTR_sort") {
      return reinterpret_cast<void *>(INSTR_sort);
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
