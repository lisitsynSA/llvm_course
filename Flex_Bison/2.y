%{
  #include <stdio.h>
  int yylex() { return getc(stdin); }
  void yyerror(char *s) {
    fprintf (stderr, "%s\n", s);
  }
%}

%%

EVALUATE: EXPR ';'      { printf("%d\n", $$);  YYACCEPT; };

EXPR:    TERM
        | EXPR '+' TERM { $$ = $1 + $3; }
        | EXPR '-' TERM { $$ = $1 - $3; }
        ;

TERM:    NUM
        | TERM '*' NUM  { $$ = $1 * $3; }
        | TERM '/' NUM  { $$ = $1 / $3; }
        ;

NUM:      DIGIT
        | NUM DIGIT    { $$ = $1*10+$2; }
        ;

DIGIT:    '0' { $$=0; } | '1' { $$=1; } | '2' { $$=2; } | '3' { $$=3; }
        | '4' { $$=4; } | '5' { $$=5; } | '6' { $$=6; } | '7' { $$=7; }
        | '8' { $$=8; } | '9' { $$=9; }
        ;

%%

int main(int argc, char **argv)
{
  yyparse();
}
