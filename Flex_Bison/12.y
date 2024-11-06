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

LLVMContext context;
IRBuilder<>* builder;
Module* module;
Function *curFunc;
FunctionCallee simFlushFunc;
FunctionCallee simPutPixelFunc;

std::map<std::string, Value *> ValueMap;

std::map<std::string, BasicBlock *> BBMap;

int main(int argc, char **argv)
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    // ; ModuleID = 'top'
    // source_filename = "top"
    module = new Module("top", context);
    builder = new IRBuilder<> (context);

    Type *voidType = Type::getVoidTy(context);
    // declare void @llvm.sim.putpixel(i32 noundef, i32 noundef, i32 noundef)
    ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                                Type::getInt32Ty(context),
                                                Type::getInt32Ty(context)};
    FunctionType *simPutPixelType =
        FunctionType::get(voidType, simPutPixelParamTypes, false);
    simPutPixelFunc =
        module->getOrInsertFunction("llvm.sim.putpixel", simPutPixelType);

    // declare void @llvm.sim.flush()
    FunctionType *simFlushType = FunctionType::get(voidType, false);
    simFlushFunc =
        module->getOrInsertFunction("llvm.sim.flush", simFlushType);

    yyparse();

    if (verifyModule(*module, &outs())) {
        outs() << "[VERIFICATION] FAIL\n";
        return 1;
    }
    module->print(outs(), nullptr);
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
%token PutToken
%token FlushToken

%%

Parse: Program {YYACCEPT;}

Program: RoutineDeclaration {}
         | Program RoutineDeclaration {}

RoutineDeclaration : FunctionBegin Identifier   {
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
                            builder->CreateRetVoid();
                        }

Statements: Assignment {}
            | Statements Assignment {}
            | Statements RoutineCall {}
            | Statements IfStatement {}
            | Statements Label {}
            | Statements GoTo {}
            | Statements Put {}
            | Statements Flush {}

Put : PutToken '('Expression','Expression','Expression')' ';' {
                            Value *args[] = {$3, $5, $7};
                            builder->CreateCall(simPutPixelFunc, args);
                        }

Flush : FlushToken ';' { builder->CreateCall(simFlushFunc); }

Assignment: Value '=' Expression ';' { builder->CreateStore($3, $1); }

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
                            if (ValueMap.find((char*)$1) == ValueMap.end()) {
                                ValueMap.insert({(char*)$1, builder->CreateAlloca(builder->getInt32Ty())});
                            }                            
                            $$ = builder->CreateConstGEP1_32(builder->getInt32Ty(), ValueMap[(char*)$1], 0);
                        }

%%