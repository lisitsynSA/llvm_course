#!/bin/bash
cd $(dirname "$0")
set -x

flex 1.lex || exit 1
clang lex.yy.c || exit 1
rm lex.yy.c
printf "10---20--15; // comment\n--42;\n"
printf "10---20--15; // comment\n--42;\n" | ./a.out
