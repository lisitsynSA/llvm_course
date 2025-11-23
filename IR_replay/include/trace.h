#ifndef TRACE_FORMAT_H
#define TRACE_FORMAT_H

#include <stdint.h>

#pragma pack(push, 1)

// Единый заголовок события
typedef struct {
 uint8_t  type;        // 1=call, 2=return, 3=external_call
 uint64_t func_id;
 uint64_t timestamp;   // можно игнорировать
 uint64_t name_len;
} TraceHeader;

#pragma pack(pop)

enum EventType {
 EVENT_CALL = 'C',
 EVENT_RETURN = 'R',
 EVENT_EXTERNAL_CALL = 'E',
 EVENT_MEMOP = 'M',
};

typedef struct {
    uint64_t address;
    uint64_t size;
    uint64_t memop_id;
    uint64_t value;
} MemoryEvent;

#endif
