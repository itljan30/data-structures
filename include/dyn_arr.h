#ifndef DYN_ARR_H
#define DYN_ARR_H

#include "callbacks.h"
#include "iterator.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void *elements;
    size_t capacity;
    size_t length;
} DynArr;

/**
 * Returns an empty dynamically sized array.
 * WARNING: Be sure to call DynArr_free() or DynArr_destroy() to avoid memory leaks.
 */
DynArr *DynArr_new();

/**
 * Frees the memory allocated to the given array.
 * WARNING: Does not free memory for data stored within.
 */
void DynArr_free(DynArr *arr);

/**
 * Removes the final element from the dynamic array.
 */
void DynArr_pop(DynArr *arr);

/**
 * Adds the given element to the end of the dynamic array.
 */
void DynArr_append(DynArr *arr, void *element);

/**
 * Returns a pointer to the element at the given index.
 */
void *DynArr_at(const DynArr *arr, const size_t index);

/**
 * Inserts the given element at the given index.
 * Moves elements to the right as needed.
 */
void DynArr_insert(DynArr *arr, const size_t index, void *element);

/**
 * Removes the element at the given index.
 * Moves elements to the left as needed.
 */
void DynArr_remove(DynArr *arr, const size_t index);

/**
 * Returns true if the given dynamic array has the given element, else returns false.
 * NOTE: compareFunc must be in form `int compareFunc(void *element1, void *element2)`
 */
int DynArr_contains(DynArr *arr, void *element, CompareFunc compareFunc);

/**
 * Returns the length of the given dynamic array.
 */
size_t DynArr_len(const DynArr *arr);

/**
 * Returns a newly allocated portion of memory that is double the current capacity.
 */
void *DynArr_resizeNoCopy(DynArr *arr);

/**
 * Returns the capacity of the given DynArr.
 */
size_t DynArr_capacity(DynArr *arr);

/**
 * Overwrites the element at the given index to be the given element.
 */
void DynArr_set(DynArr *arr, size_t index, void *element);

/**
 * Frees all memory allocated to the DynArr as well as all data stored within.
 * NOTE: freeFunc must be in form `void freeFunc(void *data)`
 */
void DynArr_destroy(void *arr, FreeFunc freeFunc);

Iterator *DynArr_iter(DynArr *arr);

int DynArr_index(DynArr *arr, void *element, CompareFunc compareFunc);

// TODO DynArr_find

#endif
