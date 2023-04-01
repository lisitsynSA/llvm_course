#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <iostream>

int main() {
  llvm::LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  llvm::Module *module = new llvm::Module("top", context);
  llvm::IRBuilder<> builder(context);

  // declare void @main()
  llvm::FunctionType *funcType =
      llvm::FunctionType::get(builder.getVoidTy(), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module);
  // entry:
  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(context, "entry", mainFunc);

  builder.SetInsertPoint(entryBB);
  builder.CreateRetVoid();

  std::cout << "#[LLVM IR]:\n";
  std::string s;
  llvm::raw_string_ostream os(s);
  module->print(os, nullptr);
  os.flush();
  std::cout << s;

  return 0;
}
