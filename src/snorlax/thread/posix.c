/**
 * @file        snorlax/thread/posix.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 16, 2024
 */

#include <signal.h>
#include <stdlib.h>

#include "posix.h"

static thread_posix_t * thread_posix_func_rem(thread_posix_t * o);
static int32_t thread_posix_func_on(thread_posix_t * o);
static int32_t thread_posix_func_off(thread_posix_t * o, thread_posix_cancel_t cancel);
static int32_t thread_posix_func_alive(thread_posix_t * o);
static thread_posix_cancel_t thread_posix_func_cancel_get(___notnull thread_posix_t * o);
static void thread_posix_func_cancel_set(___notnull thread_posix_t * o, thread_posix_cancel_t cancel);

static void * posix_start_routine(void * arg);
static void thread_posix_func_cancel(thread_posix_t * o);

static thread_posix_func_t func = {
    thread_posix_func_rem,
    thread_posix_func_on,
    thread_posix_func_off,
    thread_posix_func_alive,
    thread_posix_func_cancel_get,
    thread_posix_func_cancel_set
};

extern thread_posix_t * thread_posix_gen(thread_posix_routine_t run) {
    thread_posix_t * o = (thread_posix_t *) calloc(1, sizeof(thread_posix_t));

    o->func = &func;
    o->sync = sync_gen();
    o->run = run;

    o->handle = 0;

    return o;
}

static thread_posix_t * thread_posix_func_rem(thread_posix_t * o) {
    thread_posix_func_off(o, thread_posix_func_cancel);

    o->sync = sync_rem(o->sync);

    free(o);

    return nil;
}

static int32_t thread_posix_func_on(thread_posix_t * o) {
    object_lock((object_t *) o);
    int32_t ret = success;

    if(pthread_equal(o->handle, 0)) {
        o->cancel = nil;
        int err = pthread_create(&o->handle, nil, posix_start_routine, o);
        if(err) {
            // TODO: ERROR HANDLING
            o->handle = 0;
            ret = fail;
        }
    }

    object_unlock((object_t *) o);

    return ret;
}
static int32_t thread_posix_func_off(thread_posix_t * o, thread_posix_cancel_t cancel) {
    int32_t ret = success;
    object_lock((object_t *) o);

    if(!pthread_equal(o->handle, 0)) {
        if(o->cancel == nil) {
            o->cancel = (cancel ? cancel : thread_posix_func_cancel);
        }
        void * result = nil;
        int err = pthread_join(o->handle, &result);
        if(err) {
            // TODO: CHECK
            ret = fail;
        } else {
            o->handle = 0;
            o->cancel = nil;
        }
    }

    object_unlock((object_t *) o);

    return ret;
}

static int32_t thread_posix_func_alive(thread_posix_t * o) {
    return !pthread_equal(o->handle, 0) && pthread_kill(o->handle, 0) == 0;
}

static thread_posix_cancel_t thread_posix_func_cancel_get(___notnull thread_posix_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    return o->cancel;
}

static void thread_posix_func_cancel_set(___notnull thread_posix_t * o, thread_posix_cancel_t cancel) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    o->cancel = cancel;
}

static void thread_posix_func_cancel(thread_posix_t * o) {

}

static void * posix_start_routine(void * arg) {
    thread_posix_t * o = (thread_posix_t *) arg;

    if(o) o->run(o);
}