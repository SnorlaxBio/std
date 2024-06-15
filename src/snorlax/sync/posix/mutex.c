/**
 * @file        snorlax/sync/posix.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#include <stdlib.h>
#include <time.h>

#include "mutex.h"

static sync_posix_mutex_t * sync_posix_mutex_func_rem(sync_posix_mutex_t * sync);
static int32_t sync_posix_mutex_func_lock(sync_posix_mutex_t * sync);
static int32_t sync_posix_mutex_func_unlock(sync_posix_mutex_t * sync);
static int32_t sync_posix_mutex_func_wait(sync_posix_mutex_t * sync, int64_t second, int64_t nano);
static int32_t sync_posix_mutex_func_wakeup(sync_posix_mutex_t * sync, int32_t all);

static sync_posix_mutex_func_t func = {
    sync_posix_mutex_func_rem,
    sync_posix_mutex_func_lock,
    sync_posix_mutex_func_unlock,
    sync_posix_mutex_func_wait,
    sync_posix_mutex_func_wakeup
};

extern sync_posix_mutex_t * sync_posix_gen(void) {
    sync_posix_mutex_t * sync = (sync_posix_mutex_t *) calloc(1, sizeof(sync_posix_mutex_t));

    sync->func = &func;
    sync->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    sync->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    return sync;
}

static sync_posix_mutex_t * sync_posix_func_rem(sync_posix_mutex_t * sync) {
    pthread_mutex_destroy(&sync->mutex);
    pthread_cond_destroy(&sync->cond);

    free(sync);
    return nil;
}

static int32_t sync_posix_func_lock(sync_posix_mutex_t * sync) {
    int32_t err = pthread_mutex_lock(&sync->mutex);

    // TODO: ERROR HANDLING

    return err == success ? success : fail;
}
static int32_t sync_posix_func_unlock(sync_posix_mutex_t * sync) {
    int32_t err = pthread_mutex_unlock(&sync->mutex);

    // TODO: ERROR HANDLING

    return err == success ? success : fail;
}

static int32_t sync_posix_func_wait(sync_posix_mutex_t * sync, int64_t second, int64_t nano) {
    if(second == 0 && nano == 0) {
        int err = pthread_cond_wait(&sync->cond, &sync->mutex);

        // TODO: ERROR HANDLING

        return err == success ? success : fail;
    } else {
        struct timespec spec;

        clock_gettime(CLOCK_REALTIME, &spec);

        spec.tv_nsec = spec.tv_nsec + nano;
        spec.tv_sec = spec.tv_sec + second + (spec.tv_nsec / 1000000000L);
        spec.tv_nsec = spec.tv_nsec % 1000000000L;
        
        int err = pthread_cond_timedwait(&sync->cond, &sync->mutex, &spec);

        // TODO: ERROR HANDLING

        return err == success ? success : fail;
    }
}

static int32_t sync_posix_func_wakeup(sync_posix_mutex_t * sync, int32_t all){
    if(all) {
        int err = pthread_cond_broadcast(&sync->cond);
        
        // TODO: ERROR HANDLING

        return err == success ? success : fail;
    } else {
        int err = pthread_cond_signal(&sync->cond);

        // TODO: ERROR HANDLING

        return err == success ? success : fail;
    }
}
