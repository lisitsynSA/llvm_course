#!/bin/bash
cd $(dirname "$0")
set -x

lex 10.lex || exit 1
bison -d 10.y || exit 1
clang++ lex.yy.c 10.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm 10.tab.c 10.tab.h lex.yy.c
cat 10.txt 
cat 10.txt | ./a.out
