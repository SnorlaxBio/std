/**
 * @file        snorlax/thread.h
 * @brief
 * @details     스레드의 경우 동기화가 필요하다.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__THREAD__H__
#define   __SNORLAX__THREAD__H__

#include <snorlax.h>

struct thread;
struct thread_func;

typedef struct thread thread_t;
typedef struct thread_func thread_func_t;

typedef int (*thread_routine_t)(thread_t *);
typedef void (*thread_cancel_t)(thread_t *);

struct thread {
    thread_func_t * func;
    sync_t * sync;

    thread_cancel_t cancel;
    thread_routine_t run;
};

struct thread_func {
    thread_t * (*rem)(thread_t *);
    
    int32_t (*on)(thread_t *);
    int32_t (*off)(thread_t *, thread_cancel_t);
    int32_t (*alive)(thread_t *);
};

#endif // __SNORLAX__THREAD__H__
