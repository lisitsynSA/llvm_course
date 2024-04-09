#!/bin/bash
cd $(dirname "$0")
set -x

bison 4.y -d || exit 1
flex 4.lex || exit 1
clang -ly lex.yy.c 4.tab.c -o lex4 || exit 1
echo "1 - 2*3/6*7 - 8 + 9"
echo "1 - 2*3/6*7 - 8 + 9" | ./lex4