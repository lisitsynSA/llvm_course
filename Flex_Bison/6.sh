#!/bin/bash
cd $(dirname "$0")
set -x

lex 6.lex || exit 1
bison -d 6.y || exit 1
clang++ lex.yy.c 6.tab.c $(llvm-config --cppflags --ldflags --libs) -o lex6 || exit 1
echo "22+ 3*5*? -5;"
./lex6