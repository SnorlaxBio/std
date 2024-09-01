/**
 * @file        snorlax/hash.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 17, 2024
 */

#ifndef   __SNORLAX__HASH__H__
#define   __SNORLAX__HASH__H__

#include <snorlax/hash/jenkins.h>
#include <snorlax/hash/spooky.h>

#define default_hash            spooky_hash64
#define default_hash32          jenkins_hash
#define default_hash64          spooky_hash64

#endif // __SNORLAX__HASH__H__
