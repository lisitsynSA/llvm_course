#include "trace.h"
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

void trace_called(uint64_t func_id, const char *func_name, uint64_t *args,
                  uint64_t num_args) {
  printf("[LOG] trace_called\n");
  uint64_t ts = get_timestamp();
  uint64_t name_len = strlen(func_name);

  TraceHeader hdr = {.type = EVENT_CALL,
                     .func_id = func_id,
                     .timestamp = ts,
                     .name_len = name_len};

  safe_write(&hdr, sizeof(hdr));
  safe_write(func_name, name_len);
  printf("    func_name %s\n", func_name);
  safe_write(&num_args, sizeof(num_args));
  printf("    num_args %lu\n", num_args);
  safe_write(args, sizeof(uint64_t) * num_args);
  printf("\n");
}

void trace_return(uint64_t func_id, const char *func_name,
                  uint64_t return_value) {
  printf("[LOG] trace_return\n");

  uint64_t ts = get_timestamp();
  uint64_t name_len = strlen(func_name);

  TraceHeader hdr = {.type = EVENT_RETURN,
                     .func_id = func_id,
                     .timestamp = ts,
                     .name_len = name_len};

  safe_write(&hdr, sizeof(hdr));
  safe_write(func_name, name_len);
  printf("    func_name %s\n", func_name);
  safe_write(&return_value, sizeof(return_value));
  printf("    return_value %lu\n", return_value);
  printf("\n");
}

void trace_external_call(uint64_t func_id, const char *func_name,
                         uint64_t *args, uint64_t num_args,
                         uint64_t return_value) {
  printf("[LOG] trace_external_call\n");

  uint64_t ts = get_timestamp();
  uint64_t name_len = strlen(func_name);

  TraceHeader hdr = {.type = EVENT_EXTERNAL_CALL,
                     .func_id = func_id,
                     .timestamp = ts,
                     .name_len = name_len};

  safe_write(&hdr, sizeof(hdr));
  safe_write(func_name, name_len);
  printf("    func_name %s\n", func_name);
  safe_write(&num_args, sizeof(num_args));
  printf("    num_args %lu\n", num_args);
  safe_write(args, sizeof(uint64_t) * num_args);
  safe_write(&return_value, sizeof(return_value));
  printf("    return_value %lu\n", return_value);
  printf("\n");
}

void trace_memory(uint64_t func_id, const char *func_name, uint64_t memop_id,
                  uint64_t addr, uint64_t size, uint64_t value) {
  printf("[LOG] trace_memory\n");

  uint64_t ts = get_timestamp();
  uint64_t name_len = strlen(func_name);

  TraceHeader hdr = {.type = EVENT_MEMOP,
                     .func_id = func_id,
                     .timestamp = ts,
                     .name_len = name_len};
  safe_write(&hdr, sizeof(hdr));
  safe_write(func_name, name_len);
  printf("    func_name %s\n", func_name);
  MemoryEvent event = {
      .memop_id = memop_id, .address = addr, .size = size, .value = value};
  safe_write(&event, sizeof(event));
  printf("\n");
}