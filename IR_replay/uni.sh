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
OPT="-O2"

clang++ $OPT $1 -emit-llvm -S -o $NAME.ll || exit 1
clang++ $OPT $NAME.ll ${@:2} -o app

# 1. Module instrumentation
./unitool -instrument -i $NAME.ll -o $NAME.instr.ll || exit 1

# 2. Build project with instrumented module
clang++ $OPT tracer.o $NAME.instr.ll ${@:2} -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr 4 || exit 1

# 4. Trace dump
./unitool -trace-dump -t ./app.trace -i $NAME.ll || exit 1

# 5. Generate IR reproducer
./unitool -replay-gen -t ./app.trace -i $NAME.ll -o $NAME.replay.ll -c $NAME.comp.ll -a funcs.txt || exit 1
clang $NAME.comp.ll -c -o $NAME.comp.o

# 6. Compile IR reproducer
clang++ tracer.o $NAME.comp.o $NAME.replay.ll -o app.replay || exit 1

# 7. Run IR reproducer
./app.replay || exit 1
