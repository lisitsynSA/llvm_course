#!/bin/bash
cd $(dirname "$0")
set -x

bison 3.y -d || exit 1
flex 3.lex || exit 1
clang -ly lex.yy.c 3.tab.c -o lex3 || exit 1
echo "1 - 2*3/6*7 - 8 + 9;"
echo "1 - 2*3/6*7 - 8 + 9;" | ./lex3