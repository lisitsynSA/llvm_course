#!/bin/bash
cd $(dirname "$0")
set -x

bison -d FrontEnd.y || exit 1
lex FrontEnd.lex || exit 1
clang++ lex.yy.c FrontEnd.tab.c $(llvm-config --cppflags --ldflags --libs) || exit 1
rm FrontEnd.tab.c FrontEnd.tab.h lex.yy.c
cat app.lang 
cat app.lang | ./a.out
