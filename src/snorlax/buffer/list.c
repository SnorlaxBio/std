#include "list.h"

static buffer_list_func_t func = {

};

extern buffer_list_t * buffer_list_gen(void) {
    buffer_list_t * buffer = (buffer_list_t *) calloc(1, sizeof(buffer_list_t));

    buffer->func = address_of(func);

    return buffer;
}