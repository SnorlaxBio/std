/**
 * @file        snorlax/memory.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include <stdlib.h>

#include "../snorlax.h"

extern memory_t memory_gen(memory_t m, uint64_t n) {
    if(n == 0) {
        if(m) free(m);

        return nil;
    }

    return m ? realloc(m, n) : malloc(n);
}

extern memory_t memory_rem(memory_t m) {
    if(m) {
        free(m);
    }

    return nil;
}
