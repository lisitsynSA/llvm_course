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
Module* module;

std::map<std::string, GlobalVariable*> IdentifierMap;

int main(int argc, char **argv)
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    module = new Module("top", context);
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
    outs() << "\n";
    bool verif = verifyFunction(*mainFunc, &outs());
    outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

    // Interpreter of LLVM IR
    outs() << "[EE] Run\n";
	ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    for (auto& value : IdentifierMap) {
        ee->addGlobalMapping(value.second, new int(0));
    }
    ee->finalizeObject();
	std::vector<GenericValue> noargs;
	GenericValue res = ee->runFunction(mainFunc, noargs);
    outs() << "[EE] Result: " << res.IntVal << "\n";
    return 0;
}
%}

%token IntLiteral
%token Identifier

%%

Program:    Expression ';' { builder->CreateRet($$); YYACCEPT; };

Expression: Simple
            | Expression '!''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpNE($1, $4), builder->getInt32Ty()); }
            | Expression '=''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpEQ($1, $4), builder->getInt32Ty()); }
            | Expression '<'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSLT($1, $3), builder->getInt32Ty()); }
            | Expression '<''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSLE($1, $4), builder->getInt32Ty()); }
            | Expression '>'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSGT($1, $3), builder->getInt32Ty()); }
            | Expression '>''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSGE($1, $4), builder->getInt32Ty()); }
;
Simple:     Summand
            | Simple '+' Summand { $$ = builder->CreateAdd($1, $3); }
            | Simple '-' Summand { $$ = builder->CreateSub($1, $3); }

Summand:    Factor
            | Summand '*' Factor  { $$ = builder->CreateMul($1, $3); }
            | Summand '/' Factor  { $$ = builder->CreateSDiv($1, $3); }
            | Summand '%' Factor  { $$ = builder->CreateSRem($1, $3); }
;

Factor:     Primary { $$ = $1; }
            | '-' Primary { $$ = builder->CreateNeg($2); }
            | '(' Expression ')' { $$ =$2; }
;

Primary:    IntLiteral { $$ = $1; }
            | Value { $$ = $1; }
;

Value:      Identifier  { $$ = builder->CreateLoad(builder->getInt32Ty(), $1); }

%%