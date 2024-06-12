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

#include <snorlax.h>

#include "random.h"

static uint32_t seed = invalid;

extern void snorlax_random_init(void) {
    seed = time(nil);
}

extern int snorlax_random_get(void) {
    if(seed == invalid) snorlax_random_init();
    
    return rand();
}