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
 EVENT_CALL = 1,
 EVENT_RETURN = 2,
 EVENT_EXTERNAL_CALL = 3
};

struct MemoryEvent {
    uint64_t address;
    uint64_t size;
    uint8_t type;
};

enum MemoryEventType {
    LOAD = 1,
    STORE = 2,
    ARGUMENT = 3
};

#endif
