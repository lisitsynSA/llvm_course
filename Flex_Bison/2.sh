#!/bin/bash
cd $(dirname "$0")
set -x

bison 2.y -v || exit 1
clang 2.tab.c || exit 1
rm 2.tab.c 2.output
echo "22+3*4-5;"
echo "22+3*4-5;" | ./a.out
