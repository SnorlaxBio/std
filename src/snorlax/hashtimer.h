/**
 * @file        snorlax/hashtimer.h
 * @brief
 * @details     
 * 
 * 앞의 번호에 대해서 순서 보장이 되는 해쉬
 * 
 * 고민은 초 단위 해쉬를 수행하는가? 아니면 밀리초 단위 해쉬를 수행하는가 이다.
 * 
 * 버켓이 32면 16, 8, 4, 2, 1, 0 로 버켓을 관리한다.
 * 1   - 1024 까지의 번호가 존재하면,
 * 
 * 512 - 1024 까지는  1 에
 * 256 -  512 까지는  1 에
 * 128 -  256 까지는  2 에
 * 64  -  128 까지는  4 에
 * 32  -   64 까지는  8 에
 * 1   -   32 까지는 16 에
 * 
 * 저장된다.
 * 
 * 현재까지 소모된 버켓은 수시로 REHASH 를 수행한다. 
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Sep 1, 2024
 */

#ifndef   __SNORLAX__HASHTIMER__H__
#define   __SNORLAX__HASHTIMER__H__

#include <hashtable.h>
#include <nanosecond.h>

#endif // __SNORLAX__HASHTIMER__H__
