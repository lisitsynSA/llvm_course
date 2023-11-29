bison 4.y -d
flex 4.lex
clang -ly lex.yy.c 4.tab.c -o lex4
echo "1 - 2*3/6*7 - 8 + 9"
echo "1 - 2*3/6*7 - 8 + 9" | ./lex4