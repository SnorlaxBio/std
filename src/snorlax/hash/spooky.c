/**
 * @file        snorlax/hash/spooky.c
 * @brief
 * @details     
 * 
 * ## SpookyHash
 * 
 * In 2011 Jenkins released a new 128 bit hash function called SpookyHash. <sub>[Jenkins, Bob (November 3, 2013). "A hash function for hash Table lookup". Retrieved February 9, 2018](https://www.burtleburtle.net/bob/hash/doobs.html)</sub>
 * SpookyHash is significantly faster than lookup3.
 * 
 * Example of V2 (little-endian x64):
 * 
 * The short method for less than 192 bytes (43 bytes):
 * 
 * ```
 * Hash128("The quick brown for jumps over the lazy dog")
 * 2b12e846aa0693c71d367e742407341b
 * ```
 * 
 * The standard method for more than 191 bytes (219 bytes):
 * 
 * ```
 * Hash128("The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog")
 * f1b71c6ac5af39e7b69363a60dd29c49
 * ```
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Sep 1, 2024
 */
#include <memory.h>

#include "spooky.h"

#define ALLOW_UNALIGNED_READS               1

/**
 * The goas is for each bit of the input to expand into 128 bits of apparent entropy before it is fully overwritten.
 * n trials both set and cleared at least m bits of h0, h1, h2, h3
 * 
 * - n: 2,  m:  29
 * - n: 3,  m:  46
 * - n: 4,  m:  57
 * - n: 5,  m: 107
 * - n: 6,  m: 146
 * - n: 27, m: 152
 * 
 * when run forwards or backwards for all 1 bit and 2 bit diffs with idffs defined by either xor or subtraction
 * with a base of all zeros plus a counter, or plus another bit, or random.
 */
#define spooky_short_mix(h0, h1, h2, h3) do {           \
    h2 = rotate_left64(h2,50);  h2 += h3;  h0 ^= h2;    \
    h3 = rotate_left64(h3,52);  h3 += h0;  h1 ^= h3;    \
    h0 = rotate_left64(h0,30);  h0 += h1;  h2 ^= h0;    \
    h1 = rotate_left64(h1,41);  h1 += h2;  h3 ^= h1;    \
    h2 = rotate_left64(h2,54);  h2 += h3;  h0 ^= h2;    \
    h3 = rotate_left64(h3,48);  h3 += h0;  h1 ^= h3;    \
    h0 = rotate_left64(h0,38);  h0 += h1;  h2 ^= h0;    \
    h1 = rotate_left64(h1,37);  h1 += h2;  h3 ^= h1;    \
    h2 = rotate_left64(h2,62);  h2 += h3;  h0 ^= h2;    \
    h3 = rotate_left64(h3,34);  h3 += h0;  h1 ^= h3;    \
    h0 = rotate_left64(h0,5);   h0 += h1;  h2 ^= h0;    \
    h1 = rotate_left64(h1,36);  h1 += h2;  h3 ^= h1;    \
} while(0)

/**
 * Mix all 4 inputs together so that h0, h1 are a hash of them all.
 * 
 * For two inputs differing in just the input bits
 * Where "differ" means xor or subtraction
 * And the base value is random, or a counting value starting at that bit
 * The final result will have each bit of h9, h1 flip
 * For every input bit,
 * with probability 50+- .3% (it is probably better than that)
 * For every pair of input bits,
 * with probability 50 +- .75% (the worst case is approximately that)
 */
#define spooky_short_end(h0, h1, h2, h3) do {               \
    h3 ^= h2;  h2 = rotate_left64(h2,15);  h3 += h2;        \
    h0 ^= h3;  h3 = rotate_left64(h3,52);  h0 += h3;        \
    h1 ^= h0;  h0 = rotate_left64(h0,26);  h1 += h0;        \
    h2 ^= h1;  h1 = rotate_left64(h1,51);  h2 += h1;        \
    h3 ^= h2;  h2 = rotate_left64(h2,28);  h3 += h2;        \
    h0 ^= h3;  h3 = rotate_left64(h3,9);   h0 += h3;        \
    h1 ^= h0;  h0 = rotate_left64(h0,47);  h1 += h0;        \
    h2 ^= h1;  h1 = rotate_left64(h1,54);  h2 += h1;        \
    h3 ^= h2;  h2 = rotate_left64(h2,32);  h3 += h2;        \
    h0 ^= h3;  h3 = rotate_left64(h3,25);  h0 += h3;        \
    h1 ^= h0;  h0 = rotate_left64(h0,63);  h1 += h0;        \
} while(0)

