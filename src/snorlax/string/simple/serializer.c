/**
 * @file        snorlax/string/simple/serializer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 30, 2024
 */

#include <string.h>

#include "serializer.h"

extern int64_t string_simple_serialize(buffer_t * in, buffer_t * out) {
#ifndef   RELEASE
    snorlaxdbg(in == nil, false, "critical", "");
    snorlaxdbg(out == nil, false, "critical", "");
    snorlaxdbg(in == out, false, "critical", "");
#endif // RELEASE

    if(buffer_remain(in) == 0) {
        uint64_t capacity = buffer_size_get(in) + 1;
        capacity = (capacity / 8 + 1) * 8;
        buffer_capacity_set(in, capacity);
    }

    char * s = buffer_back(in);
    s[buffer_size_get(in)] = 0;
    s = buffer_front(in);

    if(s) {
        char * ret = rindex(s, '\n');

        if(ret != nil) {
            int64_t n = ret - s + 1;

            if(buffer_remain(out) < n) {
                uint64_t capacity = buffer_size_get(out) + n + 1;
                capacity = ((capacity + 1) / 8 + 1) * 8;
                buffer_capacity_set(out, capacity);
            }

            memcpy(buffer_back(out), buffer_front(in), n);
            buffer_size_set(out, buffer_size_get(out) + n);
            buffer_position_set(in, buffer_position_get(in) + n);

            s = buffer_back(out);
            s[buffer_size_get(out)] = 0;

            return n;
        }
    }

    return 0;
}
