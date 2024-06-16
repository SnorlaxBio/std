/**
 * @file        snorlax/list/linked/double.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 16, 2024
 */

#include <stdlib.h>

#include "../../list.h"

static list_linked_double_t * list_linked_double_func_rem(list_linked_double_t * collection, variable_get_t get);
static list_linked_double_node_t * list_linked_double_func_add(list_linked_double_t * collection, variable_t o);
static list_linked_double_node_t * list_linked_double_func_del(list_linked_double_t * collection, variable_t o);
static void list_linked_double_func_clear(list_linked_double_t * collection, variable_get_t get);
static list_linked_double_node_t * list_linked_double_func_begin(list_linked_double_t * collection);
static list_linked_double_node_t * list_linked_double_func_end(list_linked_double_t * collection);
static list_linked_double_node_t * list_linked_double_func_find(list_linked_double_t * collection, variable_t o);
static uint64_t list_linked_double_func_size(list_linked_double_t * collection);
static list_linked_double_node_t * list_linked_double_func_push(list_linked_double_t * collection, variable_t o);
static list_linked_double_node_t * list_linked_double_func_pop(list_linked_double_t * collection);

static list_linked_double_func_t func = {
    list_linked_double_func_rem,
    list_linked_double_func_add,
    list_linked_double_func_del,
    list_linked_double_func_clear,
    list_linked_double_func_begin,
    list_linked_double_func_end,
    list_linked_double_func_find,
    list_linked_double_func_size,
    list_linked_double_func_push,
    list_linked_double_func_pop
};

extern list_linked_double_t * list_linked_double_gen(void) {
    list_linked_double_t * collection = (list_linked_double_t *) calloc(1, sizeof(list_linked_double_t));

    collection->func = &func;

    return collection;
}

static list_linked_double_t * list_linked_double_func_rem(list_linked_double_t * collection, variable_get_t get) {
    object_lock(collection);

    list_linked_double_node_t * node = collection->head;
    while(node) {
        collection->head = collection->head->next;
        node = list_linked_double_node_rem(node, get);
        node = collection->head;
    }

    object_unlock(collection);

    collection->sync = sync_rem(collection->sync);

    free(collection);
    return nil;
}

static list_linked_double_node_t * list_linked_double_func_add(list_linked_double_t * collection, variable_t o) {
    object_lock(collection);

    list_linked_double_node_t * node = (list_linked_double_node_t *) list_linked_double_node_gen(collection, o);

    if(collection->tail) {
        collection->tail->next = node;
        node->prev = collection->tail;
    } else {
        collection->head = node;
    }

    collection->tail = node;
    collection->size = collection->size + 1;

    object_unlock(collection);

    return node;
}

static list_linked_double_node_t * list_linked_double_func_del(list_linked_double_t * collection, variable_t o) {
    object_lock(collection);

    list_linked_double_node_t * node = list_linked_double_func_find(collection , o);

    if(node) {
        list_linked_double_node_t * prev = node->prev;
        list_linked_double_node_t * next = node->next;

        if(prev) {
            prev->next = next;
        } else {
            collection->head = next;
        }

        if(next) {
            next->prev = prev;
        } else {
            collection->tail = prev;
        }

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        collection->size = collection->size - 1;
    }

    object_unlock(collection);

    return node;
}

static void list_linked_double_func_clear(list_linked_double_t * collection, variable_get_t get) {
    object_lock(collection);

    list_linked_double_node_t * node = collection->head;
    while(node) {
        collection->head = collection->head->next;
        node = list_linked_double_node_rem(node, get);
        node = collection->head;
    }
    collection->head = nil;
    collection->tail = nil;
    collection->size = 0lu;

    object_unlock(collection);
}

static list_linked_double_node_t * list_linked_double_func_begin(list_linked_double_t * collection) {
    object_lock(collection);
    list_linked_double_node_t * node = collection->head;
    object_unlock(collection);
    return node;
}

static list_linked_double_node_t * list_linked_double_func_end(list_linked_double_t * collection) {
    return nil;
}

static list_linked_double_node_t * list_linked_double_func_find(list_linked_double_t * collection, variable_t o) {
    list_linked_double_node_t * node = collection->head;
    for(; node != nil; node = node->next) {
        if(node->o.u64 == o.u64) {
            break;
        }
    }
    return node;
}

static uint64_t list_linked_double_func_size(list_linked_double_t * collection) {
    return collection->size;
}

static list_linked_double_node_t * list_linked_double_func_push(list_linked_double_t * collection, variable_t o) {
    list_linked_double_node_t * node = list_linked_double_node_gen(collection, o);

    if(collection->tail) {
        collection->tail->next = node;
        node->prev = collection->tail;
    } else {
        collection->head = node;
    }

    collection->tail = node;
    collection->size = collection->size + 1;

    return node;
}

static list_linked_double_node_t * list_linked_double_func_pop(list_linked_double_t * collection) {
    list_linked_double_node_t * node = collection->head;
    if(node) {
        collection->head = node->next;
        if(collection->head) {
            collection->head->prev = nil;
        } else {
            collection->tail = nil;
        }
        collection->size = collection->size - 1;

        node->next = nil;
        node->collection = nil;
    }

    return node;
}