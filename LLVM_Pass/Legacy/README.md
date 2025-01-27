# LLVM Pass example
This is example of LLVM pass that collect static information about app IR and insert instrumentation for collecting dynamic information.


## Usage:
```
sudo apt install llvm
clang++ Pass.cpp -c -fPIC -I$(llvm-config --includedir) -o Pass.o
clang++ Pass.o -fPIC -shared -o libPass.so
clang sim.c app2.c -lSDL2 -Xclang -load -Xclang ../LLVM_PASS/libPass.so -flegacy-pass-manager
```

## Examples for Functions processing:
1. Print Functions name
```
clang++ Pass_start.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
2. Dump Functions, BasicBlocks and Instructions
```
clang++ Pass_dump.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
3. Dump Uses of Functions, BasicBlocks and Instructions
```
clang++ Pass_uses.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager
```
4. Change Binary operations to subtraction
```
clang++ Pass_change.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang c_examples/calc.c
./a.out

clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -flegacy-pass-manager
./a.out
```
5. Instrumentation for code profiling
```
clang++ Pass_cfg.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/calc.c log.c -flegacy-pass-manager
./a.out

clang -Xclang -load -Xclang ./libPass.so c_examples/fact.c -emit-llvm -S -o calc.ll -flegacy-pass-manager
clang -Xclang -load -Xclang ./libPass.so c_examples/fact.c log.c -flegacy-pass-manager
./a.out 4
```
6. Example of bad optimization Pass
```
clang++ Pass_opt.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang c_examples/exp1.c
time ./a.out 1000
clang -Xclang -load -Xclang ./libPass.so c_examples/exp1.c -flegacy-pass-manager
time ./a.out 1000

clang c_examples/exp2.c
time ./a.out 1000
clang -Xclang -load -Xclang ./libPass.so c_examples/exp2.c -flegacy-pass-manager
time ./a.out 1000
```
## Examples for IR Modules:
1. IR reading
```
clang++ -O3 IR_reader.cpp $(llvm-config --cppflags --ldflags --libs) -o IR_reader
./IR_reader hello.ll
```
2. Pass for Module dump
```
clang++ ModPass_dump.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -Xclang -load -Xclang ./libPass.so ./c_examples/hello.c -flegacy-pass-manager -O1 &> test.ll
clang test.ll -o test
./test
```

## Possible instructions classes:
https://llvm.org/doxygen/classllvm_1_1Instruction.html
