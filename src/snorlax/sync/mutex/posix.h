/**
 * @file        snorlax/sync/posix.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__SYNC_POSIX__H__
#define   __SNORLAX__SYNC_POSIX__H__

#include <pthread.h>

#include "../../../snorlax.h"

struct sync_posix;
struct sync_posix_func;

typedef struct sync_posix sync_posix_t;
typedef struct sync_posix_func sync_posix_func_t;

struct sync_posix {
    sync_posix_func_t * func;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

struct sync_posix_func {
    sync_posix_t * (*rem)(sync_posix_t *);

    int32_t (*lock)(sync_posix_t *);
    int32_t (*unlock)(sync_posix_t *);
    int32_t (*wait)(sync_posix_t *, int64_t, int64_t);
    int32_t (*wakeup)(sync_posix_t *, int32_t);
};

extern sync_posix_t * sync_mutex_posix_gen(void);

#endif // __SNORLAX__SYNC_POSIX__H__
