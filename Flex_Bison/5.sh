bison -d 5.y
lex 5.lex
clang++ lex.yy.c 5.tab.c `llvm-config --cppflags --ldflags --libs` -o lex5
echo "22+ 3/4 -5;"
echo "22+ 3/4 -5;" | ./lex5