#include <string.h>
#include <stdlib.h>

#include "../list.h"

static buffer_list_node_func_t func = {
    buffer_list_node_func_rem,
    buffer_list_node_func_front,
    buffer_list_node_func_back,
    buffer_list_node_func_length,
    buffer_list_node_func_remain,
    buffer_list_node_func_position_get,
    buffer_list_node_func_position_set,
    buffer_list_node_func_size_get,
    buffer_list_node_func_size_set,
    buffer_list_node_func_capacity_get,
    buffer_list_node_func_capacity_set,
    buffer_list_node_func_clear
};

extern buffer_list_node_t * buffer_list_node_gen(buffer_list_t * buffer, const void * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = (buffer_list_node_t *) calloc(1, sizeof(buffer_list_node_t));

    node->func = address_of(func);

    buffer_list_add(buffer, node);

    if(data) {
        uint64_t page = buffer->page ? buffer->page : 1;
        node->capacity = (n / page + 1) * page;
        node->mem = memory_gen(nil, node->capacity);

        memcpy(node->mem, data, n);
        node->size = n;
    }

    return node;
}

extern buffer_list_node_t * buffer_list_node_func_rem(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    if(node->collection) buffer_list_del(node->collection, node);

    node->mem = memory_rem(node->mem);

    free(node);

    return nil;
}

extern void * buffer_list_node_func_front(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->position != node->size ? &(((uint8_t *) node->mem)[node->position]) : nil;
}

extern void * buffer_list_node_func_back(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->size != node->capacity ? &(((uint8_t *) node->mem)[node->size]) : nil;
}

extern uint64_t buffer_list_node_func_length(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->size - node->position;
}

extern uint64_t buffer_list_node_func_remain(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->capacity - node->size;
}

extern uint64_t buffer_list_node_func_position_get(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->position;
}

extern void buffer_list_node_func_position_set(buffer_list_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->size < v, false, "critical", "");
#endif // RELEASE

    node->position = v;
}

extern uint64_t buffer_list_node_func_size_get(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->size;
}

extern void buffer_list_node_func_size_set(buffer_list_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(v < node->position, false, "critical", "");
    snorlaxdbg(node->capacity < v, false, "critical", "");
#endif // RELEASE

    node->size = v;
}

extern uint64_t buffer_list_node_func_capacity_get(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    return node->capacity;
}

extern void buffer_list_node_func_capacity_set(buffer_list_node_t * node, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(v < node->size, false, "critical", "");
#endif // RELEASE

    node->capacity  = v;

    node->mem = memory_gen(node->mem, v);
}

extern void buffer_list_node_func_clear(buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    node->position = 0;
    node->size = 0;
}
