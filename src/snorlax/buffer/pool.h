/**
 * @file        snorlax/buffer/pool.h
 * @brief       Header file that declares structures and method related to the buffer pool.
 * @details     This header file declares a function table structure that defines the main structure
 *              and main methods of the buffer pool. Additionally, the `gen(size: uint64, page: uint64): pool`
 *              method that dynamically creates a basic buffer pool object and a macro that calls member functions are defined.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 15, 2024
 */

#ifndef   __SNORLAX__BUFFER_POOL__H__
#define   __SNORLAX__BUFFER_POOL__H__

#include <snorlax/buffer.h>

struct buffer_pool_func;

/**
 * @typedef     buffer_pool_func_t
 * @brief       Buffer pool function table type.
 */
typedef struct buffer_pool_func buffer_pool_func_t;

/**
 * @struct      buffer_pool
 * @brief       buffer pool structure
 * @details     The buffer pool structure is an inherited structure with object_t as its parent structure.
 *              It is a basic buffer pool that is created by defining the page size and number of buffers for dynamic memory
 *              allocation at the time of creation. Library users can inherit this structure to define and use new structures.
 * 
 * @image       html ClassDiagramStdBufferPool.jpg "Class Diagram Standard Lib Buffer Pool" width="300"
 * 
 * @var         buffer_pool::func
 * @brief       Buffer pool's virtual function table.
 * 
 * @var         buffer_pool::sync
 * @brief       Buffer pool's synchronize object.
 * 
 * @var         buffer_pool::size
 * @brief       Buffer pool's a total count of buffer.
 * 
 * @var         buffer_pool::page
 * @brief       Buffer pool's a basic page size.
 * 
 * @var         buffer_pool::container
 * @brief       buffer object container
 * 
 * @var         buffer_pool::last
 * @brief       buffer pool's last buffer index.
 *              
 */
struct buffer_pool {
    buffer_pool_func_t * func;
    sync_t * sync;
    uint64_t size;
    uint64_t page;
    buffer_t ** container;
    uint64_t last;
};

/**
 * @struct      buffer_pool_func
 * @brief       Buffer Pool Virtual Function Structure
 * 
 * @image       html ClassDiagramStdBufferPool.jpg "Class Diagram Standard Lib Buffer Pool" width="300"
 * 
 * @var         buffer_pool_func::rem
 * @brief       Destructor
 * 
 * @var         buffer_pool_func::get
 * @brief       Get buffer from buffer pool object.
 * 
 * @var         buffer_pool_func::rel
 * @brief       Release buffer to buffer pool object.
 */
struct buffer_pool_func {
    buffer_pool_t * (*rem)(buffer_pool_t *);
    buffer_t * (*get)(buffer_pool_t *);
    buffer_t * (*rel)(buffer_pool_t *, buffer_t *);
};

/**
 * @fn          buffer_pool_t * buffer_pool_gen(uint64_t size, uint64_t page)
 * @brief       Buffer pool's constructor
 * @details     With the default buffer pool constructor, you can set the size of the buffer to be pre-created
 *              in the pool and the default page when dynamically creating the buffer.
 * 
 * @param[in]   size | uint64_t | Number of buffers to be created in advance |
 * @param[in]   page | uint64_t | page size |
 */
extern buffer_pool_t * buffer_pool_gen(uint64_t size, uint64_t page);

/**
 * @def         buffer_pool_rem
 * @brief       Call pool's destructor
 * @param[in]   pool | buffer_pool_t | ...
 *              Pool's object
 * 
 * @return      | buffer_pool_t | ...
 *              Always return nil
 */
#define buffer_pool_rem(pool)           (pool->func->rem(pool))

/**
 * @def         buffer_pool_get
 * @brief       Call pool's get method
 * @param[in]   pool | buffer_pool_t | Buffer pool object
 * 
 * @return      | buffer_t | buffer object from the pool. |
 */
#define buffer_pool_get(pool)           (pool->func->get(pool))

/**
 * @def         buffer_pool_rel
 * @brief       Call pool's release method
 * @param[in]   pool | buffer_pool_t | buffer pool object |
 * @param[in]   buffer | buffer_t | buffer object |
 * @return      | buffer_t | released buffer object |
 * 
 * @todo        check no return (not necessary return value)
 */
#define buffer_pool_rel(pool, buffer)   (pool->func->rel(pool, buffer))

#endif // __SNORLAX__BUFFER_POOL__H__
