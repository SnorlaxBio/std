/**
 * @file        snorlax/collection.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 11, 2024
 */

#ifndef   __SNORLAX__COLLECTION__H__
#define   __SNORLAX__COLLECTION__H__

#include <snorlax.h>

struct collection;
struct collection_func;
struct collection_node;
struct collection_node_func;

typedef struct collection collection_t;
typedef struct collection_func collection_func_t;
typedef struct collection_node collection_node_t;
typedef struct collection_node_func collection_node_func_t;

struct collection {
    collection_func_t * func;
    sync_t *            sync;
    uint64_t            size;
};

struct collection_func {
    collection_t * (*rem)(collection_t *, variable_get_t);
    collection_node_t * (*add)(collection_t *, variable_t);
    collection_node_t * (*del)(collection_t *, variable_t);
    void (*clear)(collection_t *, variable_get_t);
    collection_node_t * (*begin)(collection_t *);
    collection_node_t * (*end)(collection_t *);
    collection_node_t * (*find)(collection_t *, variable_get_t);
    uint64_t (*size)(collection_t *);
};

struct collection_node {
    collection_node_func_t *    func;
    sync_t *                    sync;
    collection_t *              collection;
};

struct collection_node_func {
    collection_node_t * (*rem)(collection_node_t *, variable_get_t);
};

#define collection_rem(collection, get)         (collection->func->rem(collection, get))
#define collection_add(collection, o)           (collection->func->add(collection, o))
#define collection_del(collection, o, get)      (collection->func->del(collection, o, get))
#define collection_clear(collection, get)       (collection->func->clear(collection, get))
#define collection_begin(collection)            (collection->func->begin(collection))
#define collection_end(collection)              (collection->func->end(collection))
#define collection_find(collection, o)          (collection->func->find(collection, o))
#define collection_size(o)                      (collection->func->size(o))

#define collection_node_rem(node, get)          (node->func->rem(node, get))

#endif // __SNORLAX__COLLECTION__H__
