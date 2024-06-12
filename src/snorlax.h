/**
 * @file        snorlax.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 11, 2024
 */

#ifndef   __SNORLAX__H__
#define   __SNORLAX__H__

#include <stdbool.h>
#include <stdint.h>

#define success                     0
#define fail                        (-1)
#define invalid                     (-1)
#define nil                         ((void *) 0)

#define addressof(o, offset)        (&o[offset])

#define uint32of(o, offset)         (*((uint32_t *) addressof(o, offset)))

typedef void *                      object_t;

#endif // __SNORLAX__H__
