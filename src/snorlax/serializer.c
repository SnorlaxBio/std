/**
 * @file        snorlax/serializer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 30, 2024
 */


#include <string.h>

#include "serializer.h"

extern int64_t serialize(buffer_t * in, buffer_t * out) {
#ifndef   RELEASE
    snorlaxdbg(in == nil, false, "critical", "");
    snorlaxdbg(out == nil, false, "critical", "");
    snorlaxdbg(in == out, false, "critical", "");
#endif // RELEASE

    if(buffer_length(in) > 0) {
        int64_t n = buffer_length(in);

        if(buffer_remain(out) < n) buffer_capacity_set(out, buffer_size_get(out) + n);

        memcpy(buffer_back(out), buffer_front(in), n);

        buffer_position_set(in, buffer_position_get(in) + n);
        buffer_size_set(out, buffer_size_get(out) + n);

        return n;
    }
    

    return 0;
}
