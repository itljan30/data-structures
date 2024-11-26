#ifndef COMPARE_FUNC_H
#define COMPARE_FUNC_H

#include <string.h>

typedef int (*CompareFunc)(void *a, void *b);

int defaultCompare(void *a, void *b, size_t elementSize) {
    return memcmp(a, b, elementSize);
}

#endif
