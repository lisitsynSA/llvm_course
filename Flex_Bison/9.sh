#!/bin/bash
cd $(dirname "$0")
set -x

lex 9.lex || exit 1
bison -d 9.y || exit 1
clang++ lex.yy.c 9.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm 9.tab.c 9.tab.h lex.yy.c
cat 9.txt
cat 9.txt | ./a.out
