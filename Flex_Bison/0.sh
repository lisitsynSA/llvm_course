flex 0.lex
clang lex.yy.c -lfl -o lex0
printf "Hello ,\nworld!\n"
printf "Hello ,\nworld!\n" | ./lex0