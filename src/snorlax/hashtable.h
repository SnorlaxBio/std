/**
 * @file        snorlax/hashtable.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 8, 2024
 */

#ifndef   __SNORLAX__HASHTABLE__H__
#define   __SNORLAX__HASHTABLE__H__

#include <snorlax.h>

struct hashtable;
struct hashtable_func;
struct hashtable_bucket;
struct hashtable_bucket_func;
struct hashtable_list;
struct hashtable_list_func;
struct hashtable_node;
struct hashtable_node_func;
struct hashtable_node_key;

typedef struct hashtable hashtable_t;
typedef struct hashtable_func hashtable_func_t;
typedef struct hashtable_bucket hashtable_bucket_t;
typedef struct hashtable_bucket_func hashtable_bucket_func_t;
typedef struct hashtable_list hashtable_list_t;
typedef struct hashtable_list_func hashtable_list_func_t;
typedef struct hashtable_node hashtable_node_t;
typedef struct hashtable_node_func hashtable_node_func_t;
typedef struct hashtable_node_key hashtable_node_key_t;

typedef uint64_t (*hash_t)(const uint8_t *, uint64_t);
typedef uint64_t (*hashtable_bucket_index_cal_func_t)(hashtable_bucket_t *, uint64_t);

struct hashtable {
    hashtable_func_t * func;
    sync_t * sync;
    uint64_t size;
    hashtable_bucket_t * front;
    hashtable_bucket_t * back;
    hash_t hash;

    uint64_t moved;
    hashtable_bucket_index_cal_func_t index_cal;
};

struct hashtable_func {
    hashtable_t * (*rem)(hashtable_t *);
    hashtable_node_t * (*get)(hashtable_t *, hashtable_node_key_t *);
    hashtable_node_t * (*set)(hashtable_t *, hashtable_node_t *);
    hashtable_node_t * (*del)(hashtable_t *, hashtable_node_key_t *);
    int32_t (*expand)(hashtable_t *);
    int32_t (*shrink)(hashtable_t *);
};

extern hashtable_t * hashtable_gen(hash_t hash, hashtable_bucket_index_cal_func_t index_cal);

extern hashtable_t * hashtable_func_rem(hashtable_t * collection);
extern hashtable_node_t * hashtable_func_get(hashtable_t * collection, hashtable_node_key_t * key);
extern hashtable_node_t * hashtable_func_set(hashtable_t * collection, hashtable_node_t * value);
extern hashtable_node_t * hashtable_func_del(hashtable_t * collection, hashtable_node_key_t * key);
extern int32_t hashtable_func_expand(hashtable_t * collection);
extern int32_t hashtable_func_shrink(hashtable_t * collection);

#define hashtable_rem(collection)                           ((collection)->func->rem(collection))
#define hashtable_get(collection, key)                      ((collection)->func->get(collection, key))
#define hashtable_set(collection, node)                     ((collection)->func->set(collection, node))
#define hashtable_del(collection, key)                      ((collection)->func->del(collection, key))
#define hashtable_expand(collection)                        ((collection)->func->expand(collection))
#define hashtable_shrink(collection)                        ((collection)->func->shrink(collection))

#define hashtable_bucket_exponent_initial                   2
#define hashtable_bucket_rehash_move_max                    64

#define hashtable_bucket_size_cal(bucket)                   (1 << (bucket)->exponent)
#define hashtable_bucket_size_mask_cal(bucket)              (hashtable_bucket_size_cal(bucket) - 1)
#define hashtable_bucket_rehash_threshold_cal(bucket)       (hashtable_bucket_size_cal(bucket) * 2)

struct hashtable_bucket {
    hashtable_bucket_func_t * func;
    sync_t * sync;
    uint64_t size;
    uint8_t exponent;
    hashtable_list_t ** container;
    hashtable_t * collection;

    hashtable_bucket_index_cal_func_t index_cal;
};

struct hashtable_bucket_func {
    hashtable_bucket_t * (*rem)(hashtable_bucket_t *);
    hashtable_node_t * (*get)(hashtable_bucket_t *, hashtable_node_key_t *, uint64_t);
    hashtable_node_t * (*set)(hashtable_bucket_t *, hashtable_node_key_t *, uint64_t, hashtable_node_t *);
    hashtable_node_t * (*del)(hashtable_bucket_t *, hashtable_node_key_t *, uint64_t);
    hashtable_list_t * (*list)(hashtable_bucket_t *, uint64_t, int32_t);
    uint64_t (*move)(hashtable_bucket_t *, hashtable_bucket_t *, uint64_t, hash_t, uint64_t);
};

