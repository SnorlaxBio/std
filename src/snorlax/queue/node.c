// #include <stdlib.h>

// #include "../queue.h"

// static queue_node_func_t func = {
//     queue_node_func_rem,
//     queue_node_func_get,
//     queue_node_func_set,
//     queue_node_func_del,
//     queue_node_func_prev,
//     queue_node_func_next
// };

// extern queue_node_t * queue_node_gen(variable_t v) {
//     queue_node_t * node = (queue_node_t *) calloc(1, sizeof(queue_node_t));

//     node->func = &func;
//     node->v = v;

//     return node;
// }

// extern queue_node_t * queue_node_func_rem(queue_node_t * node) {
//     node->sync = sync_rem(node->sync);

//     free(node);

//     return node;
// }

// extern variable_t queue_node_func_get(queue_node_t * node) {
//     return node->v;
// }

// extern void queue_node_func_set(queue_node_t * node, variable_t v) {
//     node->v = v;
// }


// extern queue_node_t * queue_node_func_del(queue_node_t * node, queue_t * queue) {
//     // ASSERT ...
//     if(queue && queue == node->queue) {
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

//     return node;
// }

// extern queue_node_t * queue_node_func_prev(queue_node_t * node) {
//     return node->prev;
// }

// extern queue_node_t * queue_node_func_next(queue_node_t * node) {
//     return node->next;
// }
