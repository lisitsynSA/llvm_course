lex 7.lex
bison -d 7.y
clang++ lex.yy.c 7.tab.c `llvm-config --cppflags --ldflags --libs` -o lex7
echo "x + 10*y - (0 == -x) != 0;"
echo "x + 10*y - (0 == -x) != 0;" | ./lex7