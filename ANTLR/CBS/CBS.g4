grammar CBS;

seq : '{' seq* '}' seq*;
//WS: [ \t\r\n]+ -> skip;
