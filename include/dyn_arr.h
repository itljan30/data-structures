#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void *elements;
    size_t capacity;
    size_t length;
    size_t elementSize;
} DynArr;

DynArr newDynArr(const size_t elementSize);
void freeDynArr(DynArr *arr);
void popDA(DynArr *arr);
void appendDA(DynArr *arr, const void *element);
void *atDA(const DynArr *arr, const size_t index);
void insertDA(DynArr *arr, const size_t index, const void *element);
void removeDA(DynArr *arr, const size_t index);
bool containsDA(const DynArr *arr, const void *element);
int lenDA(const DynArr *arr);

#endif
