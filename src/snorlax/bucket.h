/**
 * @file        snorlax/bucket.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 11, 2024
 */

#ifndef   __SNORLAX__BUCKET__H__
#define   __SNORLAX__BUCKET__H__

#include <stdint.h>

#include <snorlax.h>

struct bucket;

typedef struct bucket bucket_t;

typedef void (*bucket_get_t)(bucket_t);

struct bucket {
    int8_t   i8;
    int16_t  i16;
    int32_t  i32;
    int64_t  i64;
    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    object_t o;
};

#define bucket_int32(v)     ((bucket_t) { .i32 = v })

#endif // __SNORLAX__BUCKET__H__
