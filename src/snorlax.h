/**
 * @file        snorlax.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__H__
#define   __SNORLAX__H__

#include <stdbool.h>
#include <stdint.h>

#define success                     0
#define fail                        (-1)
#define invalid                     (-1)
#define nil                         ((void *) 0)

#define addressof(o, offset)        (&o[offset])

#define int8of(o, offset)           (*((int8_t *) addressof(o, offset)))
#define int16of(o, offset)          (*((int16_t *) addressof(o, offset)))
#define int32of(o, offset)          (*((int32_t *) addressof(o, offset)))
#define int64of(o, offset)          (*((int64_t *) addressof(o, offset)))
#define uint8of(o, offset)          (*((uint8_t *) addressof(o, offset)))
#define uint16of(o, offset)         (*((uint16_t *) addressof(o, offset)))
#define uint32of(o, offset)         (*((uint32_t *) addressof(o, offset)))
#define uint64of(o, offset)         (*((uint64_t *) addressof(o, offset)))

typedef void *                      memory_t;

extern memory_t memory_gen(memory_t m, uint64_t n);
extern memory_t memory_rem(memory_t m);

struct object;
struct object_func;

typedef struct object object_t;
typedef struct object_func object_func_t;

struct object {
    object_func_t * func;
};

struct object_func {
    object_t * (*rem)(object_t *);
};

#define object_rem(o)               (o->func->rem(o))

union variable;

typedef union variable variable_t;

union variable {
    int8_t   i8;
    int16_t  i16;
    int32_t  i32;
    int64_t  i64;
    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    object_t o;
    memory_t p;
};

#endif // __SNORLAX__H__
