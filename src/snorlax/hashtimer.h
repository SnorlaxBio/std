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

___extend(hashtimer_t)
struct hashtimer {
    hashtimer_func_t * func;
    sync_t * sync;
    uint64_t size;
    hashtimer_bucket_t * front;
    hashtimer_bucket_t * back;
    hash_t hash;
    uint64_t moved;
    hashtimer_bucket_index_cal_func_t index_cal;
};

___extend(hashtimer_func_t)
struct hashtimer_func {
    hashtimer_t * (*rem)(hashtimer_t *);
    hashtable_node_t * (*get)(hashtimer_t *, hashtable_node_key_t *);
    hashtable_node_t * (*set)(hashtimer_t *, hashtable_node_t *);
    hashtable_node_t * (*del)(hashtimer_t *, hashtable_node_key_t *);
    int32_t (*expand)(hashtimer_t *);
    int32_t (*shrink)(hashtimer_t *);

    void (*check)(hashtimer_t *);
};

extern hashtimer_t * hashtimer_gen(void);


#endif // __SNORLAX__HASHTIMER__H__
