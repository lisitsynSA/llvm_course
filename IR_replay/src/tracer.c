#include "../include/trace.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

static FILE *trace_file = NULL;

// TODO: maybe we don't need this optimization
uint64_t callstack_size = 0;

// #define PRINT_LOG

uint64_t get_timestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
}

void safe_write(const void *data, size_t size) {
  if (!trace_file) {
    trace_file = fopen("app.trace", "wb");
  }
  if (trace_file) {
    fwrite(data, 1, size, trace_file);
    // fflush(trace_file);
  }
}

void trace_called(uint64_t op_id, uint8_t *name, uint64_t *args,
                  uint64_t num_args) {
// op_id == 0 - for replay printing
#ifdef PRINT_LOG
  printf("[FUNC %s] %lu args\n", name, num_args);
  for (int i = 0; i < num_args; i++) {
    printf("\targ%d: %lu\n", i, args[i]);
  }
#endif
  if (callstack_size == 0) {
    if (op_id) {
      uint64_t ts = get_timestamp();
      TraceHeader hdr = {
          .type = EVENT_FUNC_START, .op_id = op_id, .timestamp = ts};
      safe_write(&hdr, sizeof(hdr));
      safe_write(&num_args, sizeof(num_args));
      safe_write(args, sizeof(uint64_t) * num_args);
    }
  }
  callstack_size++;
}

void trace_return(uint64_t op_id, uint64_t return_value) {
#ifdef PRINT_LOG
  printf("[RET %lu] ret: %lu\n", op_id, return_value);
#endif
  callstack_size--;
  if (callstack_size == 0) {
    uint64_t ts = get_timestamp();
    TraceHeader hdr = {.type = EVENT_RETURN, .op_id = op_id, .timestamp = ts};
    safe_write(&hdr, sizeof(hdr));
    safe_write(&return_value, sizeof(return_value));
  }
}

void trace_external_call(uint64_t op_id, uint64_t *args, uint64_t num_args,
                         uint64_t return_value) {
#ifdef PRINT_LOG
  printf("[EXTCALL %lu] %lu args\n", op_id, num_args);
  for (int i = 0; i < num_args; i++) {
    printf("\targ%d: %lu\n", i, args[i]);
  }
  printf("\tret: %lu\n", return_value);
#endif
  uint64_t ts = get_timestamp();
  TraceHeader hdr = {
      .type = EVENT_EXTERNAL_CALL, .op_id = op_id, .timestamp = ts};
  safe_write(&hdr, sizeof(hdr));
  safe_write(&num_args, sizeof(num_args));
  safe_write(args, sizeof(uint64_t) * num_args);
  safe_write(&return_value, sizeof(return_value));
}

void trace_memory(uint64_t op_id, uint64_t addr, uint64_t size, uint64_t value,
                  uint8_t mem_type, uint64_t *ptrs) {
#ifdef PRINT_LOG
  printf("[MEMOP %lu] %c %lubit [0x%lx]: %lu\n", op_id, mem_type, size, addr,
         value);
#endif
  uint64_t ts = get_timestamp();
  TraceHeader hdr = {.type = EVENT_MEMOP, .op_id = op_id, .timestamp = ts};
  safe_write(&hdr, sizeof(hdr));
  MemoryEvent event = {
      .type = mem_type, .address = addr, .size = size, .value = value};
  safe_write(&event, sizeof(event));
  if (mem_type == MEM_GEP) {
    safe_write(&value, sizeof(value));
#ifdef PRINT_LOG
    for (int i = 0; i < value; i++) {
      if (i % 2 == 0)
        printf("\t[0x%lx] -", ptrs[i]);
      else
        printf("- [0x%lx]\n", ptrs[i]);
    }
#endif
    safe_write(ptrs, sizeof(uint64_t) * value);
  }
}
