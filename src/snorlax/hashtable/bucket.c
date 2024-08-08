#include "../hashtable.h"

static hashtable_bucket_func_t func = {
    hashtable_bucket_func_rem,
    hashtable_bucket_func_get,
    hashtable_bucket_func_set,
    hashtable_bucket_func_del,
    hashtable_bucket_func_list,
    hashtable_bucket_func_move
};

extern hashtable_bucket_t * hashtable_bucket_gen(uint8_t exponent) {
    hashtable_bucket_t * bucket = (hashtable_bucket_t *) calloc(1, sizeof(hashtable_bucket_t));

    bucket->func = address_of(func);
    bucket->exponent = exponent;
    bucket->container = (hashtable_list_t **) calloc(hashtable_bucket_size_cal(bucket), sizeof(hashtable_list_t *));

    return bucket;
}

extern hashtable_bucket_t * hashtable_bucket_func_rem(hashtable_bucket_t * bucket) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
#endif // RELEASE

    if(bucket->container) {
        uint64_t n = hashtable_bucket_size_cal(bucket);

        for(uint64_t i = 0; i < n; i++) {
            hashtable_list_t * list = bucket->container[i];
            if(list) hashtable_list_rem(list);
        }
    }

    bucket->sync = sync_rem(bucket->sync);

    free(bucket);

    return nil;
}

extern hashtable_node_t * hashtable_bucket_func_get(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = nil;

    uint64_t index = hashtable_bucket_index_cal(bucket, v);

    hashtable_list_t * list = bucket->container[index];

    if(list) node = hashtable_list_get(list, key);

    return node;
}

extern hashtable_node_t * hashtable_bucket_func_set(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v, hashtable_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
#endif // RELEASE

    uint64_t index = hashtable_bucket_index_cal(bucket, v);

    hashtable_list_t * list = bucket->container[index];

    if(list == nil) bucket->container[index] = list = hashtable_list_gen();

    hashtable_list_push(list, node);

    return node;
}

extern hashtable_node_t * hashtable_bucket_func_del(hashtable_bucket_t * bucket, hashtable_node_key_t * key, uint64_t v) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
    snorlaxdbg(key == nil, false, "critical", "");
#endif // RELEASE

    hashtable_node_t * node = nil;

    uint64_t index = hashtable_bucket_index_cal(bucket, v);

    hashtable_list_t * list = bucket->container[index];

    if(list) node = hashtable_list_get(list, key);

    return node;
}

extern hashtable_list_t * hashtable_bucket_func_list(hashtable_bucket_t * bucket, uint64_t v, int32_t gen) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
#endif // RELEASE

    uint64_t index = hashtable_bucket_index_cal(bucket, v);

    hashtable_list_t * list = bucket->container[index];

    if(list == nil && gen) bucket->container[index] = list = hashtable_list_gen();

    return list;
}

extern uint64_t hashtable_bucket_func_move(hashtable_bucket_t * bucket, hashtable_bucket_t * back, uint64_t threshold, hash_t hash, uint64_t last) {
#ifndef   RELEASE
    snorlaxdbg(bucket == nil, false, "critical", "");
    snorlaxdbg(back == nil, false, "critical", "");
#endif // RELEASE

    hashtable_list_t * list = nil;

    uint64_t index = last;

    while((list = back->container[index]) && threshold > 0) {
        hashtable_node_t * node = nil;
        while((node = hashtable_list_begin(list)) && threshold > 0) {
            hashtable_list_del(list, node);
            hashtable_node_key_t * key = address_of(node->key);
            uint64_t v = hash(key);
            hashtable_bucket_set(bucket, key, v, node);
            threshold = threshold - 1;
        }

        if(threshold) {
            back->container[index] = hashtable_list_rem(back->container[index]);
            index = index + 1;
        }
    }

    return index;
}
