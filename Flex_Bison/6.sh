lex 6.lex
bison -d 6.y
clang++ lex.yy.c 6.tab.c `llvm-config --cppflags --ldflags --libs` -o lex6
echo "22+ 3*5*? -5;"
./lex6