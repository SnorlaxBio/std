/**
 * @file        snorlax/buffer.h
 * @brief
 * @details
 * 
 * 필요할 때만 필요한 만큼 사용한다.
 * 적은 바이트에 대해서 메모리 할당이 일어나지 않도록 한다.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#ifndef   __SNORLAX__BUFFER__H__
#define   __SNORLAX__BUFFER__H__

#include <sys/types.h>
#include <sys/socket.h>

#include <snorlax.h>

struct buffer;
struct buffer_func;
struct buffer_node;
struct buffer_node_func;

typedef struct buffer buffer_t;
typedef struct buffer_func buffer_func_t;
typedef struct buffer_node buffer_node_t;
typedef struct buffer_node_func buffer_node_func_t;

struct buffer {
    buffer_func_t * func;
    sync_t *        sync;
};

struct buffer_func {
    buffer_t * (*rem)(buffer_t *);
    void (*push)(buffer_t *, const void *, uint64_t);
    void (*pop)(buffer_t *, uint64_t);
    void (*clear)(buffer_t *);
    buffer_node_t * (*front)(buffer_t *);
    buffer_node_t * (*back)(buffer_t *, uint64_t);
};

#define buffer_rem(buffer)                      ((buffer)->func->rem(buffer))
#define buffer_push(buffer, data, n)            ((buffer)->func->push(buffer, data, n))
#define buffer_pop(buffer, n)                   ((buffer)->func->pop(buffer, n))
#define buffer_clear(buffer)                    ((buffer)->func->clear(buffer))
#define buffer_front(buffer)                    ((buffer)->func->front(buffer))
#define buffer_back(buffer, hint)               ((buffer)->func->back(buffer, hint))

struct buffer_node {
    buffer_node_func_t * func;
    sync_t * sync;
};

struct buffer_node_func {
    buffer_node_t * (*rem)(buffer_node_t *);
    void * (*front)(buffer_node_t *);
    void * (*back)(buffer_node_t *);
    uint64_t (*length)(buffer_node_t *);
    uint64_t (*remain)(buffer_node_t *);
    uint64_t (*position_get)(buffer_node_t *);
    void (*position_set)(buffer_node_t *, uint64_t);
    uint64_t (*size_get)(buffer_node_t *);
    void (*size_set)(buffer_node_t *, uint64_t);
    uint64_t (*capacity_get)(buffer_node_t *);
    void (*capacity_set)(buffer_node_t *, uint64_t);
    void (*clear)(buffer_node_t *);
};

#define buffer_node_rem(node)                   ((node)->func->rem(node))
#define buffer_node_front(node)                 ((node)->func->front(node))
#define buffer_node_back(node)                  ((node)->func->back(node))
#define buffer_node_length(node)                ((node) ? (node)->func->length(node) : 0)
#define buffer_node_remain(node)                ((node) ? (node)->func->remain(node) : 0)
#define buffer_node_position_get(node)          ((node)->func->position_get(node))
#define buffer_node_position_set(node, n)       ((node)->func->position_set(node, n))
#define buffer_node_size_get(node)              ((node)->func->size_get(node))
#define buffer_node_size_set(node, n)           ((node)->func->size_set(node, n))
#define buffer_node_capacity_get(node)          ((node)->func->capacity_get(node))
#define buffer_node_capacity_set(node, n)       ((node)->func->capacity_set(node, n))
#define buffer_node_clear(node)                 ((node)->func->clear(node))

#endif // __SNORLAX__BUFFER__H__
