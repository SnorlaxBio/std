#include <stdlib.h>

#include "hashtable.h"

static hashtable_func_t func = {
    hashtable_func_rem,
    hashtable_func_get,
    hashtable_func_set,
    hashtable_func_del,
    hashtable_func_expand,
    hashtable_func_shrink
};

extern hashtable_t * hashtable_gen(hash_t hash) {
#ifndef   RELEASE
    snorlaxdbg(hash == nil, false, "critical", "");
#endif // RELEASE

    hashtable_t * collection = (hashtable_t *) calloc(1, sizeof(hashtable_t));

    collection->func = address_of(func);
    collection->hash = hash;

    collection->front = hashtable_bucket_gen(hashtable_bucket_exponent_initial);

    return collection;
}

extern hashtable_t * hashtable_func_rem(hashtable_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    if(collection->front) collection->front = hashtable_bucket_rem(collection->front);

    if(collection->back) collection->back = hashtable_bucket_rem(collection->back);

    collection->sync = sync_rem(collection->sync);

    free(collection);

    return nil;
}

extern hashtable_node_t * hashtable_func_get(hashtable_t * collection, hashtable_node_key_t * key) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE
    uint64_t v = collection->hash(key->value, key->length);
    hashtable_node_t * node = hashtable_bucket_get(collection->front, key, v);

    if(node == nil) {
        if(collection->back) {
            node = hashtable_bucket_get(collection->back, key, v);

            if(node) hashtable_bucket_set(collection->front, key, v, node);
        }
    }

    hashtable_shrink(collection);

    return node;
}

extern hashtable_node_t * hashtable_func_set(hashtable_t * collection, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_key_t * key = address_of(node->key);

    uint64_t v = collection->hash(key->value, key->length);

    hashtable_bucket_set(collection->front, key, v, node);

    collection->size = collection->front->size + (collection->back ? collection->back->size : 0);

    if(hashtable_bucket_rehash_threshold_cal(collection->front) <= collection->size) {
        hashtable_expand(collection);
    }

    hashtable_shrink(collection);

    return node;
}

extern hashtable_node_t * hashtable_func_del(hashtable_t * collection, hashtable_node_key_t * key) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE

    uint64_t v = collection->hash(key->value, key->length);

    hashtable_node_t * node = hashtable_bucket_del(collection->front, key, v);

    if(node == nil) {
        if(collection->back) {
            node = hashtable_bucket_del(collection->back, key, v);
        }
    }

    hashtable_shrink(collection);

    return node;
}

extern int32_t hashtable_func_expand(hashtable_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    if(collection->back == nil) {
        collection->back = collection->front;

        collection->front = hashtable_bucket_gen((collection->front->exponent = collection->front->exponent + 1));

        hashtable_shrink(collection);

        return success;
    }

    return fail;
}

extern int32_t hashtable_func_shrink(hashtable_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    if(collection->back) {
        collection->moved = hashtable_bucket_move(collection->front, collection->back, hashtable_bucket_rehash_move_max, collection->hash, collection->moved);

        if(hashtable_bucket_size_get(collection->back) == 0) {
            collection->back = hashtable_bucket_rem(collection->back);
            collection->moved = 0;

            return success;
        }

        return fail;
    }

    return success;
}