extern hashtable_bucket_t * hashtable_bucket_gen(uint8_t exponent, hashtable_t * collection, hashtable_bucket_index_cal_func_t index_cal);

extern hashtable_bucket_t * hashtable_bucket_func_rem(hashtable_bucket_t * bucket);
extern hashtable_node_t * hashtable_bucket_func_get(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v);
extern hashtable_node_t * hashtable_bucket_func_set(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v, hashtable_node_t * node);
extern hashtable_node_t * hashtable_bucket_func_del(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v);
extern hashtable_list_t * hashtable_bucket_func_list(hashtable_bucket_t * bucket, uint64_t v, int32_t gen);
extern uint64_t hashtable_bucket_func_move(hashtable_bucket_t * bucket, hashtable_bucket_t * back, uint64_t threshold, hash_t hash, uint64_t last);

extern uint64_t hashtable_bucket_func_index_cal(hashtable_bucket_t * bucket, uint64_t v);

#define hashtable_bucket_rem(bucket)                                    ((bucket)->func->rem(bucket))
#define hashtable_bucket_get(bucket, key, v)                            ((bucket)->func->get(bucket, key, v))
#define hashtable_bucket_set(bucket, key, v, node)                      ((bucket)->func->set(bucket, key, v, node))
#define hashtable_bucket_del(bucket, key, v)                            ((bucket)->func->del(bucket, key, v))
#define hashtable_bucket_list(bucket, v, gen)                           ((bucket)->func->list(bucket, v, gen))
#define hashtable_bucket_move(bucket, back, threshold, hash, last)      ((bucket)->func->move(bucket, back, threshold, hash, last))

#define hashtable_bucket_index_cal(bucket, v)                           ((bucket)->index_cal(bucket, v))

#define hashtable_bucket_size_get(bucket)                               ((bucket)->size)
#define hashtable_bucket_exponent_get(bucket)                           ((bucket)->exponent)

struct hashtable_list {
    hashtable_list_func_t * func;
    sync_t * sync;
    uint64_t size;
    hashtable_node_t * head;
    hashtable_node_t * tail;

    hashtable_bucket_t * bucket;
};

struct hashtable_list_func {
    hashtable_list_t * (*rem)(hashtable_list_t *);
    hashtable_node_t * (*get)(hashtable_list_t *, hashtable_node_key_t *);
    hashtable_node_t * (*del)(hashtable_list_t *, hashtable_node_key_t *);
    void (*push)(hashtable_list_t *, hashtable_node_t *);
    void (*replace)(hashtable_list_t *, hashtable_node_t *, hashtable_node_t *);
};

extern hashtable_list_t * hashtable_list_gen(hashtable_bucket_t * bucket);

extern hashtable_list_t * hashtable_list_func_rem(hashtable_list_t * list);
extern hashtable_node_t * hashtable_list_func_get(hashtable_list_t * list, hashtable_node_key_t * key);
extern hashtable_node_t * hashtable_list_func_del(hashtable_list_t * list, hashtable_node_key_t * key);
extern void hashtable_list_func_push(hashtable_list_t * list, hashtable_node_t * node);
extern void hashtable_list_func_replace(hashtable_list_t * list, hashtable_node_t * original, hashtable_node_t * node);

#define hashtable_list_rem(collection)                          ((collection)->func->rem(collection))
#define hashtable_list_get(collection, key)                     ((collection)->func->get(collection, key))
#define hashtable_list_del(collection, key)                     ((collection)->func->del(collection, key))
#define hashtable_list_push(collection, node)                   ((collection)->func->push(collection, node))
#define hashtable_list_replace(collection, original, node)      ((collection)->func->replace(collection, original, node))

#define hashtable_list_begin(collection)                        ((collection)->head)

struct hashtable_node_key {
    uint8_t * value;
    uint64_t length;
};

struct hashtable_node {
    hashtable_node_func_t * func;
    sync_t * sync;
    hashtable_list_t * list;
    hashtable_node_t * prev;
    hashtable_node_t * next;
    hashtable_node_key_t key;
};

struct hashtable_node_func {
    hashtable_node_t * (*rem)(hashtable_node_t *);
    hashtable_node_t * (*del)(hashtable_node_t *);
};

extern hashtable_node_t * hashtable_node_func_rem(hashtable_node_t * node);
extern hashtable_node_t * hashtable_node_func_del(hashtable_node_t * node);

#define hashtable_node_rem(node)                    ((node)->func->rem(node))
#define hashtable_node_del(node)                    ((node)->func->del(node))

#define hashtable_node_next(node)                   ((node)->next)

#endif // __SNORLAX__HASHTABLE__H__
