// /**
//  * @file        snorlax/queue.h
//  * @brief
//  * @details
//  * 
//  * @author      snorlax <ceo@snorlax.bio>
//  * @since       June 17, 2024
//  * 
//  * @todo        업그레이드 하자.
//  * @deprecated
//  */

// #ifndef   __SNORLAX__QUEUE__H__
// #define   __SNORLAX__QUEUE__H__

// #include <snorlax.h>

// struct queue;
// struct queue_func;
// struct queue_node;
// struct queue_node_func;

// typedef struct queue queue_t;
// typedef struct queue_func queue_func_t;
// typedef struct queue_node queue_node_t;
// typedef struct queue_node_func queue_node_func_t;

// struct queue {
//     queue_func_t * func;

//     sync_t * sync;

//     uint64_t size;
//     queue_node_t * head;
//     queue_node_t * tail;
// };

// // TODO: 메서드가 많다. QUEUE 의 상속에 대해서 조금 고민을 많이 하자....
// struct queue_func {
//     queue_t * (*rem)(queue_t *);

//     queue_node_t * (*add)(queue_t *, variable_t);           // NODE 로 변경하자.
//     queue_node_t * (*del)(queue_t *, variable_t);           // NODE 로 변경하자.
//     void (*clear)(queue_t *, variable_callback_t);          // NODE CALLBACK 으로 변경하자.
//     queue_node_t * (*begin)(queue_t *);
//     queue_node_t * (*end)(queue_t *);
//     queue_node_t * (*find)(queue_t *, variable_t);          // 고민을 조금 하자.... 업그레이드가 필요하다.
//     uint64_t (*size)(queue_t *);                            // INLINE 메서드로 변경하자.

//     queue_node_t * (*node)(variable_t);                     // 필요한 이유를 모르겠다.

//     queue_node_t * (*push)(queue_t *, queue_node_t *);      // 리턴 값에 대해서 고민하자. 필요 없을지도 모른다.
//     queue_node_t * (*pop)(queue_t *);
// };

// #define queue_rem(queue)            ((queue) ? (queue)->func->rem(queue) : nil)
// #define queue_add(queue, v)         ((queue) ? (queue)->func->add(queue, v) : nil)
// #define queue_del(queue, v)         ((queue) ? (queue)->func->del(queue, v) : nil)
// #define queue_clear(queue, callback) do {       \
//     if(queue) {                                 \
//         (queue)->func->clear(queue, callback);  \
//     }                                           \
// } while(0)
// #define queue_begin(queue)          ((queue) ? (queue)->func->begin(queue) : nil)
// #define queue_end(queue)            ((queue) ? (queue)->func->end(queue) : nil)
// #define queue_find(queue, v)        ((queue) ? (queue)->func->find(queue, v) : nil)
// #define queue_size(queue)           ((queue) ? (queue)->func->size(queue) : 0LU)
// #define queue_node(queue, v)        ((queue) ? (queue)->func->node(v) : nil)
// #define queue_push(queue, node)     ((queue) ? (queue)->func->push(queue, node) : nil)
// #define queue_pop(queue)            ((queue) ? (queue)->func->pop(queue) : nil)

// extern queue_t * queue_gen(void);

// extern queue_t * queue_func_rem(queue_t * queue);
// extern queue_node_t * queue_func_add(queue_t * queue, variable_t v);
// extern queue_node_t * queue_func_del(queue_t * queue, variable_t v);
// extern void queue_func_clear(queue_t * queue, variable_callback_t callback);
// extern queue_node_t * queue_func_begin(queue_t * queue);
// extern queue_node_t * queue_func_end(queue_t * queue);
// extern queue_node_t * queue_func_find(queue_t * queue, variable_t v);
// extern uint64_t queue_func_size(queue_t * queue);
// extern queue_node_t * queue_func_node(variable_t v);
// extern queue_node_t * queue_func_push(queue_t * queue, queue_node_t * node);
// extern queue_node_t * queue_func_pop(queue_t * queue);

// struct queue_node {
//     queue_node_func_t * func;
//     sync_t * sync;

//     queue_t * queue;
//     queue_node_t * prev;
//     queue_node_t * next;

//     variable_t v;
// };

// struct queue_node_func {
//     queue_node_t * (*rem)(queue_node_t *);

//     variable_t (*get)(queue_node_t *);
//     void (*set)(queue_node_t *, variable_t);

//     queue_node_t * (*del)(queue_node_t *, queue_t *);

//     queue_node_t * (*prev)(queue_node_t *);
//     queue_node_t * (*next)(queue_node_t *);
// };

// extern queue_node_t * queue_node_gen(variable_t v);

// #define queue_node_rem(node)            ((node) ? (node)->func->rem(node) : nil)
// #define queue_node_get(node)            ((node)->func->get(node))
// #define queue_node_set(node, v) do {        \
//     if(node) {                              \
//         (node)->func->set(node, v);         \
//     }                                       \
// } while(0)
// #define queue_node_del(node, queue)     ((node) ? (node)->func->del(node, queue) : nil)
// #define queue_node_prev(node)           ((node) ? (node)->func->prev(node) : nil)
// #define queue_node_next(node)           ((node) ? (node)->func->next(node) : nil)

// extern queue_node_t * queue_node_func_rem(queue_node_t * node);
// extern variable_t queue_node_func_get(queue_node_t * node);
// extern void queue_node_func_set(queue_node_t * node, variable_t v);
// extern queue_node_t * queue_node_func_del(queue_node_t * node, queue_t * queue);
// extern queue_node_t * queue_node_func_prev(queue_node_t * node);
// extern queue_node_t * queue_node_func_next(queue_node_t * node);

// #endif // __SNORLAX__QUEUE__H__
