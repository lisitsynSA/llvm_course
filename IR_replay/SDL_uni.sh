#!/bin/bash
cd $(dirname "$0")
set -x

OPT="-O0"

clang $OPT ../SDL/app3.c  -emit-llvm -S -o app.ll || exit 1
clang $OPT app.ll ../SDL/start.c ../SDL/sim.c -lSDL2 -o app

# 1. Module instrumentation
./unitool -instrument -i app.ll -o app.instr.ll || exit 1

# 2. Build project with instrumented module
clang $OPT tracer.o app.instr.ll ../SDL/start.c ../SDL/sim.c -lSDL2 -o app.instr || exit 1

# 3. Run instruemnted project - generate app.trace
./app.instr

# 4. Trace dump
#./unitool -trace-dump -t ./app.trace -i app.ll || exit 1

# 5. Generate IR reproducer
./unitool -replay-gen -t ./app.trace -i app.ll -o app.replay.ll -c app.comp.ll -p -a SDL_funcs.txt || exit 1
clang app.comp.ll -c -o app.comp.o

# 6. Compile IR reproducer
clang tracer_log.o app.comp.o app.replay.ll examples/prep.c ../SDL/sim.c -lSDL2 -o app.replay || exit 1
#clang++ app.replay.ll -o app.replay || exit 1

# 7. Run IR reproducer
time ./app.replay

clang -O2 app.replay.ll -S -emit-llvm -o app.replay.opt.ll || exit 1
clang tracer_log.o app.comp.o app.replay.opt.ll examples/prep.c ../SDL/sim.c -lSDL2 -o app.replay.opt || exit 1
time ./app.replay.opt
