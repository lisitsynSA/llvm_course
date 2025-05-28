#!/bin/bash
cd $(dirname "$0")
set -x

if [ $# -eq 0 ]; then
    echo "Error: Need arguments with source code"
    exit 1
fi

if [ ! -f $1 ]; then
    echo "Error: $1 not found!"
    exit 1
fi

NAME=$(basename -- "$1")
NAME="${NAME%.*}"

clang++ Pass_trace.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so || exit 1

clang -O2 $1 -emit-llvm -S -o $NAME.ll || exit 1
clang -O2 -fpass-plugin=./libPass.so $1 -emit-llvm -S -o $NAME.log.ll || exit 1
clang -O2 log.c $NAME.log.ll ${@:2} || exit 1