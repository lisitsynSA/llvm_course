#include "include/fullIR.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>

using namespace llvm;

void FullIR::buildIR(Binary &Bin) {
  module = new Module("top", context);
  IRBuilder<> builder(context);
  voidType = Type::getVoidTy(context);
  int32Type = Type::getInt32Ty(context);
  Type *boolType = Type::getInt1Ty(context);

  // declare void @app()
  FunctionType *funcType = FunctionType::get(voidType, false);
  mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "app", module);
  // Functions types
  FunctionType *voidFuncType = FunctionType::get(voidType, false);
  ArrayRef<Type *> int32x3Types = {int32Type, int32Type, int32Type};
  FunctionType *int32x3FuncType =
      FunctionType::get(voidType, int32x3Types, false);

  // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", int32x3FuncType);

  // declare void @simFlush()
  FunctionType *simFlushType = FunctionType::get(voidType, false);
  FunctionCallee simFlushFunc =
      module->getOrInsertFunction("simFlush", simFlushType);

  // declare i32 @simRand()
  FunctionType *simRandType = FunctionType::get(int32Type, false);
  FunctionCallee simRandFunc =
      module->getOrInsertFunction("simRand", simRandType);
  // declare i32 @llvm.abs.i32(i32, i1 immarg) #4
  FunctionType *AbsType =
      FunctionType::get(int32Type, {int32Type, boolType}, false);
  FunctionCallee AbsFunc = module->getOrInsertFunction("llvm.abs.i32", AbsType);

  std::unordered_map<uint32_t, BasicBlock *> BBMap;
  for (auto &BB : Bin.BBName2PC) {
    BBMap[BB.second] = BasicBlock::Create(context, BB.first, mainFunc);
  }

  uint32_t PC = 0;
  builder.SetInsertPoint(BBMap[0]);
  // %0 = alloca i32, i32 16, align 4
  ArrayType *regFileType = ArrayType::get(int32Type, CPU::RegSize);
  Value *regFile = builder.CreateAlloca(regFileType);

  for (Instr &I : Bin.Instrs) {
    switch (I.Op) {
    default:
      break;
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  case (_Opcode):                                                              \
    _IRGenExecute;                                                             \
    break;
#include "include/ISA.h"
#undef _ISA
    }
    PC++;
    auto BB = BBMap.find(PC);
    if (BB != BBMap.end()) {
      builder.CreateBr(BB->second);
      builder.SetInsertPoint(BB->second);
    }
  }
}

void FullIR::executeIR(CPU &Cpu) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "simRand") {
      return reinterpret_cast<void *>(simRand);
    }
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    return nullptr;
  });
  ee->finalizeObject();

  simInit();
  CPU::setCPU(&Cpu);
  Cpu.DumpInstrs = true;

  ArrayRef<GenericValue> noargs;
  outs() << "\n#[Running code]\n";
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  simExit();
}

bool FullIR::printIR(std::string FileName, std::string &ErrorMsg) {
  // Prepare Graphic intrinsic usage
  IRBuilder<> builder(context);
  // declare void @llvm.sim.putpixel(i32 noundef, i32 noundef, i32 noundef)
  ArrayRef<Type *> simPutPixelParamTypes = {int32Type, int32Type, int32Type};
  FunctionType *simPutPixelType =
      FunctionType::get(voidType, simPutPixelParamTypes, false);
  FunctionCallee simPutPixelIntr =
      module->getOrInsertFunction("llvm.sim.putpixel", simPutPixelType);
  // define void @simPutPixel(i32 %0, i32 %1, i32 %2) {
  Function *simPutPixelFunc = module->getFunction("simPutPixel");
  // entry:
  builder.SetInsertPoint(BasicBlock::Create(context, "entry", simPutPixelFunc));
  // call void @llvm.sim.putpixel(i32 %0, i32 %1, i32 %2)
  builder.CreateCall(simPutPixelIntr,
                     {simPutPixelFunc->getArg(0), simPutPixelFunc->getArg(1),
                      simPutPixelFunc->getArg(2)});
  // ret
  builder.CreateRetVoid();

  // declare void @llvm.sim.flush()
  FunctionType *simFlushType = FunctionType::get(voidType, false);
  FunctionCallee simFlushIntr =
      module->getOrInsertFunction("llvm.sim.flush", simFlushType);
  // define void @simFlush() {
  Function *simFlushFunc = module->getFunction("simFlush");
  // entry:
  builder.SetInsertPoint(BasicBlock::Create(context, "entry", simFlushFunc));
  // call void @llvm.sim.flush()
  builder.CreateCall(simFlushIntr);
  // ret
  builder.CreateRetVoid();

  // declare void @llvm.sim.rand()
  FunctionType *simRandType = FunctionType::get(int32Type, false);
  FunctionCallee simRandIntr =
      module->getOrInsertFunction("llvm.sim.rand", simRandType);
  // define void @simRand() {
  Function *simRandFunc = module->getFunction("simRand");
  // entry:
  builder.SetInsertPoint(BasicBlock::Create(context, "entry", simRandFunc));
  // ret call i32 @llvm.sim.rand()
  builder.CreateRet(builder.CreateCall(simRandIntr));

  // Dump LLVM IR with intrinsics
  std::error_code EC;
  raw_fd_ostream OutputFile(FileName, EC);
  if (!EC) {
    module->print(OutputFile, nullptr);
    return false;
  } else {
    ErrorMsg = "Can't print LLVM IR to " + FileName;
    return true;
  }
}
