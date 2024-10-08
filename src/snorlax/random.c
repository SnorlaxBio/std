/**
 * @file        snorlax/random.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       June 15, 2024
 */

#include <time.h>
#include <stdlib.h>

#include "random.h"

static uint32_t seed = invalid;

extern void snorlax_random_init(void) {
    seed = time(nil);
}

extern int random_get(void) {
    return rand();
}