%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
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

LLVMContext context;
IRBuilder<>* builder;
Module* module;
Function *curFunc;

typedef struct {
    GlobalVariable* irVal;
    int realVal;
} value_t;
std::map<std::string, value_t> ValueMap;


typedef struct {
    GlobalVariable* irVal;
    int size;
    int initVal;
    int* realVal;
} array_t;
std::map<std::string, array_t> ArrayMap;

std::map<std::string, BasicBlock *> BBMap;

int main(int argc, char **argv)
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    // ; ModuleID = 'top'
    // source_filename = "top"
    module = new Module("top", context);
    builder = new IRBuilder<> (context);

    yyparse();

    outs() << "#[LLVM IR]:\n";
    module->print(outs(), nullptr);

    // Interpreter of LLVM IR
    outs() << "Running code...\n";
	ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();

    for (auto& value : ValueMap) {
        ee->addGlobalMapping(value.second.irVal, &value.second.realVal);
    }
    for (auto& array : ArrayMap) {
        array.second.realVal = new int[array.second.size];
        for (int i = 0; i < array.second.size; i++) {
            array.second.realVal[i] = array.second.initVal;
        }
        ee->addGlobalMapping(array.second.irVal, array.second.realVal);
    }

    ee->finalizeObject();
	std::vector<GenericValue> noargs;
    Function *mainFunc = module->getFunction("main");
    if (mainFunc == nullptr) {
	    outs() << "Can't find main\n";
        return -1;
    }
	ee->runFunction(mainFunc, noargs);
	outs() << "Code was run.\n";

    for (auto& value : ValueMap) {
        outs() << value.first << " = " <<  value.second.realVal << "\n";
    }
    for (auto& array : ArrayMap) {
        outs() << array.first << "[" << array.second.size << "] =";
        for (int i = 0; i < array.second.size; i++) {
            outs() << " " << array.second.realVal[i];
        }
        outs() << "\n";
        delete array.second.realVal;
    }
    return 0;
}
%}

%token IntLiteral
%token FunctionBegin
%token FunctionEnd
%token CallFunction
%token Identifier
%token IfToken
%token GotoToken

%%

Parse: Program {YYACCEPT;}

Program: RoutineDeclaration {}
         | VariableDeclaration {} 
         | Program VariableDeclaration {}
         | Program RoutineDeclaration {}

VariableDeclaration : Identifier '=' IntLiteral ';' {
                            printf("Identifier '=' IntLiteral ';'\n");
                            module->getOrInsertGlobal((char*)$1, builder->getInt32Ty());
                            value_t val;
                            val.irVal = module->getNamedGlobal((char*)$1);
                            val.realVal = atoi((char*)$3);
                            ValueMap.insert({(char*)$1, val});
                        }
                    | Identifier '[' IntLiteral ']''=' IntLiteral ';' {
                            printf("Identifier '[' IntLiteral ']''=' IntLiteral ';'\n");
                            int size = atoi((char*)$3);
                            ArrayType *arrayType = ArrayType::get(builder->getInt32Ty(), size);
                            module->getOrInsertGlobal((char*)$1, arrayType);
                            array_t arr;
                            arr.irVal = module->getNamedGlobal((char*)$1);
                            arr.size = atoi((char*)$3);
                            arr.initVal = atoi((char*)$6);
                            ArrayMap.insert({(char*)$1, arr});
                        }

RoutineDeclaration : FunctionBegin Identifier   {
                            printf("FunctionBegin Identifier ...\n");
                            // declare void @Identifier()
                            Function *func = module->getFunction((char*)$2);
                            if (func == nullptr) {
                                FunctionType *funcType = 
                                                        FunctionType::get(builder->getVoidTy(), false);
                                func = Function::Create(funcType, Function::ExternalLinkage, (char*)$2, module);
                            }
                            curFunc = func;
                            // entry:
                            BasicBlock *entryBB = BasicBlock::Create(context, "entry", curFunc);
                            builder->SetInsertPoint(entryBB);
                        } Statements FunctionEnd { 
                            printf("... Statements FunctionEnd\n");
                            builder->CreateRetVoid();
                        }

Statements: Assignment {printf("Assignment\n");}
            | Statements Assignment {printf("Statements Assignment\n");}
            | Statements RoutineCall {printf("Statements RoutineCall\n");}
            | Statements IfStatement {printf("Statements IfStatement\n");}
            | Statements Label {printf("Statements Label\n");}
            | Statements GoTo {printf("Statements GoTo\n");}

Assignment: Value '=' Expression ';' { printf("Value '=' Expression ';'\n"); builder->CreateStore($3, $1); }

RoutineCall: CallFunction Identifier ';' {
                            Function *func = module->getFunction((char*)$2);
                            if (func == nullptr) {
                                FunctionType *funcType = 
                                                        FunctionType::get(builder->getVoidTy(), false);
                                func = Function::Create(funcType, Function::ExternalLinkage, (char*)$2, module);
                            }
                            builder->CreateCall(func);
                        }

IfStatement: IfToken Expression '|' Identifier '|' Identifier ';' {
                            if (BBMap.find((char*)$4) == BBMap.end()) {
                                BBMap.insert({(char*)$4, BasicBlock::Create(context, (char*)$4, curFunc)});
                            }
                            if (BBMap.find((char*)$6) == BBMap.end()) {
                                BBMap.insert({(char*)$6, BasicBlock::Create(context, (char*)$6, curFunc)});
                            }
                            Value *cond = builder->CreateICmpNE($2, builder->getInt32(0));
                            builder->CreateCondBr(cond, BBMap[(char*)$4], BBMap[(char*)$6]);
                        }

Label: Identifier ':'   {
                            if (BBMap.find((char*)$1) == BBMap.end()) {
                                BBMap.insert({(char*)$1, BasicBlock::Create(context, (char*)$1, curFunc)});
                            }
                            BasicBlock *BB = BBMap[(char*)$1];
                            builder->SetInsertPoint(BB);
                        }

GoTo:  GotoToken Identifier ';' {
                            if (BBMap.find((char*)$2) == BBMap.end()) {
                                BBMap.insert({(char*)$2, BasicBlock::Create(context, (char*)$2, curFunc)});
                            }
                            BasicBlock *BB = BBMap[(char*)$2];
                            builder->CreateBr(BB);
                        }

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

Primary:    IntLiteral { $$ = builder->getInt32(atoi((char*)$1)); }
            | Value { $$ = builder->CreateLoad(builder->getInt32Ty(), $1); }
;

Value:      Identifier  {
                            $$ = builder->CreateConstGEP1_32(builder->getInt32Ty(), ValueMap[(char*)$1].irVal, 0);
                        }
            | Identifier '[' Expression ']' {
                            ArrayType *arrayType = ArrayType::get(builder->getInt32Ty(), ArrayMap[(char*)$1].size);
                            std::vector<Value *> gepArgs;
                            gepArgs.push_back(builder->getInt32(0));
                            gepArgs.push_back($3);
                            $$ = builder->CreateGEP(arrayType, ArrayMap[(char*)$1].irVal, gepArgs);
                        }

%%