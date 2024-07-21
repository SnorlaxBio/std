#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "mem.h"

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer);
static int64_t buffer_mem_func_in(buffer_mem_t * buffer, int fd);
static int64_t buffer_mem_func_out(buffer_mem_t * buffer, int fd);
static int64_t buffer_mem_func_inmsg(buffer_mem_t * buffer, int fd, struct msghdr * msg, int flags);
static int64_t buffer_mem_func_outmsg(buffer_mem_t * buffer, int fd, struct msghdr * msg, int flags);

static buffer_mem_func_t func = {
    buffer_mem_func_rem,
    buffer_mem_func_in,
    buffer_mem_func_out,
    buffer_mem_func_inmsg,
    buffer_mem_func_outmsg
};

extern buffer_mem_t * buffer_mem_gen(uint64_t capacity, uint64_t page) {
    buffer_mem_t * buffer = (buffer_mem_t *) calloc(1, sizeof(buffer_mem_t));

    buffer->func = address_of(func);
    buffer->capacity = capacity;
    buffer->page = page;
    buffer->mem = memory_gen(buffer->mem, capacity);

    return buffer;
}

static buffer_mem_t * buffer_mem_func_rem(buffer_mem_t * buffer) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    buffer->mem = memory_rem(buffer->mem);
    free(buffer);

    return nil;
}

static int64_t buffer_mem_func_in(buffer_mem_t * buffer, int fd) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
#endif // RELEASE

    uint64_t page = buffer->page ? buffer->page : 8192;

    if((buffer->capacity - buffer->size) < page) {
        buffer->mem = memory_gen(buffer->mem, buffer->size + page);
        buffer->capacity = buffer->size + page;
    }

    int64_t n = read(fd, &buffer->mem[buffer->size], buffer->capacity - buffer->size);

    if(n > 0) {
        buffer->size = buffer->size + n;
    } else if(n == 0) {
        errno = 0;

        n = fail;
    } else {
        if(errno == EAGAIN) {
            n = 0;
        }
    }

    return n;
}

static int64_t buffer_mem_func_out(buffer_mem_t * buffer, int fd) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
#endif // RELEASE

    if((buffer->size - buffer->position) > 0) {
        int64_t n = write(fd, &buffer->mem[buffer->position], buffer->size - buffer->position);

        if(n > 0) {
            buffer->position = buffer->position + n;
        } else if(n == 0) {
#ifndef   RELEASE
            snorlaxdbg(false, true, "check", "");
#endif // RELEASE
        } else {
            if(errno == EAGAIN) {
                n = 0;
            }
        }

        return n;
    }

    return success;
}

static int64_t buffer_mem_func_inmsg(buffer_mem_t * buffer, int fd, struct msghdr * msg, int flags) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
    snorlaxdbg(msg == nil, false, "critical", "");
#endif // RELEASE

    uint64_t page = buffer->page ? buffer->page : 8192;

    if((buffer->capacity - buffer->size) < page) {
        buffer->mem = memory_gen(buffer->mem, buffer->size + page);
        buffer->capacity = buffer->size + page;
    }

    struct iovec iov = { &buffer->mem[buffer->size], buffer->capacity - buffer->size };
    msg->msg_iov = &iov;
    msg->msg_iovlen = 1;

    int64_t n = recvmsg(fd, msg, flags);

    if(n > 0) {
        buffer->size = buffer->size + n;
    } else if(n == 0) {
        errno = 0;
        return fail;
    } else {
        if(errno == EAGAIN) {
            n = 0;
        }
    }

    return n;
}

static int64_t buffer_mem_func_outmsg(buffer_mem_t * buffer, int fd, struct msghdr * msg, int flags) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(fd <= invalid, false, "critical", "");
    snorlaxdbg(msg == nil, false, "critical", "");
#endif // RELEASE

    if(buffer->size - buffer->position > 0) {
        struct iovec iov = { &buffer->mem[buffer->position], buffer->size - buffer->position };
        msg->msg_iov = &iov;
        msg->msg_iovlen = buffer->size - buffer->position;

        int64_t n = sendmsg(fd, msg, flags);

        if(n > 0) {
            buffer->position = buffer->position + n;
        } else if(n == 0) {
#ifndef   RELEASE
            snorlaxdbg(false, true, "check", "");
#endif // RELEASE
        } else {
            if(errno == EAGAIN) {
                n = 0;
            }
        }

        return n;
    }

    return success;
}

