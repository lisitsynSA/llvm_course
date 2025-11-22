# Simple graphical example
This is example of graphical application with simple interface based on the SDL 2.0.

## Usage:
Simple run:
```
sudo apt install libsdl2-dev
make app
    clang start.c sim.c app.c -lSDL2 -o app
./app
```
Run interpreter:
```
make full.bc
    clang start.c sim.c app.c -emit-llvm -S
    llvm-link start.ll sim.ll app.ll -o full.bc
lli --load=/usr/lib/x86_64-linux-gnu/libSDL2.so full.bc
```
Run with your LLVM Pass:
```
# Old Pass Manager
clang start.c sim.c app.c ../LLVM_Pass/log.c -lSDL2 -Xclang -load -Xclang ../LLVM_Pass/libPass.so -flegacy-pass-manager -O2
# New Pass Manager
clang start.c sim.c app.c ../LLVM_Pass/log.c -lSDL2 -fpass-plugin=../LLVM_Pass/libPass.so -O2
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
clang++ ../LLVM_Pass/Pass_cfg.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang app.c -c -fpass-plugin=../LLVM_PASS/libPass.so -O2
clang start.c sim.c app.o ../LLVM_Pass/log.c -lSDL2 -O2
./a.out

```
## Graphical app IR generations:
```
clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_ir_gen.cpp -lSDL2 -o ir_gen
./ir_gen

clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_asm_IRgen_1.cpp -lSDL2 -o asm2ir
./asm2ir IRGen/app.s

clang++ $(llvm-config --cppflags --ldflags --libs) sim.c IRGen/app_asm_IRgen_2.cpp -lSDL2 -o asm2fullir
./asm2fullir IRGen/app.s
```

## SDL 2.0 documentation:
https://wiki.libsdl.org
