#include "lib/memory.h"

extern "C" {
    void memcpy(void *dst, void *src, uint32_t bytes) {
        uint32_t i{0};
        char * d{static_cast<char *>(dst)};
        char * s{static_cast<char *>(src)};

        while (i < bytes) {
            d[i] = s[i];
            ++i;
        }
    }
}