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

    if(node->queue == nil) {
        if(queue->tail) {
            queue->tail->next = node;
            node->prev = queue->tail;
        } else {
            queue->head = node;
        }
        queue->tail = node;
        queue->size = queue->size + 1;
        node->queue = queue;
    }

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

extern queue_node_t * queue_func_del(queue_t * queue, queue_node_t * node) {
    if(node->queue == queue) {
        queue_node_t * prev = node->prev;
        queue_node_t * next = node->next;

        if(prev) {
            prev->next = next;
        } else {
            queue->head = next;
        }

        if(next) {
            next->prev = prev;
        } else {
            queue->tail = prev;
        }

        queue->size = queue->size - 1;

        node->prev = nil;
        node->next = nil;
        node->queue = nil;
    }

    return node;
}