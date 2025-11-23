all: libTracePass.so TraceDump IRGen tracer.o

LLVM_FLAGS = $(shell llvm-config --cxxflags --ldflags --libs core bitreader bitwriter)
LLVM_INCPATH = $(shell llvm-config --includedir)


# Build pass
libTracePass.so: src/TracePass.cpp
	clang++ -fPIC -shared -I$(LLVM_INCPATH) $^ -o $@

# Build IR generator for traces
TraceDump: src/TraceDump.cpp src/TraceReader.cpp
	clang++ $^ -o $@

# Build IR generator for traces
IRGen: src/IRGen.cpp src/TraceReader.cpp src/TraceReplGen.cpp
	clang++ $(LLVM_FLAGS) $^ -o $@

tracer.o: src/tracer.c
	clang -O3 src/tracer.c -emit-llvm -S -o tracer.ll
	clang -O3 src/tracer.c -c -o tracer.o

clean:
	rm libTracePass.so TraceDump IRGen tracer.o

.PHONY: all clean