#include <string.h>
#include <stdlib.h>

#include "mem.h"

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer);
static uint8_t * buffer_mem_func_front(buffer_mem_t * buffer);
static uint8_t * buffer_mem_func_back(buffer_mem_t * buffer);
static uint64_t buffer_mem_func_position_get(buffer_mem_t * buffer);
static void buffer_mem_func_position_set(buffer_mem_t * buffer, uint64_t v);
static uint64_t buffer_mem_func_size_get(buffer_mem_t * buffer);
static void buffer_mem_func_size_set(buffer_mem_t * buffer, uint64_t v);
static uint64_t buffer_mem_func_capacity_get(buffer_mem_t * buffer);
static void buffer_mem_func_capacity_set(buffer_mem_t * buffer, uint64_t v);
static void buffer_mem_func_reset(buffer_mem_t * buffer, uint64_t capacity);
static uint64_t buffer_mem_func_remain(buffer_mem_t * buffer);
static uint64_t buffer_mem_func_length(buffer_mem_t * buffer);
static void buffer_mem_func_adjust(buffer_mem_t * buffer, uint64_t capacity);
static void buffer_mem_func_write(buffer_mem_t * buffer, const uint8_t * data, uint64_t len);

static buffer_mem_func_t func = {
    buffer_mem_func_rem,
    buffer_mem_func_front,
    buffer_mem_func_back,
    buffer_mem_func_position_get,
    buffer_mem_func_position_set,
    buffer_mem_func_size_get,
    buffer_mem_func_size_set,
    buffer_mem_func_capacity_get,
    buffer_mem_func_capacity_set,
    buffer_mem_func_reset,
    buffer_mem_func_remain,
    buffer_mem_func_length,
    buffer_mem_func_adjust,
    buffer_mem_func_write
};

extern buffer_mem_t * buffer_mem_gen(uint64_t capacity) {
    buffer_mem_t * buffer = (buffer_mem_t *) calloc(1, sizeof(buffer_mem_t));

    buffer->func = address_of(func);

    buffer->capacity = capacity;

    buffer->mem = memory_gen(buffer->mem, capacity);

    return buffer;
}

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->sync = sync_rem(buffer->sync);
    buffer->mem = memory_rem(buffer->mem);

    free(buffer);

    return nil;
}

static uint8_t * buffer_mem_func_front(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    if(buffer->mem && buffer->position < buffer->size) {
        return &buffer->mem[buffer->position];
    }

    return nil;
}

static uint8_t * buffer_mem_func_back(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    if(buffer->mem && buffer->size < buffer->capacity) {
        return &buffer->mem[buffer->size];
    }

    return nil;
}

static uint64_t buffer_mem_func_position_get(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->position;
}

static void buffer_mem_func_position_set(buffer_mem_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(buffer->size < v, false, "critical", "");
#endif // RELEASE

    buffer->position = v;
}

static uint64_t buffer_mem_func_size_get(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->size;
}

static void buffer_mem_func_size_set(buffer_mem_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(buffer->capacity < v, false, "critical", "");
    snorlaxdbg(v < buffer->position, false, "critical", "");
#endif // RELEASE

    buffer->size = v;
}

static uint64_t buffer_mem_func_capacity_get(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->capacity;
}

static void buffer_mem_func_capacity_set(buffer_mem_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(v < buffer->size, false, "critical", "");
#endif // RELEASE

    buffer->capacity = v;
}

static void buffer_mem_func_reset(buffer_mem_t * buffer, uint64_t capacity) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->capacity = capacity;

    buffer->mem = memory_gen(buffer->mem, buffer->capacity);

    buffer->position = 0;
    buffer->size = 0;
}

static uint64_t buffer_mem_func_remain(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->capacity - buffer->size;
}

static uint64_t buffer_mem_func_length(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->size - buffer->position;
}

static void buffer_mem_func_adjust(buffer_mem_t * buffer, uint64_t capacity) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    if(buffer->position == buffer->size) {
        buffer->position = 0;
        buffer->size = 0;
    } else if((buffer->size - buffer->position) <= buffer->position) {
        memcpy(buffer->mem, &buffer->mem[buffer->position], buffer->size - buffer->position);
        buffer->size = buffer->size - buffer->position;
        buffer->position = 0;
    }

    buffer->capacity = buffer->size + capacity;

    buffer->mem = (uint8_t *) memory_gen(buffer->mem, buffer->capacity);
}

static void buffer_mem_func_write(buffer_mem_t * buffer, const uint8_t * data, uint64_t len) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    if((buffer->capacity - buffer->size) < len || buffer->mem == nil) {
        buffer->capacity = buffer->size + len;
        buffer->mem = memory_gen(buffer->mem, buffer->capacity);
    }

    memcpy(&buffer->mem[buffer->size], data, len);

    buffer->size = buffer->size + len;
}
