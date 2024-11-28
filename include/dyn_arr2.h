#ifndef DYN_ARR2_H
#define DYN_ARR2_H

#include <stdlib.h>

typedef struct {
    void *elements;
    size_t capacity;
    size_t length;
    size_t elementSize;
} DynArr;

DynArr *DynArr_new(size_t elementSize);

void DynArr_free(DynArr *arr);

void DynArr_pop(DynArr *arr);

void DynArr_append(DynArr *arr, void *element);

void DynArr_insert(DynArr *arr, size_t index, void *element);

void *DynArr_at(DynArr *arr, size_t index);

size_t DynArr_len(DynArr *arr);

size_t DynArr_capacity(DynArr *arr);

#endif
