#include "../sim.h"

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

//    XOR x1 x1 x1
//    MUL x3 x2 x1
//    SUBi x6 x6 16777216
//    PUT_PIXEL x5 x2 x6
//    INC_NEi x4 x5 512
//    BR_COND x4 label_13
//    FLUSH
//    EXIT

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE];

void do_XOR(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] ^ REG_FILE[arg3];
}

void do_MUL(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] * REG_FILE[arg3];
}

void do_SUBi(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] - arg3;
}

void do_PUT_PIXEL(int arg1, int arg2, int arg3) {
  simPutPixel(REG_FILE[arg1], REG_FILE[arg2], REG_FILE[arg3]);
}

void do_INC_NEi(int arg1, int arg2, int arg3) {
  REG_FILE[arg2]++;
  REG_FILE[arg1] = REG_FILE[arg2] != arg3;
}

void do_FLUSH(){
  simFlush();
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
    if (!name.compare("XOR") || !name.compare("MUL") || !name.compare("SUBi") ||
        !name.compare("PUT_PIXEL") || !name.compare("INC_NEi")) {
      input >> arg >> arg >> arg;
      continue;
    }
    if (!name.compare("BR_COND")) {
      input >> arg >> arg;
      continue;
    }
    if (!name.compare("EXIT") || !name.compare("FLUSH")) {
      continue;
    }

    outs() << " " << name;
    BBMap[name] = BasicBlock::Create(context, name, mainFunc);
  }
  outs() << "\n";
  input.close();
  input.open(argv[1]);

  // Funcions types
  Type *voidType = Type::getVoidTy(context);
  FunctionType *voidFuncType = FunctionType::get(voidType, {voidType}, false);
  ArrayRef<Type *> int32x3Types = {Type::getInt32Ty(context),
                                   Type::getInt32Ty(context),
                                   Type::getInt32Ty(context)};
  FunctionType *int32x3FuncType =
      FunctionType::get(voidType, int32x3Types, false);
  // Functions
  FunctionCallee do_XORFunc =
      module->getOrInsertFunction("do_XOR", int32x3FuncType);

  FunctionCallee do_MULFunc =
      module->getOrInsertFunction("do_MUL", int32x3FuncType);

  FunctionCallee do_SUBiFunc =
      module->getOrInsertFunction("do_SUBi", int32x3FuncType);

  FunctionCallee do_PUT_PIXELFunc =
      module->getOrInsertFunction("do_PUT_PIXEL", int32x3FuncType);

  FunctionCallee do_INC_NEiFunc =
      module->getOrInsertFunction("do_INC_NEi", int32x3FuncType);

  FunctionCallee do_FLUSHFunc =
      module->getOrInsertFunction("do_FLUSH", voidFuncType);

  while (input >> name) {
    if (!name.compare("EXIT")) {
      outs() << "\tEXIT\n";
      builder.CreateRetVoid();
      if (input >> name) {
        outs() << "BB " << name << "\n";
        builder.SetInsertPoint(BBMap[name]);
      }
      continue;
    }
    if (!name.compare("PUT_PIXEL")) {
      input >> arg;
      outs() << "\tPUT_PIXEL " << arg;
      Value *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " " << arg;
      Value *arg2 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " " << arg << "\n";
      Value *arg3 = builder.getInt32(std::stoi(arg.substr(1)));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(do_PUT_PIXELFunc, args);
      continue;
    }
    if (!name.compare("FLUSH")) {
      outs() << "\tFLUSH\n";
      builder.CreateCall(do_FLUSHFunc);
      continue;
    }
    if (!name.compare("XOR")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg2 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " ^ " << arg << "\n";
      // arg2
      Value *arg3 = builder.getInt32(std::stoi(arg.substr(1)));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(do_XORFunc, args);
      continue;
    }
    if (!name.compare("MUL")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg2 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " * " << arg << "\n";
      // arg2
      Value *arg3 = builder.getInt32(std::stoi(arg.substr(1)));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(do_MULFunc, args);
      continue;
    }
    if (!name.compare("SUBi")) {

      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = " << arg;
      // arg1
      Value *arg2 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " - " << arg << "\n";
      // arg2
      Value *arg3 = builder.getInt32(std::stoi(arg));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(do_SUBiFunc, args);
      continue;
    }

    if (!name.compare("INC_NEi")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = ++" << arg;
      // arg1
      Value *arg2 = builder.getInt32(std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " != " << arg << "\n";
      // arg2
      Value *arg3 = builder.getInt32(std::stoi(arg));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(do_INC_NEiFunc, args);
      continue;
    }
    if (!name.compare("BR_COND")) {
      input >> arg;
      outs() << "\tif (" << arg;
      // reg1
      Value *reg_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << ") then BB:" << arg;
      input >> name;
      outs() << " else BB:" << name << "\n";
      outs() << "BB " << name << "\n";
      builder.CreateCondBr(builder.CreateLoad(builder.getInt32Ty(), reg_p),
                           BBMap[arg], BBMap[name]);
      builder.SetInsertPoint(BBMap[name]);
      continue;
    }

    if (builder.GetInsertBlock()) {
      builder.CreateBr(BBMap[name]);
      outs() << "\tbranch to " << name << "\n";
    }
    outs() << "BB " << name << "\n";
    builder.SetInsertPoint(BBMap[name]);
  }

  outs() << "\n#[LLVM IR]:\n";
  module->print(outs(), nullptr);

  outs() << "\n#[Running code]\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == "do_XOR") {
      return reinterpret_cast<void *>(do_XOR);
    }
    if (fnName == "do_MUL") {
      return reinterpret_cast<void *>(do_MUL);
    }
    if (fnName == "do_SUBi") {
      return reinterpret_cast<void *>(do_SUBi);
    }
    if (fnName == "do_PUT_PIXEL") {
      return reinterpret_cast<void *>(do_PUT_PIXEL);
    }
    if (fnName == "do_INC_NEi") {
      return reinterpret_cast<void *>(do_INC_NEi);
    }
    if (fnName == "do_FLUSH") {
      return reinterpret_cast<void *>(do_FLUSH);
    }
    return nullptr;
  });

  ee->addGlobalMapping(regFile, (void *)REG_FILE);
  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> noargs;
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  simExit();
  return EXIT_SUCCESS;
}
