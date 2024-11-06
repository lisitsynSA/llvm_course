#!/bin/bash
cd $(dirname "$0")
set -x

bison 4.y -d || exit 1
flex 4.lex || exit 1
clang lex.yy.c 4.tab.c || exit 1
rm 4.tab.c 4.tab.h lex.yy.c
echo "1 - 2*3/6*7 - 8 + 9"
echo "1 - 2*3/6*7 - 8 + 9" | ./a.out
