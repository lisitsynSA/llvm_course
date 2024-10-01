#!/bin/bash
cd $(dirname "$0")
set -x

lex 7.lex || exit 1
bison -d 7.y || exit 1
clang++ lex.yy.c 7.tab.c $(llvm-config --cppflags --ldflags --libs) -o lex7 || exit 1
echo "x + 10*y - (0 == -x) != 0;"
echo "x + 10*y - (0 == -x) != 0;" | ./lex7