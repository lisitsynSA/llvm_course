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
%token ADD SUB MUL DIV EOL

%%

EVALUATE: EXPR EOL      { printf("=%d\n", $$); YYACCEPT; } ;

EXPR:    TERM
        | EXPR ADD TERM { $$ = $1 + $3; }
        | EXPR SUB TERM { $$ = $1 - $3; }
;

TERM:    NUM
        | TERM MUL NUM  { $$ = $1 * $3; }
        | TERM DIV NUM  { $$ = $1 / $3; }
;

%%

