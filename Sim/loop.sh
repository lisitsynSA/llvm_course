#!/bin/bash
cd $(dirname "$0")
set -x

LLVM_BUILD="../../llvm-add-backend/build"
LLC="$LLVM_BUILD/bin/llc"
CLANG="$LLVM_BUILD/bin/clang"
SIM="./a.out"

if [ ! -f ./tmp_0.ll ]; then
    echo "Need tmp_0.ll to start loop!"
    exit 1
fi

for ((i = 0; i < 10; i++)); do
    NAME="tmp_$i"
    $CLANG $NAME.ll -O2 -emit-llvm -S -target sim -o $NAME.opt.ll || exit 1
    $LLC $NAME.opt.ll -march sim --filetype=asm || exit 1
    $LLC $NAME.opt.ll -march sim --filetype=obj || exit 1
    $SIM $NAME.opt.o 1
    $SIM $NAME.opt.o 3 tmp_$((i + 1)).ll
done
