/**
 * @file        snorlax/buffer.h
 * @brief
 * @details
 * 
 * 필요할 때만 필요한 만큼 사용한다.
 * 적은 바이트에 대해서 메모리 할당이 일어나지 않도록 한다.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 13, 2024
 */

#ifndef   __SNORLAX__BUFFER__H__
#define   __SNORLAX__BUFFER__H__

#include <snorlax.h>

struct buffer_func;

typedef struct buffer_func buffer_func_t;

struct buffer {
    buffer_func_t * func;

    buffer_pool_t * pool;

    memory_t        mem;
    uint32_t        position;
    uint32_t        size;
    uint32_t        capacity;
};

struct buffer_func {
    buffer_t * (*rem)(buffer_t *);
};

extern void snorlax_buffer_init(void);
extern void snorlax_buffer_term(void);

#endif // __SNORLAX__BUFFER__H__
