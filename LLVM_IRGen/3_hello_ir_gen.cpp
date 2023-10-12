#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main() {
  LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  // declare void @main()
  FunctionType *funcType =
      FunctionType::get(builder.getInt32Ty(), false);
  Function *mainFunc = Function::Create(
      funcType, Function::ExternalLinkage, "main", module);

  // entrypoint:
  BasicBlock *entry =
      BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  // @0 = private unnamed_addr constant [14 x i8] c"hello world!\0A\00", align 1
  Value *helloWorld = builder.CreateGlobalStringPtr("hello world!\n");

  // declare i32 @puts(i8*)
  std::vector<Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  ArrayRef<Type *> argsRef(putsArgs);
  FunctionType *putsType =
      FunctionType::get(builder.getInt32Ty(), argsRef, false);
  FunctionCallee putsFunc = module->getOrInsertFunction("puts", putsType);

  // %0 = call i32 @puts(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0,
  // i32 0, i32 0))
  builder.CreateCall(putsFunc, helloWorld);
  // ret i32 0
  builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0));

  // Dump LLVM IR
  module->print(outs(), nullptr);

  // Interpreter of LLVM IR
  outs() << "Running code...\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee =
      EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(mainFunc, noargs);
  outs() << "Code was run.\n";

  return 0;
}
