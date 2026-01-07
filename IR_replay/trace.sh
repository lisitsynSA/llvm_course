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

clang++ -O0 $1 -emit-llvm -S -o $NAME.ll || exit 1

# 1. Module instrumentation
clang++ -O0 -fpass-plugin=./libTracePass.so $1 -emit-llvm -S -o $NAME.instr.ll || exit 1

# 2. Build project with instrumented module
clang++ -O0 tracer.o $NAME.instr.ll ${@:2} -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr 4

exit

# 4. Generate IR reproducer
./IRGen $NAME.ll app.func.trace app.trace replay.ll

# 5. Compile IR reproducer
clang++ replay.ll -o app.replay

# 6. Run IR reproducer
./app.replay
