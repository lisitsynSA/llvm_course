# LLVM Pass example
This is example of LLVM pass that collect static inforamtion about app IR and insert instrumentation for collecting dynamic information.


## Usage:
```
sudo apt install llvm
clang++ Pass.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang sim.c app2.c -lSDL2 -Xclang -load -Xclang ../LLVM_PASS/libPass.so -flegacy-pass-manager
```

## Examples:
1. Print Functions name
```
clang++ Pass_start.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
2. Dump Functions, BasicBlocks and Instructions
```
clang++ Pass_dump.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
3. Dump Uses of Functions, BasicBlocks and Instructions
```
clang++ Pass_uses.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
4. Change Binary operations to substruction
```
clang++ Pass_change.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so

clang c_examples/calc.c
./a.out

clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -flegacy-pass-manager
./a.out
```
5. Instrumentation for code profiling
```
clang++ Pass_cfg.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so

clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c log.c -flegacy-pass-manager
./a.out

clang -Xclang -load -Xclang ./libPass.so c_examples/fact.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/fact.c log.c -flegacy-pass-manager
./a.out 4
```
6. Example of bad optimization Pass
```
clang++ Pass_opt.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so

clang c_examples/exp1.c
time ./a.out 1000
clang -Xclang -load -Xclang ./libPass.so c_examples/exp1.c -flegacy-pass-manager
time ./a.out 1000

clang c_examples/exp2.c
time ./a.out 1000
clang -Xclang -load -Xclang ./libPass.so c_examples/exp2.c -flegacy-pass-manager
time ./a.out 1000
```

## Possible instructions classes:
https://llvm.org/doxygen/classllvm_1_1Instruction.html