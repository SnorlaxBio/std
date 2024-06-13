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

struct buffer;

typedef struct buffer buffer_t;

struct buffer {
    uint8_t * mem;
    uint64_t position;
    uint64_t size;
    uint64_t capacity;
};

extern buffer_t * buffer_gen(void);
extern buffer_t * buffer_rem(buffer_t * o);

extern void buffer_write(buffer_t * o, uint8_t * data, uint64_t n);
extern void buffer_reserve(buffer_t * o, uint64_t n);
extern void buffer_adjust(buffer_t * o);

#define buffer_front(o)     (o->mem ? &o->mem[o->position] : nil)
#define buffer_back(o)      (o->mem ? &o->mem[o->size] : nil)
#define buffer_len(o)       (o->size - o->position)
#define buffer_remain(o)    (o->capacity - o->size)

#endif // __SNORLAX__BUFFER__H__
