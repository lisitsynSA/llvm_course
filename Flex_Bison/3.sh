#!/bin/bash
cd $(dirname "$0")
set -x

bison 3.y -d || exit 1
flex 3.lex || exit 1
clang lex.yy.c 3.tab.c || exit 1
rm 3.tab.c 3.tab.h lex.yy.c
echo "1 - 2*3/6*7 - 8 + 9;"
echo "1 - 2*3/6*7 - 8 + 9;" | ./a.out
