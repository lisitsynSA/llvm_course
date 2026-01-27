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
OPT="-O0"

clang++ $OPT $1 -emit-llvm -S -o $NAME.ll || exit 1

# 1. Module instrumentation
./unitool -instrument -i $NAME.ll -o $NAME.instr.ll

# 2. Build project with instrumented module
clang++ $OPT tracer.o $NAME.instr.ll ${@:2} -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr 4

# 4. Trace dump
#./unitool -trace-dump -t ./app.trace
./unitool -trace-dump -t ./app.trace -i $NAME.ll

# 5. Generate IR reproducer
./unitool -replay-gen -t ./app.trace -i $NAME.ll -o $NAME.replay.ll

# 6. Compile IR reproducer
clang++ tracer.o $NAME.replay.ll -o app.replay

# 7. Run IR reproducer
./app.replay
