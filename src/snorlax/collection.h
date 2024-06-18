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
    collection_t * (*rem)(collection_t *);
    collection_node_t * (*add)(collection_t *, variable_t);
    collection_node_t * (*del)(collection_t *, variable_t);
    void (*clear)(collection_t *, variable_callback_t);
    collection_node_t * (*begin)(collection_t *);
    collection_node_t * (*end)(collection_t *);
    collection_node_t * (*find)(collection_t *, variable_t);
    uint64_t (*size)(collection_t *);
    collection_node_t * (*node)(variable_t);
};

struct collection_node {
    collection_node_func_t *    func;
    sync_t *                    sync;
    collection_t *              collection;
};

struct collection_node_func {
    collection_node_t * (*rem)(collection_node_t *);

    variable_t (*get)(collection_node_t *);
    void (*set)(collection_node_t *, variable_t);
    collection_node_t * (*del)(collection_node_t *, collection_t *);
};

#define collection_rem(collection)              ((collection)->func->rem(collection))
#define collection_add(collection, o)           ((collection)->func->add(collection, o))
#define collection_del(collection, o)           ((collection)->func->del(collection, o))
#define collection_clear(collection, callback)  ((collection)->func->clear(collection, callback))
#define collection_begin(collection)            ((collection)->func->begin(collection))
#define collection_end(collection)              ((collection)->func->end(collection))
#define collection_find(collection, o)          ((collection)->func->find(collection, o))
#define collection_size(collection)             ((collection)->func->size(collection))
#define collection_node(collection, v)          ((collection)->func->node(v))

#define collection_node_rem(node)               ((node) ? (node)->func->rem(node) : nil)
#define collection_node_get(node)               ((node)->func->get(node))
#define collection_node_set(node, v)            ((node)->func->set(node, v))
#define collection_node_del(node, collection)   ((node) ? (node)->func->del(node, collection) : node)

#endif // __SNORLAX__COLLECTION__H__
