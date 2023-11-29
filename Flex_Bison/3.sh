bison 3.y -d
flex 3.lex
clang -ly lex.yy.c 3.tab.c -o lex3
echo "1 - 2*3/6*7 - 8 + 9;"
echo "1 - 2*3/6*7 - 8 + 9;" | ./lex3