/**
 * @file        snorlax/collection.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
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

typedef void (collection_node_callback_t)(collection_node_t *);

struct collection {
    collection_func_t * func;
    sync_t *            sync;
    uint64_t            size;
};

struct collection_func {
    collection_t * (*rem)(collection_t *);
    collection_node_t * (*add)(collection_t *, collection_node_t *);
    collection_node_t * (*del)(collection_t *, collection_node_t *);
    void (*clear)(collection_t *, collection_node_callback_t);
    collection_node_t * (*begin)(collection_t *);
    collection_node_t * (*end)(collection_t *);
};

#define collection_rem(collection)              ((collection)->func->rem(collection))
#define collection_add(collection, node)        ((collection)->func->add(collection, o))
#define collection_del(collection, node)        ((collection)->func->del(collection, o))
#define collection_clear(collection, callback)  ((collection)->func->clear(collection, callback))
#define collection_begin(collection)            ((collection)->func->begin(collection))
#define collection_end(collection)              ((collection)->func->end(collection))

struct collection_node {
    collection_node_func_t *    func;
    sync_t *                    sync;
    collection_t *              collection;
};

struct collection_node_func {
    collection_node_t * (*rem)(collection_node_t *);
};

#define collection_node_rem(node)               ((node) ? (node)->func->rem(node) : nil)

#endif // __SNORLAX__COLLECTION__H__
