#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <string>
using namespace llvm;

void func() { outs() << "Hello from \'external\' function:)\n"; }

int main() {
  LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  // declare void @main()
  FunctionType *funcType = FunctionType::get(builder.getInt32Ty(), false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);

  // entrypoint:
  BasicBlock *entry = BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  // @0 = private unnamed_addr constant [14 x i8] c"hello world!\0A\00", align 1
  Value *helloWorld = builder.CreateGlobalStringPtr("hello world!");

  // declare i32 @puts(i8*)
  Type *int8PtrType = Type::getInt8Ty(context)->getPointerTo();
  ArrayRef<Type *> argsRef(int8PtrType);
  FunctionType *putsType =
      FunctionType::get(builder.getInt32Ty(), argsRef, false);
  FunctionCallee putsFunc = module->getOrInsertFunction("puts", putsType);

  // %0 = call i32 @puts(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0,
  // i32 0, i32 0))
  builder.CreateCall(putsFunc, helloWorld);
  // declare void @func(void)
  Function *ExtFunc =
      Function::Create(FunctionType::get(builder.getVoidTy(), false),
                       Function::ExternalLinkage, "func", module);
  // call void @func()
  builder.CreateCall(ExtFunc);
  // ret i32 0
  builder.CreateRet(builder.getInt32(0));

  // Dump LLVM IR
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "func") {
      return reinterpret_cast<void *>(func);
    }
    return nullptr;
  });
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(mainFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << '\n';

  return 0;
}
