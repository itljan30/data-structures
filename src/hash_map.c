#include "hash_map.h"
#include "dyn_arr.h"
#include "linked_list.h"
#include "compare_func.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void rehash(HashMap *map) {
    void *newArray = DynArr_resizeNoCopy(map->map);

    // TODO rehash all the data to fit in this new array

    free(map->map);
    map->map = newArray;
}

// https://en.wikipedia.org/wiki/MurmurHash
// used the psuedocode algorithm section as reference
static uint32_t murmur3_32(void *key, size_t keySize) {
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

HashMap *HashMap_new(size_t elementSize, CompareFunc keyCompareFunc) {
    HashMap *hashMap = (HashMap *)malloc(sizeof(HashMap));
    hashMap->elementSize = elementSize;
    hashMap->loadFactor = .75;
    hashMap->keyCompareFunc = keyCompareFunc;
    hashMap->map = DynArr_new(sizeof(LinkedList));

    return hashMap;
}
