/**
 * @file        snorlax/random.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 12, 2024
 */

#ifndef   __SNORLAX__RANDOM__H__
#define   __SNORLAX__RANDOM__H__

#include <snorlax.h>

extern void snorlax_random_init(void);

extern int32_t random_get(void);

#define random_int32(max)       (random_get() % max)

#endif // __SNORLAX__RANDOM__H__
