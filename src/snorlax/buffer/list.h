/**
 * @file        snorlax/buffer/list.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 15, 2024
 */

#ifndef   __SNORLAX__BUFFER_LIST__H__
#define   __SNORLAX__BUFFER_LIST__H__

#include <snorlax.h>

struct buffer_list;
struct buffer_list_func;

typedef struct buffer_list buffer_list_t;
typedef struct buffer_list_func buffer_list_func_t;

struct buffer_list {
    buffer_list_func_t * func;
    sync_t * sync;
};

struct buffer_list_func {
    buffer_list_t * (*rem)(buffer_list_t *);
    uint8_t * (*front)(buffer_list_t *);
    uint8_t * (*back)(buffer_list_t *);
    uint64_t (*position_get)(buffer_list_t *);
    void (*position_set)(buffer_list_t *, uint64_t);
    uint64_t (*size_get)(buffer_list_t *);
    void (*size_set)(buffer_list_t *, uint64_t);
    uint64_t (*capacity_get)(buffer_list_t *);
    void (*capacity_set)(buffer_list_t *, uint64_t);
    void (*reset)(buffer_list_t *, uint64_t);
    uint64_t (*remain)(buffer_list_t *);
    uint64_t (*length)(buffer_list_t *);
    void (*adjust)(buffer_list_t *, uint64_t);
    void (*write)(buffer_list_t *, const uint8_t *, uint64_t);
};

extern buffer_list_t * buffer_list_gen(void);

#define buffer_list_rem(buffer)                 ((buffer)->func->rem(buffer))
#define buffer_list_front(buffer)               ((buffer)->func->front(buffer))
#define buffer_list_back(buffer)                ((buffer)->func->back(buffer))
#define buffer_list_position_get(buffer)        ((buffer)->func->position_get(buffer))
#define buffer_list_position_set(buffer, v)     ((buffer)->func->position_set(buffer, v))
#define buffer_list_size_get(buffer)            ((buffer)->func->size_get(buffer))
#define buffer_list_size_set(buffer)            ((buffer)->func->size_set(buffer, v))
#define buffer_list_capacity_get(buffer)        ((buffer)->func->capacity_get(buffer))
#define buffer_list_capacity_set(buffer, v)     ((buffer)->func->capacity_set(buffer, v))
#define buffer_list_reset(buffer, n)            ((buffer)->func->reset(buffer, n))
#define buffer_list_remain(buffer)              ((buffer)->func->remain(buffer))
#define buffer_list_length(buffer)              ((buffer)->func->length(buffer))
#define buffer_list_adjust(buffer, n)           ((buffer)->func->adjust(buffer, n))
#define buffer_list_write(buffer, data, len)    ((buffer)->func->write(buffer, data, len))

#endif // __SNORLAX__BUFFER_LIST__H__
