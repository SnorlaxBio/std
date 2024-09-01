/**
 * @file        snorlax/hash/spooky.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Sep 1, 2024
 * 
 * @see         [Jenkins Hash Function](https://en.wikipedia.org/wiki/Jenkins_hash_function)
 */

#ifndef   __SNORLAX__HASH_SPOOKY__H__
#define   __SNORLAX__HASH_SPOOKY__H__

#include <snorlax.h>
#include <snorlax/bit.h>

extern void spooky_hash128(const void * message, uint64_t n, uint64_t * first, uint64_t * second);
extern uint64_t spooky_hash64(const void * message, uint64_t n, uint64_t seed);
extern uint32_t spooky_hash32(const void * message, uint64_t n, uint32_t seed);

#endif // __SNORLAX__HASH_SPOOKY__H__
