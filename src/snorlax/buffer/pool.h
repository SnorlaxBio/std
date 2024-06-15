/**
 * @file        snorlax/buffer/pool.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__BUFFER_POOL__H__
#define   __SNORLAX__BUFFER_POOL__H__

#include <snorlax.h>

struct buffer_pool_func;

typedef struct buffer_pool_func buffer_pool_func_t;

struct buffer_pool {
    buffer_pool_func_t * func;
    uint32_t size;
    uint32_t page;
    buffer_t ** container;
    uint32_t last;
};

#endif // __SNORLAX__BUFFER_POOL__H__
