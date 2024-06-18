/**
 * @file        snorlax.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 * 
 * EXPOSE
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

struct sync;
struct sync_func;

typedef struct sync sync_t;
typedef struct sync_func sync_func_t;

struct sync {
    sync_func_t * func;
};

struct sync_func {
    sync_t * (*rem)(sync_t *);

    int32_t (*lock)(sync_t *);
    int32_t (*unlock)(sync_t *);
    int32_t (*wait)(sync_t *, int64_t, int64_t);
    int32_t (*wakeup)(sync_t *, int32_t);
};

extern sync_t * sync_gen(void);
#define sync_rem(sync)                  (sync ? sync->func->rem(sync) : nil)
#define sync_lock(sync)                 (sync ? sync->func->lock(sync) : success)
#define sync_unlock(sync)               (sync ? sync->func->unlock(sync) : success)
#define sync_wait(sync, second, nano)   (sync ? sync->func->wait(sync, second, nano) : success)
#define sync_wakeup(sync, all)          (sync ? sync->func->wakeup(sync, all) : success)

#define sync_on(o) do {             \
    if(o->sync == nil) {            \
        o->sync = sync_gen();       \
    }                               \
} while(0)

#define sync_off(o) do {            \
    o->sync = sync_rem(o->sync);    \
} while(0)

struct object;
struct object_func;

typedef struct object object_t;
typedef struct object_func object_func_t;

struct object {
    object_func_t * func;
    sync_t * sync;
};

struct object_func {
    object_t * (*rem)(object_t *);
};

#define object_rem(o)                   (o->func->rem(o))

#define object_lock(o)                  (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->lock(((object_t *) o)->sync) : success)
#define object_unlock(o)                (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->unlock(((object_t *) o)->sync) : success)

#define object_wait(o, second, nano)    (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wait(((object_t *) o)->sync, second, nano) : success)
#define object_wakeup(o, all)           (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wakeup(((object_t *) o)->sync, all) : success)

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

typedef void (*variable_get_t)(variable_t);

#define variable_int32(v)       ((variable_t) { .i32 = v })

#endif // __SNORLAX__H__
