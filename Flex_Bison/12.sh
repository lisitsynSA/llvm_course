bison -d 12.y
lex 12.lex
clang++ lex.yy.c 12.tab.c `llvm-config --cppflags --ldflags --libs` -lSDL2 -o lex12
cat 12.txt 
cat 12.txt | ./lex12