%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"
using namespace llvm;

#define YYSTYPE Value*
extern "C" {
    int yyparse();
    int yylex();
    void yyerror(char *s) {
        std::cerr << s << "\n";
    }
    int yywrap(void){return 1;}
}
IRBuilder<>* builder;

Function *readFunc;
int readVal() {
    std::cout << "Enter a number: ";
    int res = 0;
    std::cin >> res;
    return res;
}

int main(int argc, char **argv)
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    Module* module = new Module("top", context);
    builder = new IRBuilder<> (context);

    // declare void @main()
    FunctionType *funcType =
        FunctionType::get(builder->getInt32Ty(), false);
    Function *mainFunc =
        Function::Create(funcType, Function::ExternalLinkage, "main", module);
    // entry:
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", mainFunc);

    builder->SetInsertPoint(entryBB);

    readFunc = Function::Create(funcType, Function::ExternalLinkage, "readVal", module);

    yyparse();

    outs() << "[LLVM IR]:\n";
    module->print(outs(), nullptr);
    outs() << "\n";
    bool verif = verifyFunction(*mainFunc, &outs());
    outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

    // Interpreter of LLVM IR
    outs() << "[EE] Run\n";
	ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
        if (fnName == "readVal") { return reinterpret_cast<void *>(readVal); }
        return nullptr;
    });
    ee->finalizeObject();
	std::vector<GenericValue> noargs;
	GenericValue res = ee->runFunction(mainFunc, noargs);
    outs() << "[EE] Result: " << res.IntVal << "\n";

    return 0;
}
%}

%token NUM

%%

EVALUATE: EXPR ';' { builder->CreateRet($$); YYACCEPT; };

EXPR:    TERM
        | EXPR '+' TERM { $$ = builder->CreateAdd($1, $3); }
        | EXPR '-' TERM { $$ = builder->CreateSub($1, $3); }
;

TERM:    VAL
        | TERM '*' VAL  { $$ = builder->CreateMul($1, $3); }
        | TERM '/' VAL  { $$ = builder->CreateUDiv($1, $3); }
;

VAL:    NUM
        | '?' { $$ = builder->CreateCall(readFunc); }

%%
