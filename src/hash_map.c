#include "hash_map.h"
#include "dyn_arr.h"
#include "linked_list.h"
#include "callbacks.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Uses murmur hash version 3.
// https://en.wikipedia.org/wiki/MurmurHash for more information.
static uint32_t hashFunction(void *key, size_t keySize) {
    // constants chosen for being good at avoiding collisions I guess
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;

    uint32_t hash = 0x1F346;
    uint32_t k;

    for (size_t i = keySize / 4; i != 0; i--) {
        // sizeof(uint32_t) should always be 4, but it's apparently 
        // more portable and good practice in case it ever changes
        memcpy(&k, key, sizeof(uint32_t));

        // move the pointer 4 bytes over for next iteration
        key += sizeof(uint32_t);
        k *= c1;

        // now we shift left by r1 but don't discard the bits, put them at the end
        // 32 - r1 should put the discarded bits at the lowest bits then we just or
        // our two binary numbers together
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        // ^ is the bitwise XOR operator
        hash ^= k;

        // do the same bit shift rotation thing as before, but on our hash this time
        hash = (hash << r2) | (hash >> (32 - r2));

        hash = (hash * m) + n;
    }
    // now we need to deal with any leftover bits if the keySize isn't divisble by 4
    // basically we just load the final 1-3 bytes into k
    // it does technically load them into k in reverse order though, but something about little-endian or something
    k = 0;
    for (size_t i = keySize % 4; i != 0; i--) {
        // we have 1-3 bytes left that haven't been read
        // so we keep bitshifting k to the left by 8 (one byte) to put it at the end
        // this way k will end up at most 3 bytes long, then we do math with that and the 
        // current hash value that we've calculated
        // bitshift first so that we don't end up with the final 8 bits of k being all 0s in the final iteration
        k <<= 8;
        // key is pointing deep into the given key at the last 1-3 bytes
        // copy the i - 1 byte in key (to 0 index it) into the final byte of k
        // convert &k to a char * so that we go byte by byte (since char is always 1 byte)
        // then go over 3 bytes to get to the final byte of k
        // this way we copy the i - 1 byte of key into the final byte of k
        memcpy((char*)&k + 3, key + (i - 1), 1);
    }
    // now we need to do the math on the final bytes of k, but only if they exist
    if (k != 0) {
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        hash ^= k;
    }

    // these last random numbers seem to be relatively random constants, probably
    // explicitly chosen for how useful they are at avoiding collisions
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

static void setPair(HashMap *map, KeyValue *pair) {
    uint32_t hash = hashFunction(pair->key, map->keySize);
    size_t index = hash % DynArr_capacity(map->map);
    
    if (DynArr_at(map->map, index) == NULL) {
        DynArr_set(map->map, index, LinkedList_new(sizeof(KeyValue)));
        map->usedBuckets++;
    }

    LinkedList_prepend(DynArr_at(map->map, index), pair);
}

static void rehash(HashMap *map) {
    DynArr *tempArr = DynArr_new(sizeof(KeyValue));
    for (int i = 0; i < DynArr_capacity(map->map); i++) {
        LinkedList *list = (LinkedList*)DynArr_at(map->map, i);
        if (list != NULL) {
            ListNode *currentNode = list->firstNode;
            while (currentNode != NULL) {
                DynArr_append(tempArr, currentNode->data);
                currentNode = currentNode->nextNode;
            }
        }
    }

    // get this before it gets reset by DynArr_resizeNoCopy();
    size_t range = DynArr_len(map->map);

    void *newElements = DynArr_resizeNoCopy(map->map);
    map->usedBuckets = 0;

    for (int i = 0; i < range; i++) {
        LinkedList *list = *((void**)map->map->elements + i);
        if (list != NULL) {
            LinkedList_free(list);
        }
    }

    free(map->map->elements);
    map->map->elements = newElements;

    for (int i = 0; i < DynArr_capacity(map->map); i++) {
        DynArr_append(map->map, NULL);
    }

    for (int i = 0; i < DynArr_len(tempArr); i++) {
        setPair(map, DynArr_at(tempArr, i));
    }

    DynArr_free(tempArr);
}

KeyValue *KeyValue_new(void *key, void *value, CompareFunc keyCompare) {
    KeyValue *pair = (KeyValue*)malloc(sizeof(KeyValue));
    if (pair == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    pair->key = key;
    pair->value = value;
    pair->keyCompare = keyCompare;

    return pair;
}

void KeyValue_free(KeyValue *pair) {
    free(pair);
}

HashMap *HashMap_new(size_t keySize, size_t valueSize, CompareFunc keyCompare) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->map = DynArr_new(sizeof(LinkedList));
    map->length = 0;
    map->usedBuckets = 0;
    map->loadFactor = 75;
    map->keySize = keySize;
    map->valueSize = valueSize;
    map->keyCompare = keyCompare;

    return map;
}

void HashMap_free(HashMap *map) {
    for (int i = 0; i < DynArr_capacity(map->map); i++) {
        LinkedList *list = DynArr_at(map->map, i);
        if (list != NULL) {
            ListNode *currentNode = list->firstNode;
            while (currentNode != NULL) {
                KeyValue_free(currentNode->data);

                currentNode = currentNode->nextNode;
            }
            LinkedList_free(list);
        }
    }
    DynArr_free(map->map);
    free(map);
}

void *HashMap_find(HashMap *map, void *key) {
    size_t index = hashFunction(key, map->keySize) % map->map->capacity;

    LinkedList *list = (LinkedList*)DynArr_at(map->map, index);
    if (list == NULL) {
        return NULL;
    }
    ListNode *currentNode = list->firstNode;
    while (currentNode != NULL) {
        if (currentNode != NULL) {
            KeyValue *pair = (KeyValue*)currentNode->data;
            int comparison = (pair->keyCompare != NULL) ? pair->keyCompare(key, pair->key)
                                                            : defaultCompare(key, pair->key, map->keySize);
            if (comparison == 0) {
                return pair->value;
            }
        }
        currentNode = currentNode->nextNode;
    }
    return NULL;
}

void HashMap_set(HashMap *map, void *key, void *value) {
    if (key == NULL) {
        printf("ERROR: HashMap was given a NULL key\n");
        exit(EXIT_FAILURE);
    }

    if (DynArr_capacity(map->map) == 0) {
        rehash(map);
    }

    while (map->usedBuckets * 100 / DynArr_capacity(map->map) > map->loadFactor) {
        rehash(map);
    }

    void *prevValue = HashMap_find(map, key);

    size_t index = hashFunction(key, map->keySize) % DynArr_capacity(map->map);
    
    if (DynArr_at(map->map, index) == NULL) {
        DynArr_set(map->map, index, LinkedList_new(sizeof(KeyValue)));
        map->usedBuckets++;
    }

    if (prevValue == NULL) {
        KeyValue *pair = KeyValue_new(key, value, map->keyCompare);
        LinkedList_prepend(DynArr_at(map->map, index), pair);
        map->length++;
    }
    else {
        prevValue = value;
    }
}

void HashMap_remove(HashMap *map, void *key) {
    size_t index = hashFunction(key, map->keySize) % map->map->capacity;

    LinkedList *list = (LinkedList*)DynArr_at(map->map, index);
    if (list == NULL) {
        return;
    }
    int i = 0;
    ListNode *currentNode = list->firstNode;
    while (currentNode != NULL) {
        if (currentNode != NULL) {
            KeyValue *pair = (KeyValue*)currentNode->data;
            int comparison = (pair->keyCompare != NULL) ? pair->keyCompare(key, pair->key)
                                                            : defaultCompare(key, pair->key, map->keySize);
            if (comparison == 0) {
                LinkedList_remove(list, i);
                map->length--;
                KeyValue_free(pair);
                return;
            }
        }
        i++;
        currentNode = currentNode->nextNode;
    }
}
