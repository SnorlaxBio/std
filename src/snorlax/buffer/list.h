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

struct buffer_list {
    buffer_list_func_t * func;
    sync_t * sync;
    uint64_t size;
    buffer_list_node_t * head;
    buffer_list_node_t * tail;

    buffer_list_node_t * front;
    buffer_list_node_t * back;
};

struct buffer_list_func {
    buffer_list_t * (*rem)(buffer_list_t *);

    int64_t (*in)(buffer_list_t *, int);
    int64_t (*out)(buffer_list_t *, int);
    int64_t (*inmsg)(buffer_list_t *, int, struct msghdr *, int);
    int64_t (*outmsg)(buffer_list_t *, int, struct msghdr *, int);

    buffer_list_node_t * (*nodegen)(buffer_list_t *);
};

extern buffer_list_t * buffer_list_gen(void);

#define buffer_list_rem(buffer)                     ((buffer)->func->rem(buffer))
#define buffer_list_in(buffer, fd)                  ((buffer)->func->in(buffer, fd))
#define buffer_list_out(buffer, fd)                 ((buffer)->func->out(buffer, fd))
#define buffer_list_inmsg(buffer, fd, msg, flags)   ((buffer)->func->inmsg(buffer, fd, msg, flags))
#define buffer_list_outmsg(buffer, fd, msg, flags)  ((buffer)->func->outmsg(buffer, fd, msg, flags))

#define buffer_list_nodegen(buffer)                 ((buffer)->func->nodegen(buffer))

#define buffer_list_node_state_none                 (0x00000000U)
#define buffer_list_node_state_req                  (0x00000001U <<  1U)
#define buffer_list_node_state_res                  (0x00000001U <<  2U)
#define buffer_list_node_state_done                 (0x00000001U <<  3U)

struct buffer_list_node {
    buffer_list_node_func_t * func;
    sync_t * sync;
    buffer_list_t * collection;
    buffer_list_node_t * prev;
    buffer_list_node_t * next;
    uint32_t status;

    // uint64_t position;
    // uint64_t size;
    // uint64_t capacity;
    // void * mem;
};

struct buffer_list_node_func {
    buffer_list_node_t * (*rem)(buffer_list_node_t *);

    void * (*front)(buffer_list_node_t *);
    void * (*back)(buffer_list_node_t *);
    uint64_t (*remain)(buffer_list_node_t *);
    uint64_t (*length)(buffer_list_node_t *);
    uint64_t (*position_get)(buffer_list_node_t *);
    void (*position_set)(buffer_list_node_t *, uint64_t);
    uint64_t (*size_get)(buffer_list_node_t *);
    void (*size_set)(buffer_list_node_t *, uint64_t);
    uint64_t (*capacity_get)(buffer_list_node_t *);
    void (*capacity_set)(buffer_list_node_t *, uint64_t);
};

#define buffer_list_node_rem(node)              ((node)->func->rem(node))
#define buffer_list_node_front(node)            ((node)->func->front(node))
#define buffer_list_node_back(node)             ((node)->func->back(node))
#define buffer_list_node_remain(node)           ((node)->func->remain(node))
#define buffer_list_node_length(node)           ((node)->func->length(node))
#define buffer_list_node_position_get(node)     ((node)->func->position_get(node))
#define buffer_list_node_position_set(node, n)  ((node)->func->position_set(node, n))
#define buffer_list_node_size_get(node)         ((node)->func->size_get(node))
#define buffer_list_node_size_set(node, n)      ((node)->func->size_set(node, n))
#define buffer_list_node_capacity_get(node)     ((node)->func->capacity_get(node))
#define buffer_list_node_capacity_set(node, n)  ((node)->func->capacity_set(node, n))

#endif // __SNORLAX__BUFFER_LIST__H__
