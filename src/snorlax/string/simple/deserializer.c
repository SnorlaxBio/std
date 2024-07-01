/**
 * @file        snorlax/string/simple/deserializer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 30, 2024
 */

#include <string.h>

#include "deserializer.h"

extern int64_t string_simple_deserialize(buffer_t * in, buffer_t * out) {
#ifndef   RELEASE
    snorlaxdbg(in == nil, false, "critical", "");
    snorlaxdbg(out == nil, false, "critical", "");
    snorlaxdbg(in == out, false, "critical", "");
#endif // RELEASE
    printf("1\n");
    if(buffer_remain(in) == 0){
        uint64_t capacity = buffer_size_get(in) + 1;
        capacity = (capacity / 8 + 1)* 8;
        buffer_capacity_set(in, capacity);
    }
    printf("2\n");

    char * s = buffer_back(in);

    s[buffer_size_get(in)] = 0;

    s = buffer_front(in);

    printf("3\n");

    char * ret = index(s, '\n');

    if(ret != nil) {
        printf("4\n");
        uint64_t n = ret - s;

        if(buffer_remain(out) < n) {
            uint64_t capacity = buffer_size_get(out) + n + 1;
            capacity = (capacity / 8 + 1) * 8;
            buffer_capacity_set(out, capacity);
        }
        printf("5\n");

        memcpy(buffer_back(out), buffer_front(in), n);
        buffer_size_set(out, buffer_size_get(out) + n);
        buffer_position_set(in, buffer_position_get(in) + n);

        printf("6\n");

        s = buffer_back(out);
        s[buffer_size_get(out)] = 0;

        return n;
    }

    return 0;
}
