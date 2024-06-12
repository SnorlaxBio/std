/**
 * @file        snorlax/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#include "buffer.h"

extern buffer_t * buffer_gen(void) {
    buffer_t * o = (buffer_t *) calloc(1, sizeof(buffer_t));

    o->mem = malloc(4096);
    o->capacity = 4096;

    return o;
}