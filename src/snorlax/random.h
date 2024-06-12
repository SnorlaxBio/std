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

extern void snorlax_random_init(void);
extern int snorlax_random_get(void);

#define snorlax_random_int32(max)       (snorlax_random_get() % max)

#endif // __SNORLAX__RANDOM__H__
