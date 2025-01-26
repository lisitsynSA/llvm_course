#!/bin/bash
cd $(dirname "$0")
set -x

bison -d 12.y || exit 1
lex 12.lex || exit 1
clang++ lex.yy.c 12.tab.c $(llvm-config --cppflags --ldflags --libs) ../SDL/sim.c -lSDL2 || exit 1
rm 12.tab.c 12.tab.h lex.yy.c
cat 12.txt
cat 12.txt | ./a.out
