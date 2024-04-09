bison -d 11.y
lex 11.lex
clang++ lex.yy.c 11.tab.c ../SDL/sim.c `llvm-config --cppflags --ldflags --libs` -lSDL2 -o lex11
cat 11.txt 
cat 11.txt | ./lex11