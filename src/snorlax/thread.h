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

typedef int32_t (*thread_routine_t)(thread_t *);
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

    thread_cancel_t (*cancel_get)(___notnull thread_t *);           // TODO: UPGRADE: 이름이 마음에 들지 않는다. 개인적으로 '_' 가 없었으면 한다. 즉, 하나의 단어
    void (*cancel_set)(___notnull thread_t *, thread_cancel_t);     // TODO: UPGRADE: 이름이 마음에 들지 않는다. 개인적으로 '_' 가 없었으면 한다. 즉, 하나의 단어
};

extern thread_t * thread_gen(thread_routine_t run);

#define thread_rem(thread)              ((thread) ? (thread)->func->rem(thread) : nil)
#define thread_on(thread)               ((thread) ? (thread)->func->on(thread) : fail)
#define thread_off(thread, cancel)      ((thread) ? (thread)->func->off(thread, cancel) : success)
#define thread_alive(thread)            ((thread) ? (thread)->func->alive(thread) : false)

#define thread_cancel_get(thread)       ((thread)->func->cancel_get(thread))
#define thread_cancel_set(thread, f)    ((thread)->func->cancel_set(thread, f))

#endif // __SNORLAX__THREAD__H__
