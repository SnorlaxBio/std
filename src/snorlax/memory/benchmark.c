#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define max     100000
#define size    (65536 * 64)

int main(int argc, char ** argv) {
    struct timespec start;
    struct timespec end;
    struct timespec elapse;
    
    void ** mem = (void **) malloc(max * sizeof(void *));
    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < max; i++) {
        mem[i] = malloc(size);
    }
    clock_gettime(CLOCK_REALTIME, &end);

    elapse.tv_sec = end.tv_sec - start.tv_sec;
    elapse.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(elapse.tv_nsec < 0) {
        elapse.tv_sec = elapse.tv_sec - 1;
        elapse.tv_nsec = elapse.tv_nsec + 1000000000;
    }
    printf("%d bytes %d mallo call => %ld.%09ld\n", size, max, elapse.tv_sec, elapse.tv_nsec);
    for(int i = 0; i < max; i++) {
        free(mem[i]);
    }
    free(mem);
    return 0;
}
