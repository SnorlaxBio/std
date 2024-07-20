// /**
//  * @file        snorlax/queue.c
//  * @brief
//  * @details
//  * 
//  * @author      snorlax <ceo@snorlax.bio>
//  * @since       June 17, 2024
//  */

// #include <stdlib.h>

// #include "queue.h"

// static queue_func_t func = {
//     queue_func_rem,
//     queue_func_add,
//     queue_func_del,
//     queue_func_clear,
//     queue_func_begin,
//     queue_func_end,
//     queue_func_find,
//     queue_func_size,
//     queue_func_node,
//     queue_func_push,
//     queue_func_pop
// };

// extern queue_t * queue_gen(void) {
//     queue_t * queue = (queue_t *) calloc(1, sizeof(queue_t));

//     queue->func = &func;

//     return queue;
// }

// extern queue_t * queue_func_rem(queue_t * queue) {
//     object_lock(queue);
//     queue_node_t * node = queue->head;
//     while(node) {
//         queue->head = queue->head->next;
//         node = queue_node_rem(node);
//         node = queue->head;
//     }
//     queue->head = nil;
//     queue->tail = nil;
//     queue->size = 0LU;
//     object_unlock(queue);
//     queue->sync = sync_rem(queue->sync);
//     free(queue);
//     return nil;
// }

// extern queue_node_t * queue_func_add(queue_t * queue, variable_t v) {
//     queue_node_t * node = queue_node(queue, v);
//     object_lock(queue);
//     if(queue->tail) {
//         queue->tail->next = node;
//         node->prev = queue->tail;
//     } else {
//         queue->head = node;
//     }
//     queue->size = queue->size + 1;
//     node->queue = queue;
//     object_unlock(queue);
//     return node;
// }

// extern queue_node_t * queue_func_del(queue_t * queue, variable_t v) {
//     object_lock(queue);
//     queue_node_t * node = queue_find(queue, v);
//     if(node) {
//         queue_node_t * prev = node->prev;
//         queue_node_t * next = node->next;

//         if(prev) {
//             prev->next = next;
//             node->prev = nil;
//         } else {
//             queue->head = next;
//         }

//         if(next) {
//             next->prev = prev;
//             node->next = nil;
//         } else {
//             queue->tail = prev;
//         }

//         queue->size = queue->size - 1;
//         node->queue = nil;
//     }
//     object_unlock(queue);
//     return node;
// }

// extern void queue_func_clear(queue_t * queue, variable_callback_t callback) {
//     object_lock(queue);
//     queue_node_t * node = queue->head;
//     if(callback) {
//         while(node) {
//             queue->head = queue->head->next;
//             callback(queue_node_get(node));
//             node = queue_node_rem(node);
//             node = queue->head;
//         }
//     } else {
//         while(node) {
//             queue->head = queue->head->next;
//             node = queue_node_rem(node);
//             node = queue->head;
//         }
//     }
//     queue->head = nil;
//     queue->tail = nil;
//     queue->size = 0LU;
//     object_unlock(queue);
// }

// extern queue_node_t * queue_func_begin(queue_t * queue) {
//     return queue->head;
// }

// extern queue_node_t * queue_func_end(queue_t * queue) {
//     return nil;
// }

// extern queue_node_t * queue_func_find(queue_t * queue, variable_t v) {
//     for(queue_node_t * node = queue_begin(queue); node != queue_end(queue); node = queue_node_next(node)) {
//         variable_t value = queue_node_get(node);
//         if(value.o == v.o) return node;
//     }
//     return nil;
// }

// extern uint64_t queue_func_size(queue_t * queue) {
//     return queue->size;
// }

// extern queue_node_t * queue_func_node(variable_t v) {
//     return queue_node_gen(v);
// }

// extern queue_node_t * queue_func_push(queue_t * queue, queue_node_t * node) {
//     if(queue->tail) {
//         queue->tail->next = node;
//         node->prev = queue->tail;
//     } else {
//         queue->head = node;
//     }
//     queue->tail = node;
//     queue->size = queue->size + 1;
//     node->queue = queue;

//     return node;
// }

// extern queue_node_t * queue_func_pop(queue_t * queue) {
//     queue_node_t * node = queue->head;
//     if(node) {
//         queue->head = node->next;
//         if(queue->head) {
//             queue->head->prev = nil;
//         } else {
//             queue->tail = nil;
//         }
//         queue->size = queue->size - 1;
//         node->next = nil;
//         node->queue = nil;
//     }
//     return node;
// }
