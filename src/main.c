/**
 * @file        main.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 12, 2024
 */

#include <stdio.h>

#include <snorlax.h>
#include <snorlax/random.h>
#include <snorlax/list.h>

static void snorlax_bucket_print_int32(variable_t o) {
    printf("%d\n", o.i32);
}

static int snorlax_std_check_list_linked_double(void);

int main(int argc, char ** argv) {
    snorlax_std_check_list_linked_double();
    return 0;
}

static int snorlax_std_check_list_linked_double(void) {
    list_linked_double_t * list = list_linked_double_gen();

    for(int i = 0; i < 32; i++) {
        list_linked_double_add(list, variable_int32(random_int32(32)));
    }

    list = list_linked_double_rem(list, snorlax_bucket_print_int32);

    return success;
}
