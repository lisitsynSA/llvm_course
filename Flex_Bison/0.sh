flex 0.lex
clang lex.yy.c || exit 1
rm lex.yy.c
printf "Hello ,\nworld!\n"
printf "Hello ,\nworld!\n" | ./a.out
