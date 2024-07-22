#include <stdlib.h>
#include <string.h>

#include "../mem.h"

static buffer_mem_node_t * buffer_mem_node_func_rem(buffer_mem_node_t * node);
static void * buffer_mem_node_func_front(buffer_mem_node_t * node);
static void * buffer_mem_node_func_back(buffer_mem_node_t * node);
static uint64_t buffer_mem_node_func_length(buffer_mem_node_t * node);
static uint64_t buffer_mem_node_func_remain(buffer_mem_node_t * node);
static uint64_t buffer_mem_node_func_position_get(buffer_mem_node_t * node);
static void buffer_mem_node_func_position_set(buffer_mem_node_t * node, uint64_t v);
static uint64_t buffer_mem_node_func_size_get(buffer_mem_node_t * node);
static void buffer_mem_node_func_size_set(buffer_mem_node_t * node, uint64_t v);
static uint64_t buffer_mem_node_func_capacity_get(buffer_mem_node_t * node);
static void buffer_mem_node_func_capacity_set(buffer_mem_node_t * node, uint64_t v);
static void buffer_mem_node_func_clear(buffer_mem_node_t * node);

static buffer_mem_node_func_t func = {
    buffer_mem_node_func_rem,
    buffer_mem_node_func_front,
    buffer_mem_node_func_back,
    buffer_mem_node_func_length,
    buffer_mem_node_func_remain,
    buffer_mem_node_func_position_get,
    buffer_mem_node_func_position_set,
    buffer_mem_node_func_size_get,
    buffer_mem_node_func_size_set,
    buffer_mem_node_func_capacity_get,
    buffer_mem_node_func_capacity_set,
    buffer_mem_node_func_clear
};

extern buffer_mem_node_t * buffer_mem_node_gen(void) {
    buffer_mem_node_t * node = (buffer_mem_node_t *) calloc(1, sizeof(buffer_mem_node_t));

    node->func = address_of(func);

    return node;
}

static buffer_mem_node_t * buffer_mem_node_func_rem(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    node->mem = memory_rem(node->mem);
    node->sync = sync_rem(node->sync);

    free(node);

    return nil;
}

static void * buffer_mem_node_func_front(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->position < node->size ? &(((uint8_t *) node->mem)[node->position]) : nil;
}

static void * buffer_mem_node_func_back(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->size < node->capacity ? &(((uint8_t *) node->mem)[node->size]) : nil;
}

static uint64_t buffer_mem_node_func_length(buffer_mem_node_t * node) {
// #ifndef   RELEASE
//     snorlaxdbg(node == nil, false, "critical", "");
// #endif // RELEASE

    return node ? node->size - node->position : 0;
}

static uint64_t buffer_mem_node_func_remain(buffer_mem_node_t * node) {
// #ifndef   RELEASE
//     snorlaxdbg(node == nil, false, "critical", "");
// #endif // RELEASE

    return node ? node->capacity - node->size : 0;
}

static uint64_t buffer_mem_node_func_position_get(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->position;
}

static void buffer_mem_node_func_position_set(buffer_mem_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->size < v, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "node->position == node->size: buffer consuming reset buffer");

    if(node->position == node->size) {
        node->position = 0;
        node->size = 0;
        node->capacity = 0;
        node->mem = memory_rem(node->mem);
    }

    node->position = v;
}

static uint64_t buffer_mem_node_func_size_get(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->size;
}

static void buffer_mem_node_func_size_set(buffer_mem_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(v < node->position, false, "critical", "");
    snorlaxdbg(node->capacity < v, false, "critical", "");
#endif // RELEASE

    node->size = v;
}

static uint64_t buffer_mem_node_func_capacity_get(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->capacity;
}

static void buffer_mem_node_func_capacity_set(buffer_mem_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(v < node->size, false, "critical", "");
#endif // RELEASE

    node->capacity = v;
    node->mem = memory_gen(node->mem, v);
}

static void buffer_mem_node_func_clear(buffer_mem_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    node->position = 0;
    node->capacity = 0;
    node->size = 0;
    node->mem = memory_rem(node->mem);
}
