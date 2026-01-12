#include "../include/trace.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

static FILE *trace_file = NULL;

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
    fflush(trace_file);
  }
}

void trace_called(uint64_t func_id, uint64_t *args, uint64_t num_args) {
  printf("[CALL]");
  uint64_t ts = get_timestamp();

  TraceHeader hdr = {.type = EVENT_CALL, .func_id = func_id, .timestamp = ts};

  safe_write(&hdr, sizeof(hdr));
  safe_write(&num_args, sizeof(num_args));
  printf(" num_args %lu\n", num_args);
  safe_write(args, sizeof(uint64_t) * num_args);
}

void trace_return(uint64_t func_id, uint64_t return_value) {
  printf("[RET]");
  uint64_t ts = get_timestamp();

  TraceHeader hdr = {.type = EVENT_RETURN, .func_id = func_id, .timestamp = ts};

  safe_write(&hdr, sizeof(hdr));
  safe_write(&return_value, sizeof(return_value));
  printf(" return_value %lu\n", return_value);
}

void trace_external_call(uint64_t func_id, uint64_t *args, uint64_t num_args,
                         uint64_t return_value) {
  printf("[EXTCALL]");
  uint64_t ts = get_timestamp();

  TraceHeader hdr = {
      .type = EVENT_EXTERNAL_CALL, .func_id = func_id, .timestamp = ts};

  safe_write(&hdr, sizeof(hdr));
  safe_write(&num_args, sizeof(num_args));
  printf(" num_args %lu", num_args);
  safe_write(args, sizeof(uint64_t) * num_args);
  safe_write(&return_value, sizeof(return_value));
  printf(" return_value %lu\n", return_value);
}

void trace_memory(uint64_t func_id, uint64_t memop_id, uint64_t addr,
                  uint64_t size, uint64_t value) {
  printf("[MEMOP]");
  uint64_t ts = get_timestamp();

  TraceHeader hdr = {.type = EVENT_MEMOP, .func_id = func_id, .timestamp = ts};
  safe_write(&hdr, sizeof(hdr));
  MemoryEvent event = {
      .memop_id = memop_id, .address = addr, .size = size, .value = value};
  printf(" memop_id %lu", memop_id);
  printf(" addr %lu", addr);
  printf(" size %lu", size);
  printf(" value %lu\n", value);
  safe_write(&event, sizeof(event));
}
