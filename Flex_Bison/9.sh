lex 9.lex
bison -d 9.y
clang++ lex.yy.c 9.tab.c `llvm-config --cppflags --ldflags --libs` -o lex9
cat 9.txt 
cat 9.txt | ./lex9