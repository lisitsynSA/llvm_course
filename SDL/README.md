# Simple graphical example
This is example of graphical application with simple interface based on the SDL 2.0.

## Usage:
Simple run:
```
sudo apt install libsdl2-dev
clang start.c sim.c app.c -lSDL2
./a.out
```
Run with your LLVM Pass:
```
# Old Pass Manager
clang start.c sim.c app.c -lSDL2 -Xclang -load -Xclang ../LLVM_PASS/libPass.so -flegacy-pass-manager
# New Pass Manager
clang start.c sim.c app.c -lSDL2 -fpass-plugin=../LLVM_PASS/libPass.so
```

## Graphical Interface:
```
#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
```

## Graphical app instrumentation:
```
clang++ ../LLVM_Pass/Pass_cfg.cpp -c -fPIC -I$(llvm-config --includedir) -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang app.c -c -fpass-plugin=../LLVM_PASS/libPass.so
clang start.c sim.c app.o ../LLVM_Pass/log.c -lSDL2
./a.out

```
## Graphical app IR generations:
```
clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_ir_gen.cpp -lSDL2
./a.out

clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_asm_IRgen_1.cpp -lSDL2
./a.out IRGen/app.s

clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_asm_IRgen_2.cpp -lSDL2
./a.out IRGen/app.s
```

## Simple ISA implementation:
The ISA description is placed in the `ISA/include/ISA.h`.

Application needs 2 argument: file with assembler code and execution mod (1-3):
1. Simulation
2. IR with emulate funcs
3. Full IR generation
```
clang++ $(llvm-config --cppflags --ldflags --libs) ISA/*.cpp sim.c -lSDL2
./a.out ISA/app.s 1
./a.out ISA/app.s 2
./a.out ISA/app.s 3
```

## SDL 2.0 documentation:
https://wiki.libsdl.org