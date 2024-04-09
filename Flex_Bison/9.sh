#!/bin/bash
cd $(dirname "$0")
set -x

lex 9.lex || exit 1
bison -d 9.y || exit 1
clang++ lex.yy.c 9.tab.c `llvm-config --cppflags --ldflags --libs` -o lex9 || exit 1
cat 9.txt 
cat 9.txt | ./lex9