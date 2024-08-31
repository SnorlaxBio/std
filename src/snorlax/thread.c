/**
 * @file        snorlax/thread.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       June 17, 2024
 */

#include "thread.h"

#include "thread/posix.h"

extern thread_t * thread_gen(thread_routine_t run) {
    return (thread_t *) thread_posix_gen((thread_posix_routine_t) run);
}
