#ifndef   __SNORLAX__SYNC_POSIX__H__
#define   __SNORLAX__SYNC_POSIX__H__

#include <pthread.h>

#include "../../../snorlax.h"

struct sync_posix_mutex;
struct sync_posix_mutex_func;

typedef struct sync_posix_mutex sync_posix_mutex_t;
typedef struct sync_posix_mutex_func sync_posix_mutex_func_t;

struct sync_posix_mutex {
    sync_posix_mutex_func_t * func;
    
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

struct sync_posix_mutex_func {
    sync_posix_mutex_t * (*rem)(sync_posix_mutex_t *);

    int32_t (*lock)(sync_posix_mutex_t *);
    int32_t (*unlock)(sync_posix_mutex_t *);
    int32_t (*wait)(sync_posix_mutex_t *, int64_t, int64_t);
    int32_t (*wakeup)(sync_posix_mutex_t *, int32_t);
};

extern sync_posix_mutex_t * sync_posix_mutex_gen(void);

#endif // __SNORLAX__SYNC_POSIX__H__
