%{
#define YYSTYPE void*
#include "8.tab.h"
extern "C" int yylex();
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]+          {
                  yylval = strdup(yytext);
                  return IntLiteral;
                }
[A-Za-z_]+      { // identifier or array
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%
