#include "list.h"

static list_func_t func = {
    list_func_rem,
    list_func_add,
    list_func_del,
    list_func_clear,
    list_func_begin,
    list_func_end
};

extern list_t * list_gen(void) {
    list_t * collection = (list_t *) calloc(1, sizeof(list_t));

    collection->func = address_of(func);

    return collection;
}

extern list_t * list_func_rem(list_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    list_node_t * node = collection->head;
    while(collection->head) {
        collection->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        list_node_rem(node);

        node = collection->head;
    }

    collection->sync = sync_rem(collection->sync);

    free(collection);

    return nil;
}

extern list_node_t * list_func_add(list_t * collection, list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->collection != nil, false, "critical", "");
#endif // RELEASE

    if(collection->tail) {
        collection->tail->next = node;
        node->prev = collection->tail;
    } else {
        collection->head = node;
    }

    node->collection = collection;
    collection->tail = node;
    collection->size = collection->size + 1;

    return node;
}

extern list_node_t * list_func_del(list_t * collection, list_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    list_node_t * prev = node->prev;
    list_node_t * next = node->next;

    if(prev) {
        prev->next = next;
        node->prev = nil;
    } else {
        collection->head = next;
    }

    if(next) {
        next->prev = prev;
        node->next = nil;
    } else {
        collection->tail = prev;
    }

    collection->size = collection->size - 1;
    node->collection = nil;

    return node;
}

extern void list_func_clear(list_t * collection, list_node_callback_t callback) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    list_node_t * node = collection->head;
    while(collection->head) {
        collection->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        if(callback) callback(node);

        list_node_rem(node);

        node = collection->head;
    }
    collection->tail = nil;
    collection->size = 0LU;
}

extern list_node_t * list_func_begin(list_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    return collection->head;
}

extern list_node_t * list_func_end(list_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    return collection->tail;
}
