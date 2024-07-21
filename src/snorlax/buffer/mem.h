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
#include <snorlax/buffer.h>

struct buffer_mem;
struct buffer_mem_func;

typedef struct buffer_mem buffer_mem_t;
typedef struct buffer_mem_func buffer_mem_func_t;

struct buffer_mem {
    buffer_mem_func_t * func;
    sync_t *            sync;

    uint8_t *           mem;
    uint64_t            position;
    uint64_t            size;
    uint64_t            capacity;
    uint64_t            page;
};

struct buffer_mem_func {
    buffer_mem_t * (*rem)(buffer_mem_t *);

    int64_t (*in)(buffer_mem_t *, int);
    int64_t (*out)(buffer_mem_t *, int);
    int64_t (*inmsg)(buffer_mem_t *, int, struct msghdr *, int);
    int64_t (*outmsg)(buffer_mem_t *, int, struct msghdr *, int);
};

extern buffer_mem_t * buffer_mem_gen(uint64_t capacity, uint64_t page);

#define buffer_mem_rem(buffer)                      ((buffer)->func->rem(buffer))
#define buffer_mem_in(buffer, fd)                   ((buffer)->func->in(buffer, fd))
#define buffer_mem_out(buffer, fd)                  ((buffer)->func->out(buffer, fd))
#define buffer_mem_inmsg(buffer, fd, msg, flags)    ((buffer)->func->inmsg(buffer, fd, msg, flags))
#define buffer_mem_outmsg(buffer, fd, msg, flags)   ((buffer)->func->outmsg(buffer, fd, msg, flags))

// struct buffer_mem_func {
//     buffer_mem_t * (*rem)(buffer_mem_t *);

//     int64_t (*in)(buffer_mem_t *, buffer_func_t, ...);
//     int64_t (*out)(buffer_mem_t *, buffer_func_t, ...);

//     // uint8_t * (*front)(buffer_mem_t *);
//     // uint8_t * (*back)(buffer_mem_t *);

//     // uint64_t (*position_get)(buffer_mem_t *);
//     // void (*position_set)(buffer_mem_t *, uint64_t);

//     // uint64_t (*size_get)(buffer_mem_t *);
//     // void (*size_set)(buffer_mem_t *, uint64_t);

//     // uint64_t (*capacity_get)(buffer_mem_t *);
//     // void (*capacity_set)(buffer_mem_t *, uint64_t);

//     // void (*reset)(buffer_mem_t *, uint64_t);

//     // uint64_t (*remain)(buffer_mem_t *);
//     // uint64_t (*length)(buffer_mem_t *);

//     // void (*adjust)(buffer_mem_t *, uint64_t);

//     // void (*write)(buffer_mem_t *, const uint8_t *, uint64_t);
// };

// extern buffer_mem_t * buffer_mem_gen(uint64_t capacity);

// // #define buffer_mem_rem(buffer)              ((buffer)->func->rem(buffer))
// // #define buffer_mem_front(buffer)            ((buffer)->func->front(buffer))
// // #define buffer_mem_back(buffer)             ((buffer)->func->back(buffer))
// // #define buffer_mem_position_get(buffer)     ((buffer)->func->position_get(buffer))
// // #define buffer_mem_position_set(buffer, v)  ((buffer)->func->position_set(buffer, v))
// // #define buffer_mem_size_get(buffer)         ((buffer)->func->size_get(buffer))
// // #define buffer_mem_size_set(buffer, v)      ((buffer)->func->size_set(buffer, v))
// // #define buffer_mem_capacity_get(buffer)     ((buffer)->func->capacity_get(buffer))
// // #define buffer_mem_capacity_set(buffer, v)  ((buffer)->func->capacity_set(buffer, v))
// // #define buffer_mem_reset(buffer, n)         ((buffer)->func->reset(buffer, n))
// // #define buffer_mem_remain(buffer)           ((buffer)->func->remain(buffer))
// // #define buffer_mem_length(buffer)           ((buffer)->func->length(buffer))
// // #define buffer_mem_adjust(buffer, n)        ((buffer)->func->adjust(buffer, n))
// // #define buffer_mem_write(buffer, data, n)   ((buffer)->func->write(buffer, data, n))

#endif // __SNORLAX__BUFFER_MEM__H__
