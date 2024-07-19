#include "list.h"

    // void (*adjust)(buffer_list_t *, uint64_t);
    // void (*write)(buffer_list_t *, const uint8_t *, uint64_t);

static buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer);
static uint8_t * buffer_list_func_front(buffer_list_t * buffer);
static uint8_t * buffer_list_func_back(buffer_list_t * buffer);
static uint64_t buffer_list_func_position_get(buffer_list_t * buffer);

static void buffer_list_func_position_set(buffer_list_t * buffer, uint64_t v);
static uint64_t buffer_list_func_size_get(buffer_list_t * buffer);
static void buffer_list_func_size_set(buffer_list_t * buffer, uint64_t v);
static uint64_t buffer_list_func_capacity_get(buffer_list_t * buffer);
static void buffer_list_func_capacity_set(buffer_list_t * buffer, uint64_t v);
static void buffer_list_func_reset(buffer_list_t * buffer, uint64_t n);
static uint64_t buffer_list_func_remain(buffer_list_t * buffer);
static uint64_t buffer_list_func_length(buffer_list_t * buffer);
static void buffer_list_func_adjust(buffer_list_t * buffer, uint64_t n);
static void buffer_list_func_write(buffer_list_t * buffer, const uint8_t * data, uint64_t n);

static void buffer_list_func_push(buffer_list_t * buffer, buffer_list_node_t * node);
static void buffer_list_func_del(buffer_list_t * buffer, buffer_list_node_t * node);

static buffer_list_func_t func = {
    buffer_list_func_rem,
    buffer_list_func_front,
    buffer_list_func_back,
    buffer_list_func_position_get,
    buffer_list_func_position_set,
    buffer_list_func_size_get,
    buffer_list_func_size_set,
    buffer_list_func_capacity_get,
    buffer_list_func_capacity_set,
    buffer_list_func_reset,
    buffer_list_func_remain,
    buffer_list_func_length,
    buffer_list_func_adjust,
    buffer_list_func_write,
    buffer_list_func_push,
    buffer_list_func_del
};

extern buffer_list_t * buffer_list_gen(void) {
    buffer_list_t * buffer = (buffer_list_t *) calloc(1, sizeof(buffer_list_t));

    buffer->func = address_of(func);

    return buffer;
}

static buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->head;
    while(buffer->head) {
        buffer->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        buffer_list_node_rem(node);

        node = buffer->head;
    }

    buffer->sync = sync_rem(buffer->sync);
    
    free(buffer);

    return nil;
}

static uint8_t * buffer_list_func_front(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    // TODO: UPGRADE
    return (uint8_t *) buffer->front;
}

static uint8_t * buffer_list_func_back(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    // TODO: UPGRADE
    return (uint8_t *) buffer->back;
}

static uint64_t buffer_list_func_position_get(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return (uint64_t) buffer->front;
}

static void buffer_list_func_position_set(buffer_list_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->front = (buffer_list_node_t *) v;
}

static uint64_t buffer_list_func_size_get(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return (uint64_t) buffer->back;
}

static void buffer_list_func_size_set(buffer_list_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->back = (buffer_list_node_t *) v;
}

static uint64_t buffer_list_func_capacity_get(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return (uint64_t) buffer->tail;
}

static void buffer_list_func_capacity_set(buffer_list_t * buffer, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->tail = (buffer_list_node_t *) v;
}

static void buffer_list_func_reset(buffer_list_t * buffer, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(n > 0, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->head;

    while(buffer->head) {
        buffer->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        buffer_list_node_rem(node);

        node = buffer->head;
    }

    buffer->size = 0;
    buffer->head = nil;
    buffer->tail = nil;
    buffer->front = nil;
    buffer->back = nil;
}

static uint64_t buffer_list_func_remain(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->tail != buffer->back && buffer->back != nil ? 1 : 0;
}

static uint64_t buffer_list_func_length(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->front != nil && buffer->front != buffer->back ? 1 : 0;
}

static void buffer_list_func_adjust(buffer_list_t * buffer, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(n > 0, false, "critical", "");
#endif // RELEASE

    while(buffer->head && buffer_list_node_done(buffer->head)) {
        buffer_list_node_t * node = buffer->head;

#ifndef   RELEASE
        snorlaxdbg(buffer->front == node, false, "critical", "");
        snorlaxdbg(buffer->back == node, false, "critical", "");
#endif // RELEASE

        buffer->head = node->next;
        if(buffer->head) {
            buffer->head->prev = nil;
        } else {
            buffer->tail = nil;
        }
        buffer->size = buffer->size - 1;
        node->next = nil;
        node->collection = nil;

        buffer_list_node_rem(node);
    }
}

static void buffer_list_func_write(buffer_list_t * buffer, const uint8_t * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(true, false, "critical", "");
#endif // RELEASE
}

static void buffer_list_func_push(buffer_list_t * buffer, buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    if(buffer->tail) {
        buffer->tail->next = node;
        node->prev = buffer->tail;
    } else {
        buffer->head = node;
    }

    buffer->tail = node;
    buffer->size = buffer->size + 1;
    node->collection = buffer;

    buffer->back = nil;
}

static void buffer_list_func_del(buffer_list_t * buffer, buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * prev = node->prev;
    buffer_list_node_t * next = node->next;

    if(prev) {
        prev->next = next;
        node->prev = nil;
    } else {
        buffer->head = next;
    }

    if(next) {
        next->prev = prev;
        node->next = nil;
    } else {
        buffer->tail = prev;
    }

    buffer->size = buffer->size - 1;
    node->collection = nil;
}
