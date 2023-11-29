lex 10.lex
bison -d 10.y
clang++ lex.yy.c 10.tab.c `llvm-config --cppflags --ldflags --libs` -o lex10
cat 10.txt 
cat 10.txt | ./lex10