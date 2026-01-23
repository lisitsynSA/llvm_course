all: tracer.o unitool

LLVM_FLAGS = $(shell llvm-config --cxxflags --ldflags --libs)
LLVM_INCPATH = $(shell llvm-config --includedir)

# Build unitool
unitool: src/ModuleInfo.cpp src/unitool.cpp src/ModuleInstrument.cpp
	clang++ $(LLVM_FLAGS) $^ -o $@

tracer.o: src/tracer.c
	clang -O3 src/tracer.c -emit-llvm -S -o tracer.ll
	clang -O3 src/tracer.c -c -o tracer.o

clean:
	rm tracer.o unitool

.PHONY: all clean