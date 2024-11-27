grammar NodeLang;

// Parser rule

program: nodeDecl+;
nodeDecl: '(' 'NODE' (varDecl | funcDecl) ')';
funcDecl: ID '(' ID* ')' node+;
node: nodeDecl | expr | '(' ID node* ')';
varDecl: ID expr;
expr:
	'-' expr
	| ( '*' | '/') expr expr
	| ( '+' | '-') expr expr
	| '(' expr ')'
	| INT
	| ID;

// Lexer rules
ID: [a-zA-Z_]+;
INT: [0-9]+;
WS: [ \t\r\n]+ -> skip;

