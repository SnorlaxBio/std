/**
 * @file        snorlax/list/linked/double/node.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 16, 2024
 */

#include <stdlib.h>

#include "../../../list.h"

#include "../../../queue.h"

typedef list_linked_double_node_t * (*list_linked_double_node_func_rem_t)(list_linked_double_node_t *);
typedef variable_t (*list_linked_double_node_func_get_t)(list_linked_double_node_t *);
typedef void (*list_linked_double_node_func_set_t)(list_linked_double_node_t *, variable_t);
typedef list_linked_double_node_t * (*list_linked_double_node_func_del_t)(list_linked_double_node_t *, list_linked_double_t *);
typedef list_linked_double_node_t * (*list_linked_double_node_func_prev_t)(list_linked_double_node_t *);
typedef list_linked_double_node_t * (*list_linked_double_node_func_next_t)(list_linked_double_node_t *);

static list_linked_double_node_func_t func = {
    (list_linked_double_node_func_rem_t) queue_node_func_rem,
    (list_linked_double_node_func_get_t) queue_node_func_get,
    (list_linked_double_node_func_set_t) queue_node_func_set,
    (list_linked_double_node_func_del_t) queue_node_func_del,
    (list_linked_double_node_func_prev_t) queue_node_func_prev,
    (list_linked_double_node_func_next_t) queue_node_func_next
};

extern list_linked_double_node_t * list_linked_double_node_gen(list_linked_double_t * collection, variable_t o) {
    list_linked_double_node_t * node = (list_linked_double_node_t *) calloc(1, sizeof(list_linked_double_node_t));

    node->collection = collection;
    node->func = &func;
    node->o = o;

    return node;
}

static list_linked_double_node_t * list_linked_double_node_func_rem(list_linked_double_node_t * node) {
    if(node->collection) {
        list_linked_double_node_t * prev = node->prev;
        list_linked_double_node_t * next = node->next;

        if(prev) {
            prev->next = next;
        } else {
            node->collection->head = next;
        }
        if(next) {
            next->prev = prev;
        } else {
            node->collection->tail = prev;
        }

        node->collection->size = node->collection->size - 1;
        node->prev = nil;
        node->next = nil;
        node->collection = nil;
    }

    free(node);
    
    return nil;
}