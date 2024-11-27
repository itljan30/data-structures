#include "callbacks.h"

#include <string.h>

int defaultCompare(void *a, void *b, size_t elementSize) {
    return memcmp(a, b, elementSize);
}
