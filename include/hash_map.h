#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "dyn_arr.h"
#include "callbacks.h"

typedef struct {
    void *key;
    void *value;
    CompareFunc keyCompare;
} KeyValue;

/**
 * Returns a pointer to a KeyValue pair with the given key and value.
 * WARNING: Make sure to call `KeyValue_free()` to avoid memory leaks.
 */
KeyValue *KeyValue_new(void *key, void *value, CompareFunc keyCompare);

void KeyValue_free(KeyValue *pair);

void KeyValue_destroy(KeyValue *pair, FreeFunc freeKey, FreeFunc freeValue);

typedef struct {
    // a DynArr of LinkedList whose data is KeyValuePair
    DynArr *map;
    size_t usedBuckets;
    size_t length;
    size_t keySize;
    size_t valueSize;
    size_t loadFactor;
    CompareFunc keyCompare;
} HashMap;

/**
 * Returns a pointer to an empty HashMap.
 * WARNING: Make sure to call `HashMap_free()` to avoid memory leaks.
 *
 * @param keyCompare A comparison function for comparing two keys.
 *                    Function must be in the form `int compareFunc(void *a, void *b)`.
 *                    It should return a negative int if `a < b`, 0 if `a == b`, and a positive int if `a > b`.
 *                    If `compareFunc == NULL`, it will compare values byte by byte.
 * @param freeFunc An optional function that properly frees allocated memory.
 *                 The function is passed directly to the KeyValue struct that holds both the key and value.
 *                 Your function should look like this:
 *                 ```
 *                 void dataFree(void *data) {
 *                 Node *node = (Node*)data;
 *                 KeyType *key = (KeyType*)node->key;
 *                 // call the proper free function on key
 *                 ValueType *value = (ValueType*)node->value;
 *                 // call the proper free function on value
 *                 }
 *                 ```
 */
HashMap *HashMap_new(size_t keySize, size_t valueSize, CompareFunc keyCompare);

/**
 * Frees all memory allocated to the given HashMap.
 */
void HashMap_free(HashMap *map);

/*
 * Adds the given value to the given HashMap if it does not exist yet,
 * otherwise, updates the value at the given key to the given value. 
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

void HashMap_destroy(HashMap *map, FreeFunc freeKey, FreeFunc freeValue);

// TODO void HashMap_removeAndFree(HashMap *map, void *key, FreeFunc freeFunc);

#endif