#define spooky_mix(data, s) do {                                                                            \
    s[ 0] += data[ 0]; s[ 2] ^= s[10]; s[11] ^= s[ 0]; s[ 0] = rotate_left64(s[ 0],11); s[11] += s[ 1];     \
    s[ 1] += data[ 1]; s[ 3] ^= s[11]; s[ 0] ^= s[ 1]; s[ 1] = rotate_left64(s[ 1],32); s[ 0] += s[ 2];     \
    s[ 2] += data[ 2]; s[ 4] ^= s[ 0]; s[ 1] ^= s[ 2]; s[ 2] = rotate_left64(s[ 2],43); s[ 1] += s[ 3];     \
    s[ 3] += data[ 3]; s[ 5] ^= s[ 1]; s[ 2] ^= s[ 3]; s[ 3] = rotate_left64(s[ 3],31); s[ 2] += s[ 4];     \
    s[ 4] += data[ 4]; s[ 6] ^= s[ 2]; s[ 3] ^= s[ 4]; s[ 4] = rotate_left64(s[ 4],17); s[ 3] += s[ 5];     \
    s[ 5] += data[ 5]; s[ 7] ^= s[ 3]; s[ 4] ^= s[ 5]; s[ 5] = rotate_left64(s[ 5],28); s[ 4] += s[ 6];     \
    s[ 6] += data[ 6]; s[ 8] ^= s[ 4]; s[ 5] ^= s[ 6]; s[ 6] = rotate_left64(s[ 6],39); s[ 5] += s[ 7];     \
    s[ 7] += data[ 7]; s[ 9] ^= s[ 5]; s[ 6] ^= s[ 7]; s[ 7] = rotate_left64(s[ 7],57); s[ 6] += s[ 8];     \
    s[ 8] += data[ 8]; s[10] ^= s[ 6]; s[ 7] ^= s[ 8]; s[ 8] = rotate_left64(s[ 8],55); s[ 7] += s[ 9];     \
    s[ 9] += data[ 9]; s[11] ^= s[ 7]; s[ 8] ^= s[ 9]; s[ 9] = rotate_left64(s[ 9],54); s[ 8] += s[10];     \
    s[10] += data[10]; s[ 0] ^= s[ 8]; s[ 9] ^= s[10]; s[10] = rotate_left64(s[10],22); s[ 9] += s[11];     \
    s[11] += data[11]; s[ 1] ^= s[ 9]; s[10] ^= s[11]; s[11] = rotate_left64(s[11],46); s[10] += s[ 0];     \
} while(0)

/**
 * Mix all 12 inputs together so that h0, h1 are a hash of them all.
 * 
 * For two inputs differing in just the input bits
 * Where "differ" means xor or subtraction
 * And the base value is random, or a counting value starting at that bit
 * The final result will have each bit of h0, h1 flip
 * For every input bit,
 * with probability 50 +- .3%
 * For every pair of input bits,
 * with probability 50 +- 3%
 * 
 * This does not rely on the last Mix() call having already mixed some.
 * Two interations was almost good enough for a 64 bit result, but a
 * 128 bit result is reported, so spooky_mix_end() does three interations.
 */

