lex 8.lex
bison -d 8.y
clang++ lex.yy.c 8.tab.c `llvm-config --cppflags --ldflags --libs` -o lex8
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;"
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;" | ./lex8