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
[f][u][n][c]    { return FunctionBegin; }
[e][n][d]       { return FunctionEnd; }
[c][a][l][l]    { return CallFunction; }
[i][f]          { return IfToken; }
[g][o][t][o]    { return GotoToken; }
[P][U][T]       { return PutToken; }
[F][L][U][S][H] { return FlushToken; }
[A-Za-z_]+      { // identifier or array
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%