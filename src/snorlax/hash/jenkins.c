#include "jenkins.h"

#define jenkins_hash_initval        0xDEADBEEF

#define jenkins_hash_mix(first, second, third, n) do {      \
    first = first - third;                                  \
    first = first ^ rotate_left32(third, n);                \
    third = third + second;                                 \
} while(0)

#define jenkins_hash_mix_all(first, second, third) do {     \
    jenkins_hash_mix(first, second, third,  4);             \
    jenkins_hash_mix(second, third, first,  6);             \
    jenkins_hash_mix(third, first, second,  8);             \
    jenkins_hash_mix(first, second, third, 16);             \
    jenkins_hash_mix(second, third, first, 19);             \
    jenkins_hash_mix(third, first, second,  4);             \
} while(0)

#define jenkins_hash_final(first, second, n) do {           \
    second = second ^ first;                                \
    first = first - rotate_left32(second, n);               \
} while(0)

#define jenkins_hash_final_all(first, second, third) do {   \
    jenkins_hash_final(second, third, 14);                  \
    jenkins_hash_final(third, first, 11);                   \
    jenkins_hash_final(first, second, 25);                  \
    jenkins_hash_final(second, third, 16);                  \
    jenkins_hash_final(third, first, 4);                    \
    jenkins_hash_final(first, second, 14);                  \
    jenkins_hash_final(second, third, 24);                  \
} while(0)

struct __una_u32 { uint32_t x; } __packed;

static inline uint32_t get_unaligned_cpu32(const uint8_t * p) {
    struct __una_u32 * o = (struct __una_u32 *) p;

    return o->x;
}

extern uint32_t jenkins_hash(uint8_t * values, uint64_t n) {
    uint32_t first = 0;
    uint32_t second = 0;
    uint32_t third = 0;

    first = second = third = jenkins_hash_initval + n;

    while(n > 12) {
        first = first + get_unaligned_cpu32(values);
        second = second + get_unaligned_cpu32(values);
        third = third + get_unaligned_cpu32(values);

        jenkins_hash_mix_all(first, second, third);

        n = n - 12;
        values = values + 12;
    }

    switch(n) {
        case 12:    third = third   + (((uint32_t) values[11]) << 24);
        case 11:    third = third   + (((uint32_t) values[10]) << 16);
        case 10:    third = third   + (((uint32_t) values[ 9]) <<  8);
        case  9:    third = third   + (((uint32_t) values[ 8]));
        case  8:    second = second + (((uint32_t) values[ 7]) << 24);
        case  7:    second = second + (((uint32_t) values[ 6]) << 16);
        case  6:    second = second + (((uint32_t) values[ 5]) <<  8);
        case  5:    second = second + (((uint32_t) values[ 4]));
        case  4:    first = first   + (((uint32_t) values[ 3] << 24));
        case  3:    first = first   + (((uint32_t) values[ 2] << 16));
        case  2:    first = first   + (((uint32_t) values[ 1] <<  8));
        case  1:    first = first   + (((uint32_t) values[ 0]));
                    jenkins_hash_final_all(first, second, third);
                    break;
    }

    return third;
}
