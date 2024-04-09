#!/bin/bash
cd $(dirname "$0")
set -x

bison -d 12.y || exit 1
lex 12.lex || exit 1
clang++ lex.yy.c 12.tab.c `llvm-config --cppflags --ldflags --libs` -lSDL2 -o lex12 || exit 1
cat 12.txt 
cat 12.txt | ./lex12