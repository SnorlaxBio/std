/**
 * @file        snorlax/list.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 16, 2024
 * 
 * @todo        list_linked_doube 을 double linked list 로 변경하자.
 */

#ifndef   __SNORLAX__LIST__H__
#define   __SNORLAX__LIST__H__

#include <snorlax.h>

struct list;
struct list_func;
struct list_node;
struct list_node_func;

typedef struct list list_t;
typedef struct list_func list_func_t;
typedef struct list_node list_node_t;
typedef struct list_node_func list_node_func_t;

typedef void (*list_node_callback_t)(list_node_t *);

struct list {
    list_func_t * func;
    sync_t * sync;
    uint64_t size;
    list_node_t * head;
    list_node_t * tail;
};

struct list_func {
    list_t * (*rem)(list_t *);
    list_node_t * (*add)(list_t *, list_node_t *);
    list_node_t * (*del)(list_t *, list_node_t *);
    void (*clear)(list_t *, list_node_callback_t);
    list_node_t * (*begin)(list_t *);
    list_node_t * (*end)(list_t *);
};

extern list_t * list_gen(void);

extern list_t * list_func_rem(list_t * collection);
extern list_node_t * list_func_add(list_t * collection, list_node_t * node);
extern list_node_t * list_func_del(list_t * collection, list_node_t * node);
extern void list_func_clear(list_t * collection, list_node_callback_t callback);
extern list_node_t * list_func_begin(list_t * collection);
extern list_node_t * list_func_end(list_t * collection);

#define list_rem(collection)                    ((collection)->func->rem(collection))
#define list_add(collection, node)              ((collection)->func->add(collection, node))
#define list_del(collection, node)              ((collection)->func->del(collection, node))
#define list_clear(collection, callback)        ((collection)->func->clear(collection))
#define list_begin(collection)                  ((collection)->func->begin(collection))
#define list_end(collection)                    ((collection)->func->end(collection))

struct list_node {
    list_node_func_t * func;
    sync_t * sync;
    list_t * collection;
    list_node_t * prev;
    list_node_t * next;
};

struct list_node_func {
    list_node_t * (*rem)(list_node_t *);
};

#define list_node_rem(node)                     ((node)->func->rem(node))



#endif // __SNORLAX__LIST__H__
