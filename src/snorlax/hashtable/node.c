#include "../hashtable.h"

extern hashtable_node_t * hashtable_node_func_rem(hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(node->collection != nil, false, "critical", "");
#endif // RELEASE

    node->sync = sync_rem(node->sync);

    free(node);

    return nil;
}