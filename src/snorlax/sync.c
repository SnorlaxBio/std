/**
 * @file        snorlax/sync.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include "../snorlax.h"

#include "sync/mutex/posix.h"

extern sync_t * sync_gen(void) {
    return (sync_t *) sync_mutex_posix_gen();
}
