#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "dyn_arr.h"
#include "compare_func.h"

typedef int (*CompareFunc)(void *a, void *b);

typedef struct {
    void *key;
    void *value;
} KeyValuePair;

typedef struct {
    // a DynArr of LinkedList whose data is KeyValuePair
    DynArr *map;
    float loadFactor;
    size_t elementSize;
    CompareFunc keyCompareFunc;
} HashMap;

/**
 * Returns a pointer to an empty HashMap.
 * WARNING: Make sure to call `HashMap_free()` to avoid memory leaks.
 *
 * @param keyCompareFunc A comparison function for comparing two keys.
 *                    Function must be in the form `int compareFunc(void *a, void *b)`.
 *                    It should return a negative int if `a < b`, 0 if `a == b`, and a positive int if `a > b`.
 *                    If `compareFunc == NULL`, it will compare values byte by byte.
 */
HashMap *HashMap_new(size_t elementSize, CompareFunc keyCompareFunc);

#endif
