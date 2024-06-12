/**
 * @file        snorlax/buffer.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#ifndef   __SNORLAX__BUFFER__H__
#define   __SNORLAX__BUFFER__H__

#include <snorlax.h>

struct buffer;

typedef struct buffer buffer_t;

struct buffer {
    uint8_t * mem;
    uint64_t position;
    uint64_t size;
    uint64_t capacity;
};

extern buffer_t * buffer_gen(void);

#endif // __SNORLAX__BUFFER__H__
