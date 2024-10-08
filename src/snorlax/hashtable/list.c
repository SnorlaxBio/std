#include <stdlib.h>
#include <string.h>

#include "../hashtable.h"

static hashtable_list_func_t func = {
    hashtable_list_func_rem,
    hashtable_list_func_get,
    hashtable_list_func_del,
    hashtable_list_func_push,
    hashtable_list_func_replace
};

extern hashtable_list_t * hashtable_list_gen(hashtable_bucket_t * bucket) {
    hashtable_list_t * list = (hashtable_list_t *) calloc(1, sizeof(hashtable_list_t));

    list->func = address_of(func);

    list->bucket = bucket;

    return list;
}

extern hashtable_list_t * hashtable_list_func_rem(hashtable_list_t * list) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = nil;

    while(node = list->head) hashtable_node_del(node);

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

extern hashtable_node_t * hashtable_list_func_del(hashtable_list_t * list, hashtable_node_key_t * key) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = hashtable_list_get(list, key);

    if(node) {
        hashtable_node_del(node);
    }

    return node;
}

extern void hashtable_list_func_push(hashtable_list_t * list, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(node->list, false, "critical", "");
#endif // RELEASE

    if(list->tail) {
        list->tail->next = node;
        node->prev = list->tail;
    } else {
        list->head = node;
    }

    list->tail = node;

    list->size = list->size + 1;
    list->bucket->size = list->bucket->size + 1;
    list->bucket->collection->size = list->bucket->collection->size + 1;

    node->list = list;
}

extern void hashtable_list_func_replace(hashtable_list_t * list, hashtable_node_t * original, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(list == nil, false, "critical", "");
    snorlaxdbg(original == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(original->list != list, false, "critical", "%p = %p", original->list, list);
#endif // RELEASE

    node->prev = original->prev;
    node->next = original->next;
    node->list = original->list;

    if(original->prev) {
        original->prev->next = node;
    } else {
        original->list->head = node;
    }

    if(original->next) {
        original->next->prev = node;
    } else {
        original->list->tail = node;
    }

    original->list = nil;
    original->prev = nil;
    original->next = nil;
}
