#include <stdlib.h>

#include "../../list.h"
#include "../../queue.h"

typedef list_linked_double_t * (*list_linked_double_func_rem_t)(list_linked_double_t *);
typedef list_linked_double_node_t * (*list_linked_double_func_add_t)(list_linked_double_t *, variable_t);
typedef list_linked_double_node_t * (*list_linked_double_func_del_t)(list_linked_double_t *, variable_t);
typedef void (*list_linked_double_func_clear_t)(list_linked_double_t *, variable_callback_t);
typedef list_linked_double_node_t * (*list_linked_double_func_begin_t)(list_linked_double_t *);
typedef list_linked_double_node_t * (*list_linked_double_func_end_t)(list_linked_double_t *);
typedef list_linked_double_node_t * (*list_linked_double_func_find_t)(list_linked_double_t *, variable_t);
typedef uint64_t (*list_linked_double_func_size_t)(list_linked_double_t *);
typedef list_linked_double_node_t * (*list_linked_double_func_node_t)(variable_t);
typedef list_linked_double_node_t * (*list_linked_double_func_push_t)(list_linked_double_t *, variable_t);
typedef list_linked_double_node_t * (*list_linked_double_func_pop_t)(list_linked_double_t *);

static list_linked_double_func_t func = {
    (list_linked_double_func_rem_t) queue_func_rem,
    (list_linked_double_func_add_t) queue_func_add,
    (list_linked_double_func_del_t) queue_func_del,
    (list_linked_double_func_clear_t) queue_func_clear,
    (list_linked_double_func_begin_t) queue_func_begin,
    (list_linked_double_func_end_t) queue_func_end,
    (list_linked_double_func_find_t) queue_func_find,
    (list_linked_double_func_size_t) queue_func_size,
    (list_linked_double_func_node_t) queue_func_node,
    (list_linked_double_func_push_t) queue_func_push,
    (list_linked_double_func_pop_t) queue_func_pop
};

extern list_linked_double_t * list_linked_double_gen(void) {
    list_linked_double_t * list = (list_linked_double_t *) calloc(1, sizeof(list_linked_double_t));

    list->func = &func;

    return list;
}