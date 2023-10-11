# Simple graphical example
This is example of graphical application with simple interface based on the SDL 2.0.

## Usage:
Simple run:
```
sudo apt install libsdl2-dev
clang sim.c app.c -lSDL2
./a.out
clang sim.c app2.c -lSDL2
./a.out
```
Run with your LLVM Pass:
```
clang sim.c app2.c -lSDL2 -Xclang -load -Xclang ../LLVM_PASS/libPass.so -flegacy-pass-manager
```

## Graphical Interface:
```
void sim_flush();
void sim_put_pixel(int x, int y, int argb);
int sim_rand();
```

## Graphical app instrumentation:
```
clang++ ../LLVM_Pass/Pass_cfg.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang app2.c -c -Xclang -load -Xclang ./libPass.so -flegacy-pass-manager
clang sim.c app2.o ../LLVM_Pass/log.c -lSDL2
./a.out

```

## SDL 2.0 documentation:
https://wiki.libsdl.org