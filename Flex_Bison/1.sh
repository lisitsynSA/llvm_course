#!/bin/bash
cd $(dirname "$0")
set -x

flex 1.lex || exit 1
clang lex.yy.c -o lex1 || exit 1
printf "10---20--15; // comment\n--42;\n"
printf "10---20--15; // comment\n--42;\n" | ./lex1