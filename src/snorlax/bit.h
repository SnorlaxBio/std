/**
 * @file        snorlax/bit.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 17, 2024
 */

#ifndef   __SNORLAX__BIT__H__
#define   __SNORLAX__BIT__H__

#define rotate_left32(value, shift)         ((value << shift) | (value >> ((-shift) & 31)));

#endif // __SNORLAX__BIT__H__
