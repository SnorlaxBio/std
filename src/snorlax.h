/**
 * @file        snorlax.h
 * @brief       
 * @details     
 * 
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__H__
#define   __SNORLAX__H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ___private
#define ___public
#define ___protected
#define ___expose
#define ___notnull
#define ___null
#define ___sync
#define ___notsync
#define ___reference
#define ___implement
#define ___pure
#define ___virtual
#define ___extend(o)

#define ___must                     true
#define ___should                   true
#define ___may                      false

#define ___notused(v)               ((void)(v))

typedef void *                      address_t;      // TODO: 이름이 마음에 들지 않는다.

#define success                     0
#define fail                        (-1)
#define invalid                     (-1)
#define nil                         ((void *) 0)
#define infinite                    (0xFFFFFFFF)

#define address_of(v)               (&(v))

#define int8_of(o)                  (*((int8_t *)(o)))
#define int16_of(o)                 (*((int16_t *)(o)))
#define int32_of(o)                 (*((int32_t *)(o)))
#define int64_of(o)                 (*((int64_t *)(o)))
#define uint8_of(o)                 (*((uint8_t *)(o)))
#define uint16_of(o)                (*((uint16_t *)(o)))
#define uint32_of(o)                (*((uint32_t *)(o)))
#define uint64_of(o)                (*((uint64_t *)(o)))

#define uint64_from_uint32x2(f, s)  (((uint64_t)((uint32_t) (f)) << 32LU) | ((uint64_t)((uint32_t) (s))))

extern address_t memory_gen(address_t m, uint64_t n);
extern address_t memory_rem(address_t m);
extern address_t memory_dup(address_t m, uint64_t n);

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

#define object_rem(o)                   ((o)->func->rem(o))

extern object_t * object_func_rem(object_t * o);

#define object_lock(o)                  (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->lock(((object_t *) o)->sync) : success)
#define object_unlock(o)                (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->unlock(((object_t *) o)->sync) : success)
#define object_wait(o, second, nano)    (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wait(((object_t *) o)->sync, second, nano) : success)
#define object_wakeup(o, all)           (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wakeup(((object_t *) o)->sync, all) : success)

union variable;

typedef union variable variable_t;

union variable {
    int8_t    i8;
    int16_t   i16;
    int32_t   i32;
    int64_t   i64;
    uint8_t   u8;
    uint16_t  u16;
    uint32_t  u32;
    uint64_t  u64;
    address_t o;            // TODO: CHANGE `void * p`
};

typedef void (*variable_callback_t)(variable_t);

#define variable_int32(v)       ((variable_t) { .i32 = v })
#define variable_uint32(v)      ((variable_t) { .u32 = v })
#define variable_uint64(v)      ((variable_t) { .u64 = v })
#define variable_int64(v)       ((variable_t) { .i64 = v })

#define snorlaxdbg(expression, force, type, format, ...) do {           \
    if(expression) {                                                    \
        printf("[%s|%s:%d|%s] ", type, __FILE__, __LINE__, __func__);   \
        printf(format " ", ##__VA_ARGS__);                              \
        printf("=> [critical] ");                                       \
        printf(#expression);                                            \
        printf("\n");                                                   \
        abort();                                                        \
    } else if(force) {                                                  \
        printf("[%s|%s:%d|%s] ", type, __FILE__, __LINE__, __func__);   \
        printf(format "\n", ##__VA_ARGS__);                             \
    }                                                                   \
} while(0)

extern void hexdump(FILE * stream, const uint8_t * data, uint64_t len);

#endif // __SNORLAX__H__
