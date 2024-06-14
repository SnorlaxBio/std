/**
 * @file        snorlax.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 11, 2024
 */

#include <stdlib.h>

#include "snorlax.h"

extern void * object_rem(object_t * o) {
    if(o) {
        free(o);
    }
    
    return nil;
}