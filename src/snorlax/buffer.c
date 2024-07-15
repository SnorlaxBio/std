/**
 * @file        snorlax/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#include <stdlib.h>
#include <string.h>

#include "buffer.h"

#include "buffer/pool.h"

static uint64_t page = 8;

static buffer_t * buffer_func_rem(buffer_t * buffer);
static uint8_t * buffer_func_front(buffer_t * buffer);
static uint8_t * buffer_func_back(buffer_t * buffer);

static uint64_t buffer_func_position_get(buffer_t * buffer);
static void buffer_func_position_set(buffer_t * buffer, uint64_t v);

static uint64_t buffer_func_size_get(buffer_t * buffer);
static void buffer_func_size_set(buffer_t * buffer, uint64_t v);

static uint64_t buffer_func_capacity_get(buffer_t * buffer);
static void buffer_func_capacity_set(buffer_t * buffer, uint64_t v);

static void buffer_func_reset(buffer_t * buffer, uint64_t capacity);

static uint64_t buffer_func_remain(buffer_t * buffer);
static uint64_t buffer_func_length(buffer_t * buffer);

static void buffer_func_adjust(buffer_t * buffer, uint64_t capacity);

static void buffer_func_write(buffer_t * buffer, const char * data, uint64_t len);

static buffer_func_t func = {
    buffer_func_rem,
    buffer_func_front,
    buffer_func_back,

    buffer_func_position_get,
    buffer_func_position_set,
    buffer_func_size_get,
    buffer_func_size_set,
    buffer_func_capacity_get,
    buffer_func_capacity_set,

    buffer_func_reset,
    buffer_func_remain,
    buffer_func_length,

    buffer_func_adjust,
    buffer_func_write
};

extern buffer_t * buffer_gen(uint64_t capacity) {
    buffer_t * buffer = (buffer_t *) calloc(1, sizeof(buffer_t));

    buffer->func = &func;
    buffer->capacity = capacity;
    
    if(buffer->capacity > 0) {
        buffer->mem = malloc(buffer->capacity);
    }

    return buffer;
}

static buffer_t * buffer_func_rem(buffer_t * buffer) {
    object_lock(buffer);
    buffer->mem = memory_rem(buffer->mem);
    object_unlock(buffer);

    buffer->sync = sync_rem(buffer->sync);

    free(buffer);

    return nil;
}

static uint8_t * buffer_func_front(buffer_t * buffer) {
    uint8_t * mem = nil;

    object_lock(buffer);
    
    if(buffer->mem && (buffer->position < buffer->size)) {
        mem = &buffer->mem[buffer->position];
    }

    object_unlock(buffer);

    return mem;
}

static uint8_t * buffer_func_back(buffer_t * buffer) {
    uint8_t * mem = nil;

    object_lock(buffer);

    if(buffer->mem && (buffer->size < buffer->capacity)) {
        mem = &buffer->mem[buffer->size];
    }

    object_unlock(buffer);

    return mem;
}

static uint64_t buffer_func_position_get(buffer_t * buffer) {
    object_lock(buffer);

    uint64_t n = buffer->position;

    object_unlock(buffer);

    return n;
}

static void buffer_func_position_set(buffer_t * buffer, uint64_t v) {
    object_lock(buffer);

    if(buffer->size <= v) {
        // TODO: CHECK & ASSERTION
    }

    buffer->position = v;

    object_unlock(buffer);
}

static uint64_t buffer_func_size_get(buffer_t * buffer) {
    object_lock(buffer);

    uint64_t n = buffer->size;

    object_unlock(buffer);

    return n;
}

static void buffer_func_size_set(buffer_t * buffer, uint64_t v) {
    object_lock(buffer);

    if(v < buffer->position && buffer->capacity <= v) {
        // TODO: CHECK & ASSERTION
    }

    buffer->size = v;

    object_unlock(buffer);
}

static uint64_t buffer_func_capacity_get(buffer_t * buffer) {
    object_lock(buffer);

    uint64_t n = buffer->capacity;

    object_unlock(buffer);

    return n;
}

static void buffer_func_capacity_set(buffer_t * buffer, uint64_t v) {
    object_lock(buffer);

    if(v < buffer->size) {
        // TODO: ASSERTION
    }

    buffer->capacity = v;
    buffer->mem = memory_gen(buffer->mem, buffer->capacity);

    object_unlock(buffer);
}

static void buffer_func_reset(buffer_t * buffer, uint64_t capacity) {
    object_lock(buffer);

    if(capacity == invalid) capacity = page;

    buffer->capacity = capacity;

    buffer->mem = memory_gen(buffer->mem, buffer->capacity);

    buffer->position = 0;
    buffer->size = 0;

    object_unlock(buffer);
}

static uint64_t buffer_func_remain(buffer_t * buffer) {
    return buffer->capacity - buffer->size;
}

static uint64_t buffer_func_length(buffer_t * buffer) {
    return buffer->size - buffer->position;
}

static void buffer_func_adjust(buffer_t * buffer, uint64_t capacity) {
    if(buffer->position == buffer->size) {
        buffer->position = 0;
        buffer->size = 0;
    } else if((buffer->size - buffer->position) <= buffer->position) {
        memcpy(buffer->mem, &buffer->mem[buffer->position], (buffer->size - buffer->position));
        buffer->size = buffer->size - buffer->position;
        buffer->position = 0;
    }

    buffer->capacity = buffer->size + capacity;

    buffer->mem = (uint8_t *) memory_gen(buffer->mem, buffer->capacity);
}

static void buffer_func_write(buffer_t * buffer, const char * data, uint64_t len) {
    if(buffer_remain(buffer) < len) {
        buffer_func_capacity_set(buffer, buffer_func_capacity_get(buffer) + len);
    }

    memcpy(&buffer->mem[buffer->size], data, len);

    buffer->size = buffer->size + len;
}
