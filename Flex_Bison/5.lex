%{
#define YYSTYPE llvm::Value*
#include "llvm/IR/IRBuilder.h"
#include "5.tab.h"
extern "C" int yylex();
extern llvm::IRBuilder<>* builder;
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]+          { 
                  yylval = builder->getInt32(atoi(yytext));
                  return NUM;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%