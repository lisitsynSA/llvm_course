all: tracer.o tracer_log.o unitool

LLVM_FLAGS = $(shell llvm-config --cxxflags --ldflags --libs)
LLVM_INCPATH = $(shell llvm-config --includedir)

# Build unitool
unitool: src/*.cpp
	clang++ -O2 $(LLVM_FLAGS) $^ -o $@

tracer.o: src/tracer.c
	clang -O2 src/tracer.c -emit-llvm -S -o tracer.ll
	clang -O2 src/tracer.c -c -o tracer.o

tracer_log.o: src/tracer.c
	clang -O2 src/tracer.c -D PRINT_LOG -c -o tracer_log.o

clean:
	rm tracer.o tracer_log.o unitool

.PHONY: all clean