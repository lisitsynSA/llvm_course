## Simulator 
Simple simulator for generated object files for `sim` target. Simulator ELF parsing is based on elfio.
```
clang++ ../SDL/sim.c simulator.cpp -lSDL2 -std=c++17 -o simulator
./simulator ../LLVM_BackEnd/graphic.o
./simulator ../LLVM_BackEnd/app.o
```
## ELFIO repository:
https://github.com/serge1/ELFIO
