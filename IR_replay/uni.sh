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
./unitool $NAME.ll $NAME.instr.ll

# 2. Build project with instrumented module
clang++ $OPT tracer.o $NAME.instr.ll ${@:2} -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr 4

exit

# 4. Dump trace
./TraceDump ./app.func.trace ./app.trace

exit

# 5. Generate IR reproducer
./IRGen $NAME.ll app.func.trace app.trace replay.ll

# 6. Compile IR reproducer
clang++ replay.ll -o app.replay

# 7. Run IR reproducer
./app.replay
