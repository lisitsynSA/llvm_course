#!/bin/bash
cd $(dirname "$0")
set -x

lex 6.lex || exit 1
bison -d 6.y || exit 1
clang++ lex.yy.c 6.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm 6.tab.c 6.tab.h lex.yy.c
echo "Example for lex6: 22+ 3*5*? -5;"
./a.out
