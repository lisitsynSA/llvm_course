# LLVM Pass example
This is example of LLVM pass that collect static inforamtion about app IR and insert instrumentation for collecting dynamic information.


## For clang-12:
```
cd llvm-pass/ && mkdir build && cd build
CC=clang-12 CXX=clang++-12 cmake ../
make
cd ../../
clang-12 -Xclang -load -Xclang llvm-pass/build/skeleton/libSkeletonPass.so fact.c -emit-llvm -S -o fact.ll
clang-12 -Xclang -load -Xclang llvm-pass/build/skeleton/libSkeletonPass.so fact.c log.c
./a.out 4
```

## Optional flags for compiler (LLVM version > 12):
1. `-flegacy-pass-manager`
2. `-enable-new-pm=0`

## Possible instructions classes:
https://llvm.org/doxygen/classllvm_1_1Instruction.html