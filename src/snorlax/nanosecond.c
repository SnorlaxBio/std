/**
 * @file        snorlax/nanosecond.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       July 2, 2024
 */

#include <time.h>

#include "nanosecond.h"

extern void nanosecond_get(nanosecond_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    o->nano = spec.tv_nsec;
    o->second = spec.tv_sec;
}

extern void nanosecond_elapse(nanosecond_t * start, nanosecond_t * end, nanosecond_t * elapse) {
#ifndef   RELEASE
    snorlaxdbg(start == nil, false, "critical", "");
    snorlaxdbg(end == nil, false, "critical", "");
    snorlaxdbg(elapse == nil, false, "critical", "");
#endif // RELEASE 

    elapse->second = end->second - start->second;
    elapse->nano = end->nano - start->nano;
    if(elapse->nano < 0) {
        elapse->second = elapse->second - 1;
        elapse->nano = 1000000000 + elapse->nano;
    }
}