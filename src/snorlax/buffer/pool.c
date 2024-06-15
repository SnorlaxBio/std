/**
 * @file        snorlax/buffer/pool.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include <stdlib.h>

#include "pool.h"

static buffer_pool_t * buffer_pool_func_rem(buffer_pool_t * pool);
static buffer_t * buffer_pool_func_get(buffer_pool_t * pool);
static buffer_t * buffer_pool_func_rel(buffer_pool_t * pool, buffer_t * buffer);

static buffer_pool_func_t func = {
    buffer_pool_func_rem,
    buffer_pool_func_get,
    buffer_pool_func_rel
};

extern buffer_pool_t * buffer_pool_gen(uint32_t size, uint32_t page) {
    buffer_pool_t * pool = (buffer_pool_t *) calloc(1, sizeof(buffer_pool_t));

    pool->func = &func;
    pool->size = size;
    pool->page = page;
    if(pool->size > 0) {
        pool->container = (buffer_t **) malloc(pool->size * sizeof(buffer_t *));
        for(uint32_t i = 0; i < pool->size; i++) {
            pool->container[i] = buffer_gen(pool->page);
        }
    }
    pool->last = pool->size;

    return pool;
}

static buffer_pool_t * buffer_pool_func_rem(buffer_pool_t * pool) {
    if(pool) {
        for(uint32_t i = 0; i < pool->last; i++) {
            pool->container[i] = buffer_rem(pool->container[i]);
        }
        free(pool->container);
        free(pool);
    }
    return nil;
}

static buffer_t * buffer_pool_func_get(buffer_pool_t * pool) {
    if(pool->last) {
        pool->last = pool->last - 1;
        buffer_t * buffer = pool->container[pool->last];

        pool->container[pool->last] = nil;

        return buffer;
    }

    return buffer_gen(pool->page);
}

static buffer_t * buffer_pool_func_rel(buffer_pool_t * pool, buffer_t * buffer) {
    if(pool->last < pool->size) {
        buffer_reset(buffer, pool->page);

        pool->container[pool->last] = buffer;
        pool->last = pool->last + 1;
    } else {
        buffer_rem(buffer);
    }

    return nil;
}