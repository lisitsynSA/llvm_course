%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;

#define YYSTYPE Value*
extern "C" {
    int yyparse();
    int yylex();
    void yyerror(char *s) {
        std::cerr << s << '\n';
    }
    int yywrap(void){return 1;}
}
IRBuilder<>* builder;

int main(int argc, char **argv)
{
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

    yyparse();

    outs() << "[LLVM IR]:\n";
    module->print(outs(), nullptr);
    outs() << '\n';
    bool verif = verifyFunction(*mainFunc, &outs());
    outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

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

TERM:    NUM
        | TERM '*' NUM  { $$ = builder->CreateMul($1, $3); }
        | TERM '/' NUM  { $$ = builder->CreateUDiv($1, $3); }
;

%%
