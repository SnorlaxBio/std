/**
 * @file        snorlax/queue.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 17, 2024
 */

#include "queue.h"

extern queue_node_t * queue_func_push(queue_t * queue, queue_node_t * node) {
    // TODO: ASSERTION

    if(queue->tail) {
        queue->tail->next = node;
        node->prev = queue->tail;
    } else {
        queue->head = node;
    }
    queue->tail = node;
    queue->size = queue->size + 1;
    node->queue = queue;

    return node;
}

extern queue_node_t * queue_func_pop(queue_t * queue) {
    queue_node_t * node = queue->head;

    if(node) {
        queue->head = node->next;
        queue->size = queue->size - 1;

        if(queue->head == nil) queue->tail = nil;

        node->queue = nil;
        node->next = nil;
    }

    return node;
}