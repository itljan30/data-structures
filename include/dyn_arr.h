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

/**
 * Returns an empty dynamically sized array.
 * Example usage: 
 * `DynArr arr = newDynArr(sizeof(int));` .
 * WARNING: Be sure to call freeDynArr() to avoid memory leaks.
 */
DynArr newDynArr(const size_t elementSize);

/**
 * Frees the memory allocated to the array 
 * and sets the arrays length and capacity to 0.
 */
void freeDynArr(DynArr *arr);

/**
 * Removes the final item from the dynamic array.
 */
void popDA(DynArr *arr);

/**
 * Places the given element at the end of the dynamic array.
 */
void appendDA(DynArr *arr, const void *element);

/**
 * Returns a pointer to the element at the given index.
 */
void *atDA(const DynArr *arr, const size_t index);

/**
 * TODO Add implemenetation.
 */
void insertDA(DynArr *arr, const size_t index, const void *element);

/**
 * TODO Add implemenetation.
 */
void removeDA(DynArr *arr, const size_t index);

/**
 * Returns the index of the given value if it exists, else it returns -1.
 */
size_t containsDA(const DynArr *arr, const void *element);

/**
 * Returns the length of the dynamic array.
 */
size_t lenDA(const DynArr *arr);

#endif
