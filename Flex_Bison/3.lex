%{
  #include "3.tab.h"
%}

%%

[/][/].*\n      ; // comment
[0-9]+          { yylval = atoi(yytext);
                  return NUM;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%

