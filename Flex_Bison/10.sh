#!/bin/bash
cd $(dirname "$0")
set -x

lex 10.lex || exit 1
bison -d 10.y || exit 1
clang++ lex.yy.c 10.tab.c $(llvm-config --cppflags --ldflags --libs) -o lex10 || exit 1
cat 10.txt 
cat 10.txt | ./lex10