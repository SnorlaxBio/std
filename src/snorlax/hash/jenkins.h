/**
 * @file        snorlax/hash/jenkins.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 17, 2024
 * 
 * @copyright
 * 
 * Copyright (C) 2006. Bob Jenkins (bob_jenkins@burtleburtle.net)
 * 
 * https://burtleburtle.net/bob/hash/
 * 
 * These are the credits from Bob's sources:
 *
 * lookup3.c, by Bob Jenkins, May 2006, Public Domain.
 * 
 * These are functions for producing 32-bit hashes for hash table lookup.
 * hashword(), hashlittle(), hashlittle2(), hashbig(), mix(), and final()
 * are externally useful functions.  Routines to test the hash are included
 * if SELF_TEST is defined.  You can use this free for any purpose.  It's in
 * the public domain.  It has no warranty.
 *
 * Copyright (C) 2009-2010 Jozsef Kadlecsik (kadlec@netfilter.org)
 *
 * I've modified Bob's hash to be useful in the Linux kernel, and
 * any bugs present are my fault.
 * Jozsef
 */

#ifndef   __SNORLAX__HASH_JENKINS__H__
#define   __SNORLAX__HASH_JENKINS__H__

#include <snorlax.h>
#include <snorlax/bit.h>

extern uint32_t jenkins_hash(const uint8_t * values, uint64_t n);

#endif // __SNORLAX__HASH_JENKINS__H__