/**
 * @file        snorlax/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#include <stdlib.h>
#include <string.h>

#include "buffer.h"

#define page        8

extern buffer_t * buffer_gen(void) {
    buffer_t * o = (buffer_t *) calloc(1, sizeof(buffer_t));

    return o;
}

extern buffer_t * buffer_rem(buffer_t * o) {
    if(o->mem) free(o->mem);
    free(o);
    return nil;
}

extern void buffer_write(buffer_t * o, uint8_t * data, uint64_t n) {
    buffer_reserve(o, n);

    memcpy(&o->mem[o->size], data, n);
}

extern void buffer_reserve(buffer_t * o, uint64_t n) {
    if(buffer_remain(o) < n) {
        n = ((o->size + n) / page + 1) * page;

        o->mem = (uint8_t *) (o->mem ? realloc(o->mem, n) : malloc(n));
        o->capacity = n;
    }
}

extern void buffer_adjust(buffer_t * o) {
    if(o->position == o->size) {
        o->position = 0;
        o->size = 0;
        o->capacity = page;
        o->mem = o->mem ? realloc(o->mem, o->capacity) : malloc(o->capacity);
    } else if(o->size - o->position <= o->position) {
        memcpy(o->mem, &o->mem[o->position], o->size - o->position);
        o->size = o->size - o->position;
        o->position = 0;
    }

    if(o->capacity - o->size > page) {
        o->capacity = ((o->size + page) / page + 1) * page;
        o->mem = (uint8_t *) realloc(o->mem, o->capacity);
    }
}

extern void buffer_position_set(buffer_t * o, uint64_t n) {
    o->position = n;
    buffer_adjust(o);
}
