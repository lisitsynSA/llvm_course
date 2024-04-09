#!/bin/bash
cd $(dirname "$0")
set -x

bison 2.y || exit 1
clang -ly 2.tab.c -o lex2 || exit 1
echo "22+3*4-5;"
echo "22+3*4-5;" | ./lex2