#define spooky_end_partical(h) do {                                             \
    h[11] += h[ 1];   h[ 2] ^= h[11]; h[ 1] = rotate_left64(h[ 1],44);          \
    h[ 0] += h[ 2];   h[ 3] ^= h[ 0]; h[ 2] = rotate_left64(h[ 2],15);          \
    h[ 1] += h[ 3];   h[ 4] ^= h[ 1]; h[ 3] = rotate_left64(h[ 3],34);          \
    h[ 2] += h[ 4];   h[ 5] ^= h[ 2]; h[ 4] = rotate_left64(h[ 4],21);          \
    h[ 3] += h[ 5];   h[ 6] ^= h[ 3]; h[ 5] = rotate_left64(h[ 5],38);          \
    h[ 4] += h[ 6];   h[ 7] ^= h[ 4]; h[ 6] = rotate_left64(h[ 6],33);          \
    h[ 5] += h[ 7];   h[ 8] ^= h[ 5]; h[ 7] = rotate_left64(h[ 7],10);          \
    h[ 6] += h[ 8];   h[ 9] ^= h[ 6]; h[ 8] = rotate_left64(h[ 8],13);          \
    h[ 7] += h[ 9];   h[10] ^= h[ 7]; h[ 9] = rotate_left64(h[ 9],38);          \
    h[ 8] += h[10];   h[11] ^= h[ 8]; h[10] = rotate_left64(h[10],53);          \
    h[ 9] += h[11];   h[ 0] ^= h[ 9]; h[11] = rotate_left64(h[11],42);          \
    h[10] += h[ 0];   h[ 1] ^= h[10]; h[ 0] = rotate_left64(h[ 0],54);          \
} while(0)

#define spooky_end(data, h) do {                                                \
    h[ 0] += data[ 0];                                                          \
    h[ 1] += data[ 1];                                                          \
    h[ 2] += data[ 2];                                                          \
    h[ 3] += data[ 3];                                                          \
    h[ 4] += data[ 4];                                                          \
    h[ 5] += data[ 5];                                                          \
    h[ 6] += data[ 6];                                                          \
    h[ 7] += data[ 7];                                                          \
    h[ 8] += data[ 8];                                                          \
    h[ 9] += data[ 9];                                                          \
    h[10] += data[10];                                                          \
    h[11] += data[11];                                                          \
    spooky_end_partical(h);                                                     \
    spooky_end_partical(h);                                                     \
    spooky_end_partical(h);                                                     \
} while(0)

/**
 * number of uint64's in internal state.
 * 
 */
static const uint64_t numbervar = 12;

/**
 * size of the internal state
 */
static const uint64_t blocksize = numbervar * 8;

/**
 * size of buffer of unhashed data, in bytes
 */
static const uint64_t buffersize = 2 * blocksize;

/**
 * A constant which:
 * 
 * - is not zero
 * - is odd
 * - is a not very regular mix of 1's and 0's
 * - does not need any other special mathematical properties
 * 
 */
static const uint64_t constant = 0xDEADBEEFDEADBEEFllu;

static void spooky_short(const void * message, uint64_t n, uint64_t * first, uint64_t * second);

/**
 * Hash a single message in one call, produce 128 bit output.
 * 
 * @param in        message | const void * | message to hash
 * @param in        n       | uint64_t     | length of message in bytes
 * @param inout     frist   | uint64_t     | in: first seed, out: first hash value
 * @param inout     second  | uint64_t     | in: second seed, oiut: second hash value
 */
extern void spooky_hash128(const void * message, uint64_t n, uint64_t * first, uint64_t * second) {
    if(n < buffersize) {
        spooky_hash128(message, n, first, second);
        return;
    }

    uint64_t h[12];
    uint64_t buffer[numbervar];
    uint64_t * end = nil;
    union {
        const uint8_t * p8;
        uint64_t *p64;
        uint64_t i;
    } u;
    uint64_t remainder;

    h[0] = h[3] = h[6] = h[ 9] = *first;
    h[1] = h[4] = h[7] = h[10] = *second;
    h[2] = h[5] = h[8] = h[11] = constant;

    u.p8 = (const uint8_t *) message;
    end = u.p64 + (n / blocksize) * numbervar;

    /**
     * Handle all whole block size blocks of bytes
     */

    if(ALLOW_UNALIGNED_READS || ((u.i & 0x7) == 0)) {
        while(u.p64 < end) {
            spooky_mix(u.p64, h);
            u.p64 = u.p64 + numbervar;
        }
    } else {
        while(u.p64 < end) {
            memcpy(buffer, u.p64, blocksize);
        }
    }

    /**
     * Handle the last partical block of block size bytes
     */

    remainder = (n - ((const uint8_t *) end - (const uint8_t *) message));
    memcpy(buffer, end, remainder);
    memset(((uint8_t *) buffer) + remainder, 0, blocksize - remainder);
    ((uint8_t *) buffer)[blocksize - 1] = remainder;

    /**
     * Do some final mixing
     */

    spooky_end(buffer, h);
    *first = h[0];
    *second = h[1];
}

