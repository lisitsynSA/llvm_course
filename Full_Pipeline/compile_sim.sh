#!/bin/bash
cd $(dirname "$0")
set -x

cat $1.lang | ../Flex_Bison/a.out > $1.ll || exit 1
opt $1.ll -O2 -o $1.opt.ll -S  || exit 1
../../llvm-add-backend/build/bin/llc $1.opt.ll -march sim --filetype=asm  || exit 1
../../llvm-add-backend/build/bin/llc $1.opt.ll -march sim --filetype=obj  || exit 1
../Simulator/simulator $1.opt.o
