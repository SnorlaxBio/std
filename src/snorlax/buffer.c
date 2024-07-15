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
#include "buffer/mem.h"

extern buffer_t * buffer_gen(uint64_t capacity) {
    return (buffer_t *) buffer_mem_gen(capacity);
}
