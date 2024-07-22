#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "mem.h"

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer);
static void buffer_mem_func_push(buffer_mem_t * buffer, const void * data, uint64_t n);
static void buffer_mem_func_pop(buffer_mem_t * buffer, uint64_t n);
static void buffer_mem_func_clear(buffer_mem_t * buffer);
static buffer_mem_node_t * buffer_mem_func_front(buffer_mem_t * buffer);
static buffer_mem_node_t * buffer_mem_func_back(buffer_mem_t * buffer, uint64_t hint);

static buffer_mem_func_t func = {
    buffer_mem_func_rem,
    buffer_mem_func_push,
    buffer_mem_func_pop,
    buffer_mem_func_clear,
    buffer_mem_func_front,
    buffer_mem_func_back
};

extern buffer_mem_t * buffer_mem_gen(uint64_t page) {
    buffer_mem_t * buffer = (buffer_mem_t *) calloc(1, sizeof(buffer_mem_t));

    buffer->func = address_of(func);
    buffer->page = page;
    buffer->node = buffer_mem_node_gen();

    return buffer;
}

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->node = buffer_node_rem(buffer->node);
    buffer->sync = sync_rem(buffer->sync);

    free(buffer);

    return nil;
}

static void buffer_mem_func_push(buffer_mem_t * buffer, const void * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(data == nil, false, "critical", "");
    snorlaxdbg(n == 0, false, "critical", "");
#endif // RELEASE

    if(buffer_node_remain(buffer->node) < n) {
        uint64_t page = buffer->page ? buffer->page : 1;

        uint64_t capacity = ((buffer_node_size_get(buffer->node) + n) / page + 1) * page;

        buffer_node_capacity_set(buffer->node, capacity);
    }

    void * mem = buffer_node_back(buffer->node);

    memcpy(mem, data, n);

    buffer_node_size_set(buffer->node, buffer_node_size_get(buffer->node) + n);
}

static void buffer_mem_func_pop(buffer_mem_t * buffer, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_node_position_set(buffer->node, buffer_node_position_get(buffer->node) + n);
}

static void buffer_mem_func_clear(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_node_clear(buffer->node);
}

static buffer_mem_node_t * buffer_mem_func_front(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->node;
}

static buffer_mem_node_t * buffer_mem_func_back(buffer_mem_t * buffer, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    if(buffer_node_remain(buffer->node) < hint) {
        uint64_t page = buffer->page ? buffer->page : 1;

        uint64_t capacity = ((buffer_node_size_get(buffer->node) + hint) / page + 1) * page;

        buffer_node_capacity_set(buffer->node, capacity);
    }

    return buffer->node;
}
