#!/bin/bash
cd $(dirname "$0")
set -x

bison -d 11.y || exit 1
lex 11.lex || exit 1
clang++ lex.yy.c 11.tab.c ../SDL/sim.c $(llvm-config --cppflags --ldflags --libs) -lSDL2 -o lex11 || exit 1
cat 11.txt 
cat 11.txt | ./lex11