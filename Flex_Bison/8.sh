#!/bin/bash
cd $(dirname "$0")
set -x

lex 8.lex || exit 1
bison -d 8.y || exit 1
clang++ lex.yy.c 8.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm 8.tab.c 8.tab.h lex.yy.c
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;"
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;" | ./a.out
