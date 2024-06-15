/**
 * @file        snorlax.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include "snorlax.h"

extern sync_t * sync_gen(void) {
    sync_t * sync = sync_posix_gen();

    return sync;
}