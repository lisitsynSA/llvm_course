flex 1.lex
clang lex.yy.c -o lex1
printf "10---20--15; // comment\n--42;\n"
printf "10---20--15; // comment\n--42;\n" | ./lex1