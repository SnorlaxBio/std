/**
 * @file        snorlax.h
 * @brief       Snorlax standard library header file
 * @details     Snorlax 의 다양한 라이브러리, 프레임워크와 소프트웨어 구현에서
 *              표준으로 사용할 타입, 구조체, 매크로 그리고 함수들을 선언한 파일입니다.
 *              
 *              이 선언 안에는 자주 사용되어지는 프리미티브 타입과 자주 사용하는 성공,
 *              실패 혹은 널과 같은 상수가 선언되어 있다.
 * 
 *              기본적인 이름 규칙은 스네이크 형태이다.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__H__
#define   __SNORLAX__H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ___notnull
#define ___null
#define ___synchronized
#define ___notsynchronized

#define ___notused(v)               ((void)(v))

typedef void *                      address_t;

#define success                     0
#define fail                        (-1)
#define invalid                     (-1)
#define nil                         ((void *) 0)

#define address_of(v)               (&(v))

#define int8_of(o)                  (*((int8_t *)(o)))
#define int16_of(o)                 (*((int16_t *)(o)))
#define int32_of(o)                 (*((int32_t *)(o)))
#define int64_of(o)                 (*((int64_t *)(o)))
#define uint8_of(o)                 (*((uint8_t *)(o)))
#define uint16_of(o)                (*((uint16_t *)(o)))
#define uint32_of(o)                (*((uint32_t *)(o)))
#define uint64_of(o)                (*((uint64_t *)(o)))

#define uint64_from_uint32x2(f, s)  (((uint64_t)((uint32_t) (f)) << 32LU) | ((uint64_t)((uint32_t) (s))))

extern address_t memory_gen(address_t m, uint64_t n);
extern address_t memory_rem(address_t m);

struct sync;
struct sync_func;

typedef struct sync sync_t;
typedef struct sync_func sync_func_t;

struct sync {
    sync_func_t * func;
};

struct sync_func {
    sync_t * (*rem)(sync_t *);

    int32_t (*lock)(sync_t *);
    int32_t (*unlock)(sync_t *);
    int32_t (*wait)(sync_t *, int64_t, int64_t);
    int32_t (*wakeup)(sync_t *, int32_t);
};

extern sync_t * sync_gen(void);

#define sync_rem(sync)                  (sync ? sync->func->rem(sync) : nil)
#define sync_lock(sync)                 (sync ? sync->func->lock(sync) : success)
#define sync_unlock(sync)               (sync ? sync->func->unlock(sync) : success)
#define sync_wait(sync, second, nano)   (sync ? sync->func->wait(sync, second, nano) : success)
#define sync_wakeup(sync, all)          (sync ? sync->func->wakeup(sync, all) : success)

#define sync_on(o) do {             \
    if(o->sync == nil) {            \
        o->sync = sync_gen();       \
    }                               \
} while(0)

#define sync_off(o) do {            \
    o->sync = sync_rem(o->sync);    \
} while(0)

struct object;
struct object_func;

typedef struct object object_t;
typedef struct object_func object_func_t;

/**
 * @struct      struct object
 * @brief       기본 객체 인터페이스 자료 구조
 * @details     특별한 케이스가 아니면 거의 모든 구조체는 아래와 같은 구조를 지닌다.
 *              이런 구조를 지니기 때문에 암시적 형변환을 통하여 object_func_t 에 정의된
 *              함수를 공통적으로 호출할 수 있다.
 * 
 *              간단하게 객체의 소멸자를 호출하는 것은 `o->func->rem(o)` 와 같이 호출하여
 *              어떤 타입과 상관없이 객체를 쉽게 삭제할 수 있도록 하였다.
 *              
 *              함수 테이블을 둔 것은 함수 타입을 객체의 멤버로 정의하면 구조체의 크기가 
 *              커지기 때문이다. 또한, func 멤버를 통해서 객체가 어떤 객체인지 유추할 수 있다.
 *              또한, 그렇게 구현할 수 있다.
 *              
 *              어찌보면, 클래스와 유사한 구조이긴 하다.
 *              차후에 클래스와 성능에 대해서 벤치마킹을 수행할 필요는 있다.
 */
struct object {
    object_func_t * func;
    sync_t * sync;
};

struct object_func {
    object_t * (*rem)(object_t *);
};

#define object_rem(o)                   (o->func->rem(o))

#define object_lock(o)                  (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->lock(((object_t *) o)->sync) : success)
#define object_unlock(o)                (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->unlock(((object_t *) o)->sync) : success)
#define object_wait(o, second, nano)    (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wait(((object_t *) o)->sync, second, nano) : success)
#define object_wakeup(o, all)           (((o) && ((object_t *) o)->sync) ? ((object_t *) o)->sync->func->wakeup(((object_t *) o)->sync, all) : success)

union variable;

typedef union variable variable_t;

/**
 * @union           union variable
 * @brief           다양한 타입의 변수를 사용할 수 있는 타입
 * @details         일반화 프로그래밍을 해야 할 때, 다양한 타입의 변수형을 나타낼 수 있다.
 *                  다만, 64비트 이상의 타입이 필요할 경우는 포인터를 사용해야 한다.
 */
union variable {
    int8_t    i8;
    int16_t   i16;
    int32_t   i32;
    int64_t   i64;
    uint8_t   u8;
    uint16_t  u16;
    uint32_t  u32;
    uint64_t  u64;
    address_t o;
};

typedef void (*variable_callback_t)(variable_t);

#define variable_int32(v)       ((variable_t) { .i32 = v })
#define variable_uint32(v)      ((variable_t) { .u32 = v })
#define variable_uint64(v)      ((variable_t) { .u64 = v })
#define variable_int64(v)       ((variable_t) { .i64 = v })

// TODO: TIMESTAMP
#define snorlaxdbg(expression, type, format, ...) do {              \
    printf("[%s|%s:%d|%s] ", type, __FILE__, __LINE__, __func__);   \
    printf(format, ##__VA_ARGS__);                                  \
    if(expression) {                                                \
        printf(" => [critical] ");                                  \
        printf(#expression);                                        \
        printf("\n");                                               \
        abort();                                                    \
    }                                                               \
} while(0)

#endif // __SNORLAX__H__
