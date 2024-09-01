/**
 * @file        snorlax/hashtimer.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Sep 1, 2024
 */

#ifndef   __SNORLAX__HASHTIMER__H__
#define   __SNORLAX__HASHTIMER__H__

#include <hashtable.h>
#include <nanosecond.h>

struct hashtimer;
struct hashtimer_func;
struct hashtimer_bucket;
struct hashtimer_bucket_func;
struct hashtimer_list;
struct hashtimer_list_func;
struct hashtimer_node;
struct hashtimer_node_func;
struct hashtimer_node_key;

typedef struct hashtimer                    hashtimer_t;
typedef struct hashtimer_func               hashtimer_func_t;
typedef struct hashtimer_bucket             hashtimer_bucket_t;
typedef struct hashtimer_bucket_func        hashtimer_bucket_func_t;
typedef struct hashtimer_list               hashtimer_list_t;
typedef struct hashtimer_list_func          hashtimer_list_func_t;
typedef struct hashtimer_node               hashtimer_node_t;
typedef struct hashtimer_node_func          hashtimer_node_func_t;
typedef struct hashtimer_node_key           hashtimer_node_key_t;

typedef uint32_t (*hashtimer_hash_t)(const nanosecond_t *, uint64_t);
typedef uint32_t (*hashtimer_bucket_index_cal_func_t)(hashtimer_bucket_t *, uint32_t);


/**
 * 
 * @var hashtimer::size         uint64_t | The total time event count.
 * @var hashtimer::interval     uint64_t | The total count to be stored millisecond nodes.
 */
struct hashtimer {
    hashtimer_func_t *      func;
    sync_t *                sync;
    uint64_t                size;
    hashtimer_bucket_t *    front;
    hashtimer_bucket_t *    back;
    hash_t                  hash;
    uint64_t                moved;

    uint64_t                total;
};

struct hashtimer_func {
    hashtimer_t * (*rem)(hashtimer_t *);
    hashtimer_node_t * (*get)(hashtimer_t *, hashtimer_node_key_t *);
    hashtimer_node_t * (*set)(hashtimer_t *, hashtimer_node_t *);
    hashtimer_node_t * (*del)(hashtimer_t *, hashtimer_node_key_t *);
    int32_t (*expand)(hashtimer_t *);
    int32_t (*shrink)(hashtimer_t *);

    void (*check)(hashtimer_t *);
};

extern hashtimer_t * hashtimer_gen(void);

extern hashtimer_t * hashtimer_func_rem(hashtimer_t * collection);
extern hashtimer_node_t * hashtimer_func_get(hashtimer_t * collection, hashtimer_node_key_t * key);
extern hashtimer_node_t * hashtimer_func_set(hashtimer_t * collection, hashtimer_node_t * node);
extern hashtimer_node_t * hashtimer_func_del(hashtimer_t * collection, hashtimer_node_key_t * key);
extern int32_t hashtimer_func_expand(hashtimer_t * collection);
extern int32_t hashtimer_func_shrink(hashtimer_t * collection);

#define hashtimer_rem(collection)               ((collection)->func->rem(collection))
#define hashtimer_get(collection, key)          ((collection)->func->get(collection, key))
#define hashtimer_set(collection, node)         ((collection)->func->set(collection, node))
#define hashtimer_del(collection, key)          ((collection)->func->del(collection, key))
#define hashtimer_expand(collection)            ((collection)->func->expand(collection))
#define hashtimer_shrink(collection)            ((collection)->func->shrink(collection))

struct hashtimer_bucket {
    hashtimer_bucket_func_t *   func;
    sync_t *                    sync;
    uint64_t                    size;
    uint8_t                     exponent;
    hashtimer_list_t **         container;
    hashtable_t *               collection;

    uint64_t                    millisecond;
};

struct hashtimer_bucket_func {

};


#define hashtimer_bucket_rehash_move_max                    64
#define hashtimer_bucket_size_cal(bucket)                   (1llu << (bucket)->exponent)

extern hashtimer_bucket_t * hashtable_bucket_gen(uint8_t exponent, hashtimer_t * collection);

struct hashtimer_node {
    hashtimer_node_func_t * func;
    sync_t *                sync;
    hashtimer_list_t *      list;
    hashtimer_node_t *      prev;
    hashtimer_node_t *      next;
    hashtimer_node_key_t    key;
};

struct hashtimer_node_func {

};

struct hashtimer_node_key {
    nanosecond_t * value;
    uint64_t length;
};

#endif // __SNORLAX__HASHTIMER__H__
