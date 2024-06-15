/**
 * @file        snorlax/random.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 12, 2024
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