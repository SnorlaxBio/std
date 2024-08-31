/**
 * @file        snorlax/memory.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       June 15, 2024
 */

#include <stdlib.h>
#include <string.h>

#include "../snorlax.h"

/**
 * @fn          extern address_t memory_gen(address_t m, uint64_t n)
 * @brief       allocate or reallocate dymamic memory
 * @details     메모리 할당 함수는 `m: address_t` 의 값에 따라서 새롭게 메모리를 할당하거나
 *              기본의 메모리 크기를 업그레이드 한다. 그리고 `n: uint64_t` 가 0인 경우는
 *              메모리를 해제하고, nil 을 리턴한다.
 * 
 * @param[in]   m | address_t | m 이 null 이면 새롭게 메모리를 할당하고, 그렇지 않으면 메모리 크기를 재할당한다. |
 * @param[in]   n | uint64_t | 할당할 메모리 영역의 크기, 만약 n 이 0 이면, 메모리를 해제한다. |
 * 
 * @return      | address_t | 할당되거나 재할당된 메모리 주소 (만약에 n 이 0 이면 메모리 영역을 삭제하고 nil 을 리턴한다.) |
 */
extern address_t memory_gen(address_t m, uint64_t n) {
    if(n == 0) {
        if(m) free(m);

        return nil;
    }

    return m ? realloc(m, n) : malloc(n);
}

/**
 * @fn          extern address_t memory_rem(address_t m)
 * @brief       free a allocated dynamic memory
 * @details     `m: address_t` 가 널이면 `free()` 함수를 호출하지 않는다.
 *              일반적인 `free()`의 구현은 `null`을 체크하도록 되어 있지만,
 *              예외를 발생시키는 라이브러리들도 존재한다. 그렇기 때문에,
 *              사용자 구현에서 분기문을 통하여 null 일 경우 `free()`를 호출하지 않도록
 *              구현해 주어야 한다. 파라미터가 항상 널이 아닌 경우는 직접 `free()`
 *              함수를 호출하도록 하는 것이 좋다.
 * 
 * @param[in]   m | address_t | a allocated dynamic memory variable to free |
 * 
 * @return      | address_t | always return nil |
 */
extern address_t memory_rem(address_t m) {
    if(m) free(m);

    return nil;
}

extern address_t memory_dup(address_t m, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(m == nil, false, "critical", "");
    snorlaxdbg(n == 0, false, "critical", "");
#endif // RELEASE

    void * o = malloc(n);

    memcpy(o, m, n);

    return o;
}