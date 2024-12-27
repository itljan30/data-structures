#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "dyn_arr.h"
#include "callbacks.h"
#include "iterator.h"

typedef struct {
    void *key;
    void *value;
} KeyValue;

/**
 * Returns a pointer to a KeyValue pair with the given key and value.
 * WARNING: Make sure to call KeyValue_free() or KeyValue_destroy() to avoid memory leaks.
 */
KeyValue *KeyValue_new(void *key, void *value);

/**
 * Frees memory allocated to the KeyValue.
 * WARNING: Does not free memory of data held within.
 */
void KeyValue_free(KeyValue *pair);

/**
 * Frees memory allocated to the KeyValue as well as all data held within.
 * NOTE: freeKey and freeValue must be in form `void freeFunc(void *element)`.
 * NOTE: Does not free key or value if NULL.
 */
void KeyValue_destroy(KeyValue *pair, FreeFunc freeKey, FreeFunc freeValue);

typedef struct {
    // a DynArr of LinkedList whose data is KeyValuePair
    DynArr *map;
    size_t usedBuckets;
    size_t length;
    size_t loadFactor;
    size_t keySize;
    CompareFunc keyCompare;
} HashMap;

/**
 * Returns a pointer to an empty HashMap.
 * WARNING: Make sure to call HashMap_free() or HashMap_destroy to avoid memory leaks.
 */
HashMap *HashMap_new(size_t keySize, CompareFunc keyCompare);

/**
 * Frees memory allocated to the given HashMap.
 * WARNING: Does not free memory of data held within.
 */
void HashMap_free(HashMap *map);

/*
 * Adds the given value to the given HashMap if it does not exist yet,
 * else, updates the value at the given key to the given value. 
 */
void HashMap_set(HashMap *map, void *key, void *value);

/**
 * Returns a pointer to the value at the given key if it exists.
 * Returns NULL if the given key does not exist.
 */
void *HashMap_find(HashMap *map, void *key);

/**
 * Removes the given key from the given HashMap.
 */
void HashMap_remove(HashMap *map, void *key);

/**
 * Frees memory allocated to the given HashMap and all data held within.
 * NOTE: freeKey and freeValuee must be in form `void freeFunc(void *element)`.
 * NOTE: Does not free memory if freeKey or freeValue is NULL.
 */
void HashMap_destroy(HashMap *map, FreeFunc freeKey, FreeFunc freeValue);

Iterator *HashMap_iterData(HashMap *map);

Iterator *HashMap_iterKey(HashMap *map);

void *HashMap_nextData(Iterator *iter);

void *HashMap_nextKey(Iterator *iter);

// TODO void HashMap_removeAndFree(HashMap *map, void *key, FreeFunc freeFunc);

#endif
