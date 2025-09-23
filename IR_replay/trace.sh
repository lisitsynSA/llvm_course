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


# 0. Build pass
clang++ -O2 src/TracePass.cpp -fPIC -shared -I$(llvm-config --includedir) -I./include -o libPass.so || exit 1

# 1. Module instrumentation
clang++ -O0 -fpass-plugin=./libPass.so $1 -emit-llvm -S -o $NAME.instr.ll || exit 1
clang -O3 src/tracer.c -I./include -emit-llvm -S -o tracer.ll
clang -O3 src/tracer.c -I./include -c -o tracer.o

# 2. Build project with instrumented module
clang++ -O0 tracer.o $NAME.instr.ll ${@:2} -I./include -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr 4

# 4. Build IR generator for traces
clang++ src/IRGen.cpp src/TraceReader.cpp -o IRGen $(llvm-config --cxxflags --ldflags --system-libs --libs core bitreader bitwriter) -I./include || exit 1

# 5. Generate IR reproducer
./IRGen $NAME.ll app.trace replay.ll

# 6. Compile IR reproducer
clang++ replay.ll -o app.replay

# 7. Run IR reproducer
./app.replay
