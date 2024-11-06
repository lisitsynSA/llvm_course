#!/bin/bash
cd $(dirname "$0")
set -x

bison -d 5.y || exit 1
lex 5.lex || exit 1
clang++ lex.yy.c 5.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm 5.tab.c 5.tab.h lex.yy.c
echo "22+ 3/4 -5;"
echo "22+ 3/4 -5;" | ./a.out
