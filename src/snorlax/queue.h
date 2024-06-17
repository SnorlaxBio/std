/**
 * @file        snorlax/queue.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 17, 2024
 */

#ifndef   __SNORLAX__QUEUE__H__
#define   __SNORLAX__QUEUE__H__

#include <snorlax.h>

struct queue;
struct queue_func;
struct queue_node;
struct queue_node_func;

typedef struct queue queue_t;
typedef struct queue_func queue_func_t;
typedef struct queue_node queue_node_t;
typedef struct queue_node_func queue_node_func_t;

struct queue {
    queue_func_t * func;

    sync_t * sync;

    uint64_t size;
    queue_node_t * head;
    queue_node_t * tail;
};

struct queue_func {
    queue_t * (*rem)(queue_t *);
    queue_node_t * (*push)(queue_t *, queue_node_t *);
    queue_node_t * (*pop)(queue_t *);
    queue_node_t * (*del)(queue_t *, queue_node_t *);
};

#define queue_rem(queue)            (queue ? ((queue_t *) queue)->func->rem((queue_t *) queue) : nil)
#define queue_push(queue, node)     (queue ? ((queue_t *) queue)->func->push((queue_t *) queue, (queue_node_t *) node) : nil)
#define queue_pop(queue)            (queue ? ((queue_t *) queue)->func->pop((queue_t *) queue) : nil)
#define queue_del(queue, node)      (queue ? ((queue_t *) queue)->func->del((queue_t *) queue, (queue_node_t *) node) : nil)

extern queue_node_t * queue_func_push(queue_t * queue, queue_node_t * node);
extern queue_node_t * queue_func_pop(queue_t * queue);
extern queue_node_t * queue_func_del(queue_t * queue, queue_node_t * node);

struct queue_node {
    queue_node_func_t * func;
    sync_t * sync;

    queue_t * queue;
    queue_node_t * prev;
    queue_node_t * next;
};

struct queue_node_func {
    queue_node_t * (*rem)(queue_node_t *);
};

#define queue_node_rem(node)    (node ? node->func->rem(node) : nil)

#endif // __SNORLAX__QUEUE__H__
