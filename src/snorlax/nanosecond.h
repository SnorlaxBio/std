/**
 * @file        snorlax/nanosecond.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 2, 2024
 */

#ifndef   __SNORLAX__NANOSECOND__H__
#define   __SNORLAX__NANOSECOND__H__

#include <snorlax.h>

struct nanosecond;

typedef struct nanosecond nanosecond_t;

struct nanosecond {
    int64_t second;
    int64_t nano;
};

extern void nanosecond_get(nanosecond_t * o);
extern void nanosecond_elapse(nanosecond_t * start, nanosecond_t * end, nanosecond_t * elapse);

#endif // __SNORLAX__NANOSECOND__H__
