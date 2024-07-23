/**
 * @file        snorlax/buffer/list.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 15, 2024
 */

#ifndef   __SNORLAX__BUFFER_LIST__H__
#define   __SNORLAX__BUFFER_LIST__H__

#include <snorlax.h>
#include <snorlax/buffer.h>

struct buffer_list;
struct buffer_list_func;
struct buffer_list_node;
struct buffer_list_node_func;

typedef struct buffer_list buffer_list_t;
typedef struct buffer_list_func buffer_list_func_t;
typedef struct buffer_list_node buffer_list_node_t;
typedef struct buffer_list_node_func buffer_list_node_func_t;

typedef buffer_list_node_t * (*buffer_list_node_factory_t)(buffer_list_t *, const void *, uint64_t);

struct buffer_list {
    buffer_list_func_t * func;
    sync_t * sync;
    uint64_t size;
    buffer_list_node_t * head;
    buffer_list_node_t * tail;
    buffer_list_node_t * front;

    uint64_t page;
    buffer_list_node_factory_t nodegen;
};

struct buffer_list_func {
    buffer_list_t * (*rem)(buffer_list_t *);
    void (*push)(buffer_list_t *, const void *, uint64_t);
    void (*pop)(buffer_list_t *, uint64_t);
    void (*clear)(buffer_list_t *);
    void (*shrink)(buffer_list_t *);
    buffer_list_node_t * (*front)(buffer_list_t *);
    buffer_list_node_t * (*back)(buffer_list_t *, uint64_t);
    buffer_list_node_t * (*head)(buffer_list_t *);

    buffer_list_node_t * (*add)(buffer_list_t *, buffer_list_node_t *);
    buffer_list_node_t * (*del)(buffer_list_t *, buffer_list_node_t *);
};

extern buffer_list_t * buffer_list_gen(buffer_list_node_factory_t nodegen, int64_t page);

extern buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer);
extern void buffer_list_func_push(buffer_list_t * buffer, const void * data, uint64_t n);
extern void buffer_list_func_pop(buffer_list_t * buffer, uint64_t n);
extern void buffer_list_func_clear(buffer_list_t * buffer);
extern void buffer_list_func_shrink(buffer_list_t * buffer);
extern buffer_list_node_t * buffer_list_func_front(buffer_list_t * buffer);
extern buffer_list_node_t * buffer_list_func_back(buffer_list_t * buffer, uint64_t hint);
extern buffer_list_node_t * buffer_list_func_head(buffer_list_t * buffer);
extern buffer_list_node_t * buffer_list_func_add(buffer_list_t * buffer, buffer_list_node_t * node);
extern buffer_list_node_t * buffer_list_func_del(buffer_list_t * buffer, buffer_list_node_t * node);

#define buffer_list_rem(buffer)                     ((buffer)->func->rem(buffer))
#define buffer_list_push(buffer, data, n)           ((buffer)->func->push(buffer, data, n))
#define buffer_list_pop(buffer, n)                  ((buffer)->func->pop(buffer, n))
#define buffer_list_clear(buffer)                   ((buffer)->func->clear(buffer))
#define buffer_list_front(buffer)                   ((buffer)->func->front(buffer))
#define buffer_list_back(buffer, hint)              ((buffer)->func->back(buffer, hint))
#define buffer_list_add(buffer, node)               ((buffer)->func->add(buffer, node))
#define buffer_list_del(buffer, node)               ((buffer)->func->del(buffer, node))

#define buffer_list_nodegen(buffer, data, n)        ((buffer)->nodegen(buffer, data, n))

struct buffer_list_node {
    buffer_list_node_func_t * func;
    sync_t * sync;
    buffer_list_t * collection;
    buffer_list_node_t * prev;
    buffer_list_node_t * next;
    uint64_t position;
    uint64_t size;
    uint64_t capacity;
    void * mem;
};

struct buffer_list_node_func {
    buffer_list_node_t * (*rem)(buffer_list_node_t *);
    void * (*front)(buffer_list_node_t *);
    void * (*back)(buffer_list_node_t *);
    int32_t (*shrink)(buffer_list_node_t *);
    uint64_t (*length)(buffer_list_node_t *);
    uint64_t (*remain)(buffer_list_node_t *);
    uint64_t (*position_get)(buffer_list_node_t *);
    void (*position_set)(buffer_list_node_t *, uint64_t);
    uint64_t (*size_get)(buffer_list_node_t *);
    void (*size_set)(buffer_list_node_t *, uint64_t);
    uint64_t (*capacity_get)(buffer_list_node_t *);
    void (*capacity_set)(buffer_list_node_t *, uint64_t);
    void (*clear)(buffer_list_node_t *);
};

extern buffer_list_node_t * buffer_list_node_gen(buffer_list_t * buffer, const void * data, uint64_t n);

extern buffer_list_node_t * buffer_list_node_func_rem(buffer_list_node_t * node);
extern void * buffer_list_node_func_front(buffer_list_node_t * node);
extern void * buffer_list_node_func_back(buffer_list_node_t * node);
extern int32_t buffer_list_node_func_shrink(buffer_list_node_t * node);
extern uint64_t buffer_list_node_func_length(buffer_list_node_t * node);
extern uint64_t buffer_list_node_func_remain(buffer_list_node_t * node);
extern uint64_t buffer_list_node_func_position_get(buffer_list_node_t * node);
extern void buffer_list_node_func_position_set(buffer_list_node_t * node, uint64_t v);
extern uint64_t buffer_list_node_func_size_get(buffer_list_node_t * node);
extern void buffer_list_node_func_size_set(buffer_list_node_t * node, uint64_t v);
extern uint64_t buffer_list_node_func_capacity_get(buffer_list_node_t * node);
extern void buffer_list_node_func_capacity_set(buffer_list_node_t * node, uint64_t v);
extern void buffer_list_node_func_clear(buffer_list_node_t * node);

#define buffer_list_node_rem(node)                  ((node)->func->rem(node))
#define buffer_list_node_front(node)                ((node)->func->front(node))
#define buffer_list_node_back(node)                 ((node)->func->back(node))
#define buffer_list_node_shrink(node)               ((node)->func->shrink(node))
#define buffer_list_node_length(node)               ((node) ? (node)->func->length(node) : 0)
#define buffer_list_node_remain(node)               ((node) ? (node)->func->remain(node) : 0)
#define buffer_list_node_position_get(node)         ((node)->func->position_get(node))
#define buffer_list_node_position_set(node, n)      ((node)->func->position_set(node, n))
#define buffer_list_node_size_get(node)             ((node)->func->size_get(node))
#define buffer_list_node_size_set(node, n)          ((node)->func->size_set(node, n))
#define buffer_list_node_capacity_get(node)         ((node)->func->capacity_get(node))
#define buffer_list_node_capacity_set(node, n)      ((node)->func->capacity_set(node, n))
#define buffer_list_node_clear(node)                ((node)->func->clear(node))

#endif // __SNORLAX__BUFFER_LIST__H__
