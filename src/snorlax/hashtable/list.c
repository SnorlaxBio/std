#include <stdlib.h>
#include <string.h>

#include "../hashtable.h"

static hashtable_list_func_t func = {
    hashtable_list_func_rem,
    hashtable_list_func_get,
    hashtable_list_func_del,
    hashtable_list_func_push
};

extern hashtable_list_t * hashtable_list_gen(void) {
    hashtable_list_t * list = (hashtable_list_t *) calloc(1, sizeof(hashtable_list_t));

    list->func = address_of(func);

    return list;
}

extern hashtable_list_t * hashtable_list_func_rem(hashtable_list_t * list) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = nil;

    while(node = list->head) hashtable_list_del(list, node);

    list->sync = sync_rem(list->sync);

    free(list);

    return nil;
}

extern hashtable_node_t * hashtable_list_func_get(hashtable_list_t * list, hashtable_node_key_t * key) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = nil;

    for(node = hashtable_list_begin(list); node != nil; node = hashtable_node_next(node)) {
        if(node->key.length == key->length && memcmp(node->key.value, key->value, key->length) == 0) {
            break;
        }
        continue;
    }

    return node;
}

extern hashtable_node_t * hashtable_list_func_del(hashtable_list_t * list, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->collection != list, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * prev = node->prev;
    hashtable_node_t * next = node->next;

    if(prev) {
        prev->next = next;
        node->prev = nil;
    } else {
        list->head = next;
    }

    if(next) {
        next->prev = prev;
        node->next = nil;
    } else {
        list->tail = prev;
    }

    node->collection = nil;
    list->size = list->size - 1;

    return node;
}

extern void hashtable_list_func_push(hashtable_list_t * list, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(node->collection, false, "critical", "");
#endif // RELEASE

    if(list->tail) {
        list->tail->next = node;
        node->prev = list->tail;
    } else {
        list->head = node;
    }

    list->tail = node;
    list->size = list->size + 1;
    node->collection = list;
}
