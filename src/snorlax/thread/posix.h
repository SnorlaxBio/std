/**
 * @file        snorlax/thread/posix.h
 * @brief
 * @details     
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 16, 2024
 * 
 * @todo        cancel 을 atomic 변수로 처리하자.
 */

#ifndef   __SNORLAX__THREAD_POSIX__H__
#define   __SNORLAX__THREAD_POSIX__H__

#include <pthread.h>

#include <snorlax.h>

struct thread_posix;
struct thread_posix_func;

typedef struct thread_posix thread_posix_t;
typedef struct thread_posix_func thread_posix_func_t;

typedef int (*thread_posix_routine_t)(thread_posix_t *);
typedef void (*thread_posix_cancel_t)(thread_posix_t *);

struct thread_posix { 
    thread_posix_func_t * func;
    sync_t * sync;

    thread_posix_cancel_t cancel;
    thread_posix_routine_t run;

    pthread_t handle;
};

struct thread_posix_func {
    thread_posix_t * (*rem)(thread_posix_t *);
    
    int32_t (*on)(thread_posix_t *);
    int32_t (*off)(thread_posix_t *, thread_posix_cancel_t);
    int32_t (*alive)(thread_posix_t *);

    thread_posix_cancel_t (*cancel_get)(___notnull thread_posix_t *);
    void (*cancel_set)(___notnull thread_posix_t *, thread_posix_cancel_t);
};

extern thread_posix_t * thread_posix_gen(thread_posix_routine_t run);

#endif // __SNORLAX__THREAD_POSIX__H__
