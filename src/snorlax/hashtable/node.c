#include "../hashtable.h"

extern hashtable_node_t * hashtable_node_func_rem(hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->list != nil, false, "critical", "");
#endif // RELEASE

    node->sync = sync_rem(node->sync);

    free(node);

    return nil;
}

extern hashtable_node_t * hashtable_node_func_del(hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->list == nil, false, "critical", "");
    snorlaxdbg(node->list->bucket == nil, false, "critical", "");
    snorlaxdbg(node->list->bucket->collection == nil, false, "critical", "");
#endif // RELEASE

    hashtable_list_t * list = node->list;

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

    node->list = nil;

    list->size = list->size - 1;
    list->bucket->size = list->bucket->size - 1;
    list->bucket->collection->size = list->bucket->collection->size - 1;

    return node;
}

