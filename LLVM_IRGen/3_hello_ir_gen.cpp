#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

int main() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  llvm::LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  llvm::Module *module = new llvm::Module("top", context);
  llvm::IRBuilder<> builder(context);

  // declare void @main()
  llvm::FunctionType *funcType =
      llvm::FunctionType::get(builder.getInt32Ty(), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module);

  // entrypoint:
  llvm::BasicBlock *entry =
      llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  // @0 = private unnamed_addr constant [14 x i8] c"hello world!\0A\00", align 1
  llvm::Value *helloWorld = builder.CreateGlobalStringPtr("hello world!\n");

  // declare i32 @puts(i8*)
  std::vector<llvm::Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  llvm::ArrayRef<llvm::Type *> argsRef(putsArgs);
  llvm::FunctionType *putsType =
      llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
  llvm::FunctionCallee putsFunc = module->getOrInsertFunction("puts", putsType);

  // %0 = call i32 @puts(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0,
  // i32 0, i32 0))
  builder.CreateCall(putsFunc, helloWorld);
  // ret i32 0
  builder.CreateRet(llvm::ConstantInt::get(builder.getInt32Ty(), 0));

  // Dump LLVM IR
  std::string s;
  llvm::raw_string_ostream os(s);
  module->print(os, nullptr);
  os.flush();
  std::cout << s;

  // Interpreter of LLVM IR
  std::cout << "Running code...\n";
  llvm::ExecutionEngine *ee =
      llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
  ee->finalizeObject();
  std::vector<llvm::GenericValue> noargs;
  llvm::GenericValue v = ee->runFunction(mainFunc, noargs);
  std::cout << "Code was run.\n";

  return 0;
}
