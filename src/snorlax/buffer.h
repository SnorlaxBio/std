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
struct buffer_func;
struct buffer_pool;
struct buffer_pool_func;

typedef struct buffer buffer_t;
typedef struct buffer_func buffer_func_t;
typedef struct buffer_pool buffer_pool_t;
typedef struct buffer_pool_func buffer_pool_func_t;

struct buffer {
    buffer_func_t * func;
    sync_t *        sync;

    uint8_t *       mem;
    uint64_t        position;
    uint64_t        size;
    uint64_t        capacity;
};

struct buffer_func {
    buffer_t * (*rem)(buffer_t *);

    uint8_t * (*front)(buffer_t *);
    uint8_t * (*back)(buffer_t *);

    uint64_t (*position_get)(buffer_t *);
    void (*position_set)(buffer_t *, uint64_t);

    uint64_t (*size_get)(buffer_t *);
    void (*size_set)(buffer_t *, uint64_t);

    uint64_t (*capacity_get)(buffer_t *);
    void (*capacity_set)(buffer_t *, uint64_t);

    void (*reset)(buffer_t *, uint64_t);

    uint64_t (*remain)(buffer_t *);
    uint64_t (*length)(buffer_t *);
};

extern buffer_t * buffer_gen(uint64_t capacity);

#define buffer_rem(buffer)              ((buffer)->func->rem(buffer))

#define buffer_front(buffer)            ((buffer)->func->front(buffer))
#define buffer_back(buffer)             ((buffer)->func->back(buffer))

#define buffer_position_get(buffer)     ((buffer)->func->position_get(buffer))
#define buffer_position_set(buffer, v)  ((buffer)->func->position_set(buffer, v))

#define buffer_size_get(buffer)         ((buffer)->func->size_get(buffer))
#define buffer_size_set(buffer, v)      ((buffer)->func->size_set(buffer, v))

#define buffer_capacity_get(buffer)     ((buffer)->func->capacity_get(buffer))
#define buffer_capacity_set(buffer, v)  ((buffer)->func->capacity_set(buffer, v))

#define buffer_reset(buffer, capacity)  ((buffer)->func->reset(buffer, capacity))

#define buffer_remain(buffer)           ((buffer)->func->remain(buffer))
#define buffer_length(buffer)           ((buffer)->func->length(buffer))

#endif // __SNORLAX__BUFFER__H__
