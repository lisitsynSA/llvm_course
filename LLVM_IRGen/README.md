# LLVM IR Generators examples
This is example of LLVM IR generators: from simple "hello world" generator to binary lifter and mathematical expressions frontend. Need to install `llvm-dev` package for build examples.

## Example for IR Reader:
```
clang++ -O2 0_IR_reader.cpp $(llvm-config --cppflags --ldflags --libs)
./a.out hello.ll out.ll
```

## Usage for IR Generators:
```
clang++ $(llvm-config --cppflags --ldflags --libs) main.cpp
./a.out <required arguments>
```

## List of IR Generator examples:
1. Empty main function
2. Empty main function and IR interpretation (ExecutionEngine)
3. Main function generation with "hello world" printing.
4. Main function generation with "hello world" printing + external function.
5. LLVM IR generation for simple calculation with external functions.
5. LLVM IR generation for simple calculation with IR functions.
```
addi x4 x0 105
addi x1 x0 9
add x0 x1 x4
sort
```
6. LLVM IR generation for calculation with branches:
```
ENTRY
    read x2
    addi x3 x3 1
    b LOOP
EXIT
    exit
LOOP
    addi x1 x1 1
    mul x3 x3 x1
    dump x3
    bne x2 x1 LOOP
preEXIT
    sort
    b EXIT
```
7. Simulator that work in 2 ways: calling instruction simulation functions and build IR from input application:
```
read x1
addi x3 x3 1
addi x2 x2 1
mul x3 x3 x2
bne x1 x2 3
write x3
exit
```
8. Simulator extended with complex control flow:
```
ENTRY
    read x1
    addi x3 x3 1
LOOP
    addi x2 x2 1
    mul x3 x3 x2
    bne x1 x2 LOOP
EXIT
    write x3
    exit
```
9. Simple expressions parser, that build LLVM IR for calculation:
```
10 * 7 - 20 
```
9. Expression parser with function support:
```
10 * 7 - sqr(4)/2
```