/**
 * Hash a single message in one call, return 64 bit output
 * 
 * @param in        message | const void * | message to hash
 * @param in        n       | uint64_t     | length of message in bytes
 * @param in        seed    | uint64_t     | seed
 */
extern uint64_t spooky_hash64(const void * message, uint64_t n, uint64_t seed) {
    uint64_t first = seed;

    spooky_hash128(message, n, &first, &seed);

    return first;

}

/**
 * Hash a single message in one call, produce 32 bit output.
 * 
 * @param in        message | const void * | message to hash
 * @param in        n       | uint64_t     | length of message in bytes
 * @param in        seed    | uint32_t     | seed
 */
extern uint32_t spooky_hash32(const void * message, uint64_t n, uint32_t seed) {
    uint64_t first = seed;
    uint64_t second = seed;

    spooky_hash128(message, n, &first, &second);

    return (uint32_t)(first);
}

/**
 * Short hash
 * 
 * It could be used on any message, but it's used by Spooky just for short messages.
 */
static void spooky_short(const void * message, uint64_t n, uint64_t * first, uint64_t * second) {
    uint64_t buffer[2 * numbervar];
    union {
        const uint8_t * p8;
        uint32_t * p32;
        uint64_t * p64;
        uint64_t i;
    } u;

    u.p8 = (const uint8_t *) message;

    if(!ALLOW_UNALIGNED_READS && (u.i & 0x7)) {
        memcpy(buffer, message, n);
        u.p64 = buffer;
    }

    uint64_t remainder = n % 32;
    uint64_t a = *first;
    uint64_t b = *second;
    uint64_t c = constant;
    uint64_t d = constant;

    if(n > 15) {
        const uint64_t * end = u.p64 + (n / 32) * 4;

        /**
         * Handle all complete sets of 32 bytes
         */
        for(; u.p64 < end; u.p64 += 4) {
            c += u.p64[0];
            d += u.p64[1];
            spooky_short_mix(a, b, c, d);
            a += u.p64[2];
            b += u.p64[3];
        }

        /**
         * Handle the case of 16+ remaining bytes.
         */
        if(remainder >= 16) {
            c += u.p64[0];
            d += u.p64[1];

            spooky_short_mix(a, b, c, d);
            u.p64 += 2;
            remainder -= 16;
        }
    }

    /**
     * Handle th last 0..15 bytes, and its length
     */

    d += ((uint64_t) n) << 56;
    switch(remainder) {
        case 15:    d += ((uint64_t) u.p8[14]) << 48;
        case 14:    d += ((uint64_t) u.p8[13]) << 40;
        case 13:    d += ((uint64_t) u.p8[12]) << 32;
        case 12:    d += u.p32[2];
                    c += u.p64[0];
                    break;
        case 11:    d += ((uint64_t) u.p8[10]) << 16;
        case 10:    d += ((uint64_t) u.p8[ 9]) <<  8;
        case  9:    d += ((uint64_t) u.p8[ 8])      ;
        case  8:    c += u.p64[0];
                    break;
        case  7:    c += ((uint64_t) u.p8[ 6]) << 48;
        case  6:    c += ((uint64_t) u.p8[ 5]) << 40;
        case  5:    c += ((uint64_t) u.p8[ 4]) << 32;
        case  4:    c += u.p32[0];
                    break;
        case  3:    c += ((uint64_t) u.p8[ 2]) << 16;
        case  2:    c += ((uint64_t) u.p8[ 1]) <<  8;
        case  1:    c += ((uint64_t) u.p8[ 0]);
                    break;
        case  0:    c += constant;
                    d += constant;
    }

    spooky_short_end(a, b, c, d);

    *first = a;
    *second = b;
}