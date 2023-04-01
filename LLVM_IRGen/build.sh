#! /bin/bash
CPP="g++"
FILES=$1
LLVMCONFIG="llvm-config"
CPPFLAGS="$($LLVMCONFIG --cppflags)"
LDFLAGS="$($LLVMCONFIG --ldflags)"
LIBS="$($LLVMCONFIG --libs)"

echo "[CPPFLAGS] : $CPPFLAGS"
echo "[LDFLAGS] : $LDFLAGS"
echo "[LIBS] : $LIBS"

BUILD_CMD="$CPP $FILES $CPPFLAGS $LDFLAGS $LIBS"
echo "[BUILD] $BUILD_CMD"
$BUILD_CMD
