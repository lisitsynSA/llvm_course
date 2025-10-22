## Simple Simulator implementation:
The ISA description is placed in the `include/ISA.h`.

Application needs 2 argument: file with assembler or binary code and execution mod (1-3):
1. Simulation
2. IR with emulate funcs
3. Full IR generation
```
clang++ $(llvm-config --cppflags --ldflags --libs) *.cpp ../SDL/sim.c -I ../SDL -lSDL2
./a.out examples/app.sim 1-3
./a.out examples/graphic.sim 1-3
./a.out examples/graphic.o 1-3
./a.out examples/clang.o 1-3
./a.out examples/lang.o 1-3
./a.out examples/nodelang.o 1-3
./a.out examples/app2.o 1-3
```
## Link with SDL Example
```
./a.out examples/app.sim 3 -> Copy to app.ll
clang app.ll ../SDL/sim.c ../SDL/start.c -I ../SDL -lSDL2
./a.out
```

## Endless compilation:
Choose IR Generation:
```
./a.out examples/app.sim 3 tmp1_.ll
./a.out examples/clang.o 3 tmp1_.ll
./a.out examples/lang.o 3 tmp1_.ll
./a.out examples/nodelang.o 3 tmp1_.ll
./a.out examples/app2.o 3 tmp1_.ll
```
Compilation loop.sh:
```
IR    -> OptIR : opt tmp(i)_.ll -O2 -o tmp(i).ll -S
OptIR -> Bin   : llc tmp(i).ll -march sim -filetype=obj
Bin   -> IR    : ./a.out tmp(i).o 3 tmp(i+1)_.ll
```
## ELFIO repository:
https://github.com/serge1/ELFIO
