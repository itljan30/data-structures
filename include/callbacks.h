#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <string.h>

typedef void (*FreeFunc)(void *data);

typedef int (*CompareFunc)(void *a, void *b);

int defaultCompare(void *a, void *b, size_t elementSize);


#endif
