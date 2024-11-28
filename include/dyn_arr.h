#ifndef DYN_ARR_H
#define DYN_ARR_H

#include "callbacks.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void *elements;
    size_t capacity;
    size_t length;
    size_t elementSize;
    FreeFunc freeFunc;
} DynArr;

/**
 * Returns an empty dynamically sized array.
 * Example usage: `DynArr *arr = DynArr_new(sizeof(int));` .
 * WARNING: Be sure to call DynArr_free() to avoid memory leaks.
 */
DynArr *DynArr_new(const size_t elementSize, FreeFunc freeFunc);

/**
 * Frees the memory allocated to the given array.
 * Uses `free()` if no custom free function was given during construction.
 *
 * @param arr is assumed to be a DynArr *.
 */
void DynArr_free(void *arr);

/**
 * Removes the final item from the dynamic array.
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
void DynArr_insert(DynArr *arr, const size_t index, const void *element);

/**
 * Removes the element at the given index.
 * Moves elements to the left as needed.
 */
void DynArr_remove(DynArr *arr, const size_t index);

/**
 * Returns true if the given dynamic array has the given element, else returns false.
 */
bool DynArr_contains(const DynArr *arr, const void *element);

/**
 * Returns the length of the given dynamic array.
 */
size_t DynArr_len(const DynArr *arr);

// TODO DynArr_find

/**
 * Returns a newly allocated portion of memory that is double the current capacity.
 */
void *DynArr_resizeNoCopy(DynArr *arr);

/**
 * Returns the capacity of the given DynArr.
 */
size_t DynArr_capacity(DynArr *arr);

#endif
