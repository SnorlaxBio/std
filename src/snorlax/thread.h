/**
 * @file        snorlax/thread.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__THREAD__H__
#define   __SNORLAX__THREAD__H__

struct thread;
struct thread_func;

typedef struct thread thread_t;
typedef struct thread_func thread_func_t;

typedef int (*thread_routine_t)(thread_t *);

struct thread {
    thread_func_t * func;
    thread_routine_t run;
};

struct thread_func {
    thread_t * (*rem)(thread_t *);
    int (*on)(thread_t *);
    int (*off)(thread_t *);
};

#endif // __SNORLAX__THREAD__H__
