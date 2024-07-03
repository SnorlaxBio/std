#ifndef   __SNORLAX__BUFFER_POOL__H__
#define   __SNORLAX__BUFFER_POOL__H__

#include <snorlax/buffer.h>

struct buffer_pool_func;

typedef struct buffer_pool_func buffer_pool_func_t;

struct buffer_pool {
    buffer_pool_func_t * func;
    sync_t * sync;
    uint64_t size;
    uint64_t page;
    buffer_t ** container;
    uint64_t last;
};

struct buffer_pool_func {
    buffer_pool_t * (*rem)(buffer_pool_t *);
    buffer_t * (*get)(buffer_pool_t *);
    buffer_t * (*rel)(buffer_pool_t *, buffer_t *);
};

extern buffer_pool_t * buffer_pool_gen(uint64_t size, uint64_t page);

#define buffer_pool_rem(pool)           (pool->func->rem(pool))
#define buffer_pool_get(pool)           (pool->func->get(pool))
#define buffer_pool_rel(pool, buffer)   (pool->func->rel(pool, buffer))

#endif // __SNORLAX__BUFFER_POOL__H__
