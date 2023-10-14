#include "../sim.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define FRAME_TICKS 50

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

void simInit() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SIM_X_SIZE, SIM_Y_SIZE, 0, &Window, &Renderer);
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
  SDL_RenderClear(Renderer);
}

void simExit() {
  SDL_Event event;
  while (1) {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;
  }
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void simFlush() {
  SDL_PumpEvents();
  assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
  Uint32 cur_ticks = SDL_GetTicks() - Ticks;
  if (cur_ticks < FRAME_TICKS) {
    SDL_Delay(FRAME_TICKS - cur_ticks);
  }
  SDL_RenderPresent(Renderer);
}

void simPutPixel(int x, int y, int argb) {
  assert(0 <= x && x < SIM_X_SIZE && "Out of range");
  assert(0 <= y && y < SIM_Y_SIZE && "Out of range");
  Uint8 a = argb >> 24;
  Uint8 r = (argb >> 16) & 0xFF;
  Uint8 g = (argb >> 8) & 0xFF;
  Uint8 b = argb & 0xFF;
  SDL_SetRenderDrawColor(Renderer, r, g, b, a);
  SDL_RenderDrawPoint(Renderer, x, y);
  Ticks = SDL_GetTicks();
}

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

  Type *voidType = Type::getVoidTy(context);
  // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
  ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                            Type::getInt32Ty(context),
                                            Type::getInt32Ty(context)};
  FunctionType *simPutPixelType =
      FunctionType::get(voidType, simPutPixelParamTypes, false);
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", simPutPixelType);

  // declare void @simFlush(...)
  FunctionType *simFlushType = FunctionType::get(voidType, {voidType}, false);
  FunctionCallee simFlushFunc =
      module->getOrInsertFunction("simFlush", simFlushType);

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
      Value *arg1 = builder.CreateLoad(
          builder.getInt32Ty(),
          builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                     std::stoi(arg.substr(1))));
      input >> arg;
      outs() << " " << arg;
      Value *arg2 = builder.CreateLoad(
          builder.getInt32Ty(),
          builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                     std::stoi(arg.substr(1))));
      input >> arg;
      outs() << " " << arg << "\n";
      Value *arg3 = builder.CreateLoad(
          builder.getInt32Ty(),
          builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                     std::stoi(arg.substr(1))));
      Value *args[] = {arg1, arg2, arg3};
      builder.CreateCall(simPutPixelFunc, args);
      continue;
    }
    if (!name.compare("FLUSH")) {
      outs() << "\tFLUSH\n";
      builder.CreateCall(simFlushFunc);
      continue;
    }
    if (!name.compare("XOR")) {
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
      outs() << " ^ " << arg << "\n";
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *xor_arg1_arg2 =
          builder.CreateXor(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.CreateLoad(builder.getInt32Ty(), arg2_p));
      builder.CreateStore(xor_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("MUL")) {
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
      Value *mul_arg1_arg2 =
          builder.CreateMul(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.CreateLoad(builder.getInt32Ty(), arg2_p));
      builder.CreateStore(mul_arg1_arg2, res_p);
      continue;
    }
    if (!name.compare("SUBi")) {
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
      outs() << " - " << arg << "\n";
      // arg2
      Value *arg2 = builder.getInt32(std::stoi(arg));
      Value *sub_arg1_arg2 = builder.CreateSub(
          builder.CreateLoad(builder.getInt32Ty(), arg1_p), arg2);
      builder.CreateStore(sub_arg1_arg2, res_p);
      continue;
    }

    if (!name.compare("INC_NEi")) {
      input >> arg;
      outs() << "\t" << arg;
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                std::stoi(arg.substr(1)));
      input >> arg;
      outs() << " = ++" << arg;
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 std::stoi(arg.substr(1)));
      Value *arg1 =
          builder.CreateAdd(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.getInt32(1));
      builder.CreateStore(arg1, arg1_p);
      input >> arg;
      outs() << " != " << arg << "\n";
      // arg2
      Value *arg2 = builder.getInt32(std::stoi(arg));
      Value *cond = builder.CreateICmpNE(arg1, arg2);
      builder.CreateStore(cond, res_p);
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
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
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
