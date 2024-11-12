#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stdlib.h>

typedef struct {
    void *elements;
    size_t capacity;
    size_t length;
    size_t elementSize;
} DynArr;

DynArr newDynArr(size_t elementSize);
void freeDynArr(DynArr *arr);
void popDA(DynArr *arr);
void appendDA(DynArr *arr, void *element);
void *atDA(DynArr *arr, size_t index);

#endif
