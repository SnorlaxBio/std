#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "list.h"

static buffer_list_func_t func = {
    buffer_list_func_rem,
    buffer_list_func_push,
    buffer_list_func_pop,
    buffer_list_func_clear,
    buffer_list_func_front,
    buffer_list_func_back,
    buffer_list_func_add,
    buffer_list_func_del
};

extern buffer_list_t * buffer_list_gen(buffer_list_node_factory_t nodegen, int64_t page) {
    buffer_list_t * buffer = (buffer_list_t *) calloc(1, sizeof(buffer_list_t));

    buffer->func = address_of(func);
    buffer->nodegen = nodegen ? nodegen : buffer_list_node_gen;
    buffer->page = page;

    return buffer;
}

extern buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->head;
    while(buffer->head) {
        buffer->head = node->next;

        node->collection = nil;
        node->prev = nil;
        node->next = nil;

        buffer_list_node_rem(node);

        node = buffer->head;
    }

    buffer->sync = sync_rem(buffer->sync);

    free(buffer);

    return nil;
}

extern void buffer_list_func_push(buffer_list_t * buffer, const void * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(data == nil, false, "critical", "");
    snorlaxdbg(n == 0, false, "critical", "");
#endif // RELEASE

    if(buffer->tail == nil || buffer_list_node_remain(buffer->tail) < n) {
        buffer_list_nodegen(buffer, data, n);
    } else {
        void * mem = buffer_list_node_back(buffer->tail);

        memcpy(mem, data, n);

        buffer_list_node_size_set(buffer->tail, buffer_list_node_size_get(buffer->tail) + n);
    }
}

extern void buffer_list_func_pop(buffer_list_t * buffer, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->head;

    while(buffer->head && buffer_list_node_size_get(node) && buffer_list_node_size_get(node) == buffer_list_node_position_get(node)) {
        buffer->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        buffer_list_node_rem(node);

        buffer->size = buffer->size - 1;
        node = buffer->head;
        if(node == nil) {
            buffer->tail = nil;
        } else {
            node->prev = nil;
        }
    }

    buffer->front = node;

    while(node && n > 0 && buffer_list_node_size_get(node) && buffer_list_node_size_get(node) != buffer_list_node_position_get(node)) {
        if(n < buffer_list_node_length(node)) {
            buffer_list_node_position_set(node, buffer_list_node_position_get(node) + n);
            n = 0;
            break;
        }

        n = n - buffer_list_node_length(node);

        buffer->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;
        buffer_list_node_rem(node);

        buffer->size = buffer->size - 1;
        buffer->front = buffer->head;
        node = buffer->head;
        if(node == nil) {
            buffer->tail = nil;
        } else {
            node->prev = nil;
        }
    }
}

extern void buffer_list_func_clear(buffer_list_t * buffer) {
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

    buffer->head = nil;
    buffer->tail = nil;
    buffer->size = 0;
    buffer->front = nil;
}

extern buffer_list_node_t * buffer_list_func_front(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->front ? buffer->front : buffer->head;

    while(node && buffer_list_node_position_get(node) == buffer_list_node_size_get(node)) {
        node = node->next;
    }
    
    buffer->front = node;

    return node;
}

extern buffer_list_node_t * buffer_list_func_head(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    return buffer->head;
}

extern buffer_list_node_t * buffer_list_func_back(buffer_list_t * buffer, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->tail;

    if(node == nil || buffer_list_node_remain(node) < hint) {
        uint64_t page = buffer->page ? buffer->page : 1;
        node = buffer_list_nodegen(buffer, nil, (hint / page + 1) * page);
    }

    return node;
}

extern buffer_list_node_t * buffer_list_func_add(buffer_list_t * buffer, buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->collection, false, "critical", "");
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

    return node;
}

extern buffer_list_node_t * buffer_list_func_del(buffer_list_t * buffer, buffer_list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(buffer != node->collection, false, "critical", "");
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

    return node;
}
