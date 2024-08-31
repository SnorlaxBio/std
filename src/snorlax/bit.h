/**
 * @file        snorlax/bit.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 17, 2024
 */

#ifndef   __SNORLAX__BIT__H__
#define   __SNORLAX__BIT__H__

#define rotate_left32(value, shift)         ((value << shift) | (value >> ((-shift) & 31)));

/**
 * (x + y > 0xFFFFFFFFu) => x > 0xFFFFFFFFu - y
 */
#define overflow_u32_check(x, y)            ((x) > (0xFFFFFFFFu - (y)))

#endif // __SNORLAX__BIT__H__
