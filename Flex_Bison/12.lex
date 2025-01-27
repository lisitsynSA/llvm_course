%{
#define YYSTYPE void*
#include "12.tab.h"
extern "C" int yylex();
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]*          {
                  yylval = strdup(yytext);
                  return IntLiteral;
                }
"func"          { return FunctionBegin; }
"end"           { return FunctionEnd; }
"call"          { return CallFunction; }
"if"            { return IfToken; }
"goto"          { return GotoToken; }
"PUT"           { return PutToken; }
"FLUSH"         { return FlushToken; }
[A-Za-z_]+      { // identifier or array
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%
