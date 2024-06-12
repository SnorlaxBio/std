/**
 * @file        snorlax/list/linked/double.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 12, 2024
 */

#ifndef   __SNORLAX__LIST_LINKED_DOUBLE__H__
#define   __SNORLAX__LIST_LINKED_DOUBLE__H__

#include <snorlax.h>
#include <snorlax/bucket.h>

struct list_linked_double;
struct list_linked_double_func;
struct list_linked_double_node;
struct list_linked_double_node_func;

typedef struct list_linked_double list_linked_double_t;
typedef struct list_linked_double_func list_linked_double_func_t;
typedef struct list_linked_double_node list_linked_double_node_t;
typedef struct list_linked_double_node_func list_linked_double_node_func_t;

struct list_linked_double {
    list_linked_double_func_t * func;
    uint64_t                    size;
    list_linked_double_node_t * head;
    list_linked_double_node_t * tail;
};

struct list_linked_double_func {
    list_linked_double_t * (*rem)(list_linked_double_t *, bucket_get_t);
    list_linked_double_node_t * (*add)(list_linked_double_t *, bucket_t);
    list_linked_double_node_t * (*del)(list_linked_double_t *, bucket_t);
    void (*clear)(list_linked_double_t *, bucket_get_t);
    list_linked_double_node_t * (*begin)(list_linked_double_t *);
    list_linked_double_node_t * (*end)(list_linked_double_t *);
    list_linked_double_node_t * (*find)(list_linked_double_t *, bucket_t);
    uint64_t (*size)(list_linked_double_t *);

    list_linked_double_node_t * (*push)(list_linked_double_t *, bucket_t);
    list_linked_double_node_t * (*pop)(list_linked_double_t *);
};

struct list_linked_double_node {
    list_linked_double_node_func_t *    func;
    list_linked_double_t *              collection;
    list_linked_double_node_t *         prev;
    list_linked_double_node_t *         next;

    bucket_t                            o;
};

struct list_linked_double_node_func {
    list_linked_double_node_t * (*rem)(list_linked_double_node_t *, bucket_get_t);
};

extern list_linked_double_t * list_linked_double_gen(void);

#define list_linked_double_rem(collection, get)     (collection->func->rem(collection, get))
#define list_linked_double_add(collection, o)       (collection->func->add(collection, o))
#define list_linked_double_del(collection, o, get)  (collection->func->del(collection, o, get))
#define list_linked_double_clear(collection, get)   (collection->func->clear(collection, get))
#define list_linked_double_begin(collection)        (collection->func->begin(collection))
#define list_linked_double_end(collection)          (collection->func->end(collection))
#define list_linked_double_find(collection, o)      (collection->func->find(collection, o))
#define list_linked_double_size(collection)         (collection->func->size(collection))

extern list_linked_double_node_t * list_linked_double_node_gen(list_linked_double_t * collection, bucket_t o);

#define list_linked_double_node_rem(node, get)      (node->func->rem(node, get))

#endif // __SNORLAX__LIST_LINKED_DOUBLE__H__
