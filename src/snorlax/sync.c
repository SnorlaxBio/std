/**
 * @file        snorlax/sync.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       June 15, 2024
 */

#include "../snorlax.h"

#include "sync/posix/mutex.h"

/**
 * @fn          extern sync_t * sync_gen(void)
 * @brief       동기화 객체를 생성하는 함수
 * @details     
 * 
 * 
 * 
 * @return      | sync_t | 생성된 기본 동기화 객체 |
 * @todo        파라미터를 정의하고 다양한 동기화 객체를 지원해야 한다.
 *              semaphore, spinlock, read lock, write lock 등을 구현해야 한다.
 *              현재는 간단하게만 구현하였다.
 */
extern sync_t * sync_gen(void) {
    return (sync_t *) sync_posix_mutex_gen();
}
