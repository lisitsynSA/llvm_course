#!/bin/bash
cd $(dirname "$0")
set -x

LLVM_BUILD="../../llvm-add-backend/build"
LLC="$LLVM_BUILD/bin/llc"
CLANG="$LLVM_BUILD/bin/clang"
LANG="../Flex_Bison/a.out"
NODELANG="../ANTLR/Frontend/a.out"
SIM="../Sim/a.out"

NAME="${1%.*}"

if [[ $1 == *.lang ]]; then
    # Lang source
    cat $1 | $LANG >$NAME.ll || exit 1
    $CLANG $NAME.ll -O2 -emit-llvm -S -target sim -o $NAME.opt.ll || exit 1
elif [[ $1 == *.nl ]]; then
    # NodeLAng source
    $NODELANG $1 $NAME.ll || exit 1
    $CLANG $NAME.ll -O2 -emit-llvm -S -target sim -o $NAME.opt.ll || exit 1
else
    # Clang source
    $CLANG $1 -emit-llvm -S -target sim -O2 -o $NAME.opt.ll
fi

$LLC $NAME.opt.ll -march sim --filetype=asm || exit 1
$LLC $NAME.opt.ll -march sim --filetype=obj || exit 1
$SIM $NAME.opt.o 1

rm $NAME.ll $NAME.opt.ll $NAME.opt.o $NAME.opt.s
