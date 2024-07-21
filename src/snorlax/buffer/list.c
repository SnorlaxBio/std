#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#include "list.h"

static buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer);
static int64_t buffer_list_func_in(buffer_list_t * buffer, int fd);
static int64_t buffer_list_func_out(buffer_list_t * buffer, int fd);
static int64_t buffer_list_func_inmsg(buffer_list_t * buffer, int fd, struct msghdr * msg, int flags);
static int64_t buffer_list_func_outmsg(buffer_list_t * buffer, int fd, struct msghdr * msg, int flags);

static buffer_list_func_t func = {
    buffer_list_func_rem,
    buffer_list_func_in,
    buffer_list_func_out,
    buffer_list_func_inmsg,
    buffer_list_func_outmsg
};

extern buffer_list_t * buffer_list_gen(void) {
    buffer_list_t * buffer = (buffer_list_t *) calloc(1, sizeof(buffer_list_t));

    buffer->func = address_of(func);

    return buffer;
}

static buffer_list_t * buffer_list_func_rem(buffer_list_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->head;
    while(buffer->head) {
        buffer->head = node->next;

        node->prev = nil;
        node->next = nil;
        node->collection = nil;

        buffer_list_node_rem(node);

        node = buffer->head;
    }

    buffer->sync = sync_rem(buffer->sync);
    
    free(buffer);

    return nil;
}

static int64_t buffer_list_func_in(buffer_list_t * buffer, int fd) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
    snorlaxdbg(buffer->back == nil && buffer->tail && buffer_list_node_remain(buffer->tail), false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = (buffer->back == nil || buffer_list_node_remain(buffer->back) == 0) ? buffer_list_nodegen(buffer) : buffer->back;

    int64_t n = read(fd, buffer_list_node_back(node), buffer_list_node_remain(node));

    if(n > 0) {
        buffer_list_node_size_set(node, buffer_list_node_size_get(node) + n);

        buffer->back = buffer_list_node_remain(node) == 0 ? node->next : node;
    } else if(n == 0) {
        errno = 0;

#ifndef   RELEASE
        snorlaxdbg(true, false, "implement", "set end of file error number.");
#endif // RELEASE

        return fail;
    } else {
        if(errno == EAGAIN) {
            n = 0;
        }
    }

    return n;
}

static int64_t buffer_list_func_out(buffer_list_t * buffer, int fd) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
    snorlaxdbg(buffer->front == nil && buffer->head && buffer_list_node_length(buffer->front), false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->front == nil || buffer_list_node_length(buffer->front) == 0 ? nil : buffer->front;

    if(node) {
        int64_t n = write(fd, buffer_list_node_front(node), buffer_list_node_length(node));

        if(n > 0) {
            buffer_list_node_position_set(node, buffer_list_node_position_get(node) + n);
            
            buffer->front = buffer_list_node_length(node) == 0 ? node->next : node;
        } else if(n == 0) {
            errno = 0;

#ifndef   RELEASE
            snorlaxdbg(true, false, "check", "");
#endif // RELEASE

            return fail;
        } else {
            if(errno == EAGAIN) {
                n = 0;
            }
        }

        return n;
    }

#ifndef   RELEASE
    snorlaxdbg(false, true, "check", "");
#endif // RELEASE

    return success;
}

static int64_t buffer_list_func_inmsg(buffer_list_t * buffer, int fd, struct msghdr * msg, int flags) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(msg == nil, false, "critical", "");
    snorlaxdbg(buffer->back == nil && buffer->tail && buffer_list_node_remain(buffer->tail), false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = (buffer->back == nil || buffer_list_node_remain(buffer->back) == 0) ? buffer_list_nodegen(buffer) : buffer->back;

    struct iovec iov = { buffer_list_node_back(node), buffer_list_node_remain(node) };

    msg->msg_iov = &iov;
    msg->msg_iovlen = 1;

    int64_t n = recvmsg(fd, msg, flags);

    if(n > 0) {
        buffer_list_node_size_set(node, buffer_list_node_size_get(node) + n);

        buffer->back = buffer_list_node_remain(node) == 0 ? node->next : node;
    } else if(n == 0) {
        errno = 0;
#ifndef   RELEASE
        snorlaxdbg(n == 0, false, "critical", "implement out");
#endif // RELEASE

        return fail;
    } else {
        if(errno == EAGAIN) {
            n = 0;
        }
    }

    return n;
}

static int64_t buffer_list_func_outmsg(buffer_list_t * buffer, int fd, struct msghdr * msg, int flags) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(msg == nil, false, "critical", "");
    snorlaxdbg(buffer->front == nil && buffer->head && buffer_list_node_length(buffer->front), false, "critical", "");
#endif // RELEASE

    buffer_list_node_t * node = buffer->front == nil || buffer_list_node_length(buffer->front) == 0 ? nil : buffer->front;

    if(node) {
        struct iovec iov = { buffer_list_node_front(node), buffer_list_node_length(node) };

        int64_t n = sendmsg(fd, msg, flags);

        if(n > 0) {
            buffer_list_node_position_set(node, buffer_list_node_position_get(node) + n);

            buffer->front = buffer_list_node_length(node) == 0 ? node->next : node;
        } else if(n == 0) {
            errno = 0;
#ifndef   RELEASE
            snorlaxdbg(n == 0, false, "critical", "");
#endif // RELEASE
            return fail;
        } else {
            if(errno == EAGAIN) {
                n = 0;
            }
        }
    }

#ifndef   RELEASE
    snorlaxdbg(false, true, "check", "");
#endif // RELEASE
    
    return success;
}
