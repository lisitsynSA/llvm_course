%{
#define YYSTYPE void*
#include "11.tab.h"
extern "C" int yylex();
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]*          {
                  printf("IntLiteral %s\n", yytext);
                  yylval = strdup(yytext);
                  return IntLiteral;
                }
"func"          { printf("FunctionBegin\n"); return FunctionBegin; }
"end"           { printf("FunctionEnd\n"); return FunctionEnd; }
"call"          { printf("CallFunction\n"); return CallFunction; }
"if"            { printf("IfToken\n"); return IfToken; }
"goto"          { printf("GotoToken\n"); return GotoToken; }
"PUT"           { printf("PutToken\n"); return PutToken; }
"FLUSH"         { printf("FlushToken\n"); return FlushToken; }
[A-Za-z_]+      { // identifier or array
                  printf("Identifier %s\n", yytext);
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%
