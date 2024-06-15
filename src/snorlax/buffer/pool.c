/**
 * @file        snorlax/buffer/pool.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include "pool.h"

extern buffer_pool_t * buffer_pool_gen(uint32_t size, uint32_t page) {
    buffer_pool_t * pool = (buffer_pool_t *) calloc(1, sizeof(buffer_pool_t));

    pool->size = size;
    pool->page = page;

    if(pool->size > 0) {
        pool->container = (buffer_t **) calloc(size, sizeof(buffer_t *));
        for(uint32_t i = 0; i < pool->size; i++) {
            pool->container[i] = buffer_gen(pool->page);
        }
        pool->last = pool->size;
    }

    return pool;
}

extern buffer_t * buffer_pool_get(buffer_pool_t * pool) {
    if(pool->last) {
        pool->last = pool->last - 1;

        return pool->container[pool->last];
    }

    return buffer_gen(pool->page);
}
