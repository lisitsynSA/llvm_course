#!/bin/bash
cd $(dirname "$0")
set -x

clang++ -O2 examples/fact.c -emit-llvm -S -o fact.ll || exit 1
clang++ -O2 fact.ll -o fact

# 1. Module instrumentation
./unitool -instrument -i fact.ll -o fact.instr.ll || exit 1

# 2. Build project with instrumented module
clang++ -O2 tracer.o fact.instr.ll -o fact.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./fact.instr 4 || exit 1

# 4. Trace dump
./unitool -trace-dump -t ./app.trace -i fact.ll || exit 1

# 5. Generate IR reproducer
./unitool -replay-gen -t ./app.trace -i fact.ll -o fact.replay.ll -c fact.comp.ll -a funcs.txt || exit 1
clang fact.comp.ll -c -o fact.comp.o

# 6. Compile IR reproducer
clang++ tracer.o fact.comp.o fact.replay.ll -o fact.replay || exit 1

# 7. Run IR reproducer
./fact.replay || exit 1

# 8. Clean artefacts
rm fact* app.trace