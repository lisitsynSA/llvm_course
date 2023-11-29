%{
  #include <stdio.h>
  int yyparse();
  int yylex();
  void yyerror(char *s) {
    fprintf (stderr, "%s\n", s);
  }
  int yywrap(void) { return 1; }
%}

%token NUM

%%

EVALUATE: EXPR ';'      { printf("=%d\n", $$); YYACCEPT; } ;

EXPR:    TERM
        | EXPR '+' TERM { $$ = $1 + $3; }
        | EXPR '-' TERM { $$ = $1 - $3; }
;

TERM:    NUM
        | TERM '*' NUM  { $$ = $1 * $3; }
        | TERM '/' NUM  { $$ = $1 / $3; }
;

%%
