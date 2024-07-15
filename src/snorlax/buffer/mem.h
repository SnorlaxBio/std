/**
 * @file        snorlax/buffer/mem.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 15, 2024
 */

#ifndef   __SNORLAX__BUFFER_MEM__H__
#define   __SNORLAX__BUFFER_MEM__H__

#include <snorlax.h>

struct buffer_mem;
struct buffer_mem_func;

typedef struct buffer_mem buffer_mem_t;
typedef struct buffer_mem_func buffer_mem_func_t;

struct buffer_mem {
    buffer_mem_func_t * func;
    sync_t * sync;

    uint8_t *       mem;
    uint64_t        position;
    uint64_t        size;
    uint64_t        capacity;
};

struct buffer_mem_func {
    buffer_mem_t * (*rem)(buffer_mem_t *);

    uint8_t * (*front)(buffer_mem_t *);
    uint8_t * (*back)(buffer_mem_t *);

    uint64_t (*position_get)(buffer_mem_t *);
    void (*position_set)(buffer_mem_t *, uint64_t);

    uint64_t (*size_get)(buffer_mem_t *);
    void (*size_set)(buffer_mem_t *, uint64_t);

    uint64_t (*capacity_get)(buffer_mem_t *);
    void (*capacity_set)(buffer_mem_t *, uint64_t);

    void (*reset)(buffer_mem_t *, uint64_t);

    uint64_t (*remain)(buffer_mem_t *);
    uint64_t (*length)(buffer_mem_t *);

    void (*adjust)(buffer_mem_t *, uint64_t);

    void (*write)(buffer_mem_t *, const char *, uint64_t);

    uint8_t * (*pop)(buffer_mem_t *, uint64_t, int32_t);
    uint8_t * (*rel)(buffer_mem_t *, uint64_t);
};

// extern buffer_mem_t * buffer_mem_gen(uint64_t capacity);

#endif // __SNORLAX__BUFFER_MEM__H__
