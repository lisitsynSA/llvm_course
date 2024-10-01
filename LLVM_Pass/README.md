# LLVM Pass example
This is example of LLVM pass that collect static inforamtion about app IR and insert instrumentation for collecting dynamic information.


## Usage:
```
sudo apt install llvm
clang++ Pass6_cfg.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so log.c ../SDL/sim.c ../SDL/app2.c ../SDL/start.c -lSDL2
```
![Lissajous curve](https://github.com/user-attachments/assets/0fded2a6-a511-4505-8995-47a2670a1c8d)


## Examples for Functions processing:
1. Pass registration
```
clang++ Pass1_reg.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so c_examples/hello.c
opt hello.ll -load-pass-plugin ./libPass.so -passes="function(mem2reg,sroa,myFuncPass),module(myModPass)" -o a.out -print-pipeline-passes
```
2. Print Functions name
```
clang++ Pass2_names.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so 
clang -fpass-plugin=./libPass.so c_examples/hello.c -O2
```
3. Dump Functions, BasicBlocks and Instructions
```
clang++ Pass3_dump.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so c_examples/hello.c -O2
```
4. Dump Uses of Functions, BasicBlocks and Instructions
```
clang++ Pass4_uses.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so c_examples/hello.c
```
5. Change Binary operations to substruction
```
clang++ Pass5_change.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang c_examples/calc.c
./a.out

clang -fpass-plugin=./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll
clang -fpass-plugin=./libPass.so c_examples/calc.c
./a.out
```
6. Instrumentation for code profiling
```
clang++ Pass6_cfg.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang -fpass-plugin=./libPass.so c_examples/calc.c -emit-llvm -S -o calc.ll
clang -fpass-plugin=./libPass.so c_examples/calc.c log.c
./a.out

clang -fpass-plugin=./libPass.so c_examples/fact.c -emit-llvm -S -o fact.ll
clang -fpass-plugin=./libPass.so c_examples/fact.c log.c
./a.out 4
```
7. Example of bad optimization Pass
```
clang++ Pass7_opt.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so

clang c_examples/exp1.c
time ./a.out 1000
clang -fpass-plugin=./libPass.so c_examples/exp1.c
time ./a.out 1000

clang c_examples/exp2.c
time ./a.out 1000
clang -fpass-plugin=./libPass.so c_examples/exp2.c
time ./a.out 1000
```
## Example for IR Reader:
```
clang++ -O3 IR_reader.cpp $(llvm-config --cppflags --ldflags --libs)
./a.out hello.ll
```

## Possible instructions classes:
https://llvm.org/doxygen/classllvm_1_1Instruction.html
