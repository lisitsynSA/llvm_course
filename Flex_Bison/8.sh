#!/bin/bash
cd $(dirname "$0")
set -x

lex 8.lex || exit 1
bison -d 8.y || exit 1
clang++ lex.yy.c 8.tab.c `llvm-config --cppflags --ldflags --libs` -o lex8 || exit 1
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;"
echo "x + 10*y[3*5 + x] - (0 == -x) != 0;" | ./lex8