#include "snorlax.h"

extern void hexdump(FILE * stream, const uint8_t * data, uint64_t len) {
    char str[32];
    str[16] = 0;
    for(uint64_t i = 0; i < len; i++) {
        str[i % 16] = (32 <= data[i] && data[i] < 128) ? data[i] : '.';
        if(i % 16 == 0) {
            fprintf(stream, "| %08x | %02x", (uint32_t) i, data[i]);
        } else {
            fprintf(stream, " %02x", data[i]);
        }

        if((i + 1) % 16 == 0) {
            fprintf(stream, " | %s |\n", str);
        } else if((i + 1) == len) {
            for(uint64_t j = (i + 1) % 16; j < 16; j++) {
                str[j] = ' ';
                fprintf(stream, "   ");
            }
            fprintf(stream, " | %s |\n", str);
        }
    }
    
}