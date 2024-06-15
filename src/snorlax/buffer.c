/**
 * @file        snorlax/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#include "buffer.h"

#include "buffer/pool.h"

static buffer_pool_t * pool = nil;

extern void snorlax_buffer_init(void) {
    if(pool == nil) pool = buffer_pool_gen(0lu, 8);
}

extern void snorlax_buffer_term(void) {
    if(pool != nil) pool = buffer_pool_rem(pool);
}

extern buffer_t * buffer_gen(buffer_pool_t * parent) {
    return buffer_pool_get(parent ? parent : pool);
}
