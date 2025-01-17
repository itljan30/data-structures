#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Iterator {
    void *dataStruct;
    void *currentNode;
    size_t length;
    size_t index;
    size_t bucketIndex;

    void *(*next)(struct Iterator *iter);
} Iterator;

void Iterator_free(Iterator *iter);

void *Iterator_next(Iterator *iter);

int Iterator_len(Iterator *iter);

void Iterator_begin(Iterator *iter);

void Iterator_end(Iterator *iter);

bool Iterator_hasNext(Iterator *iter);

// TODO
// void Iterator_map(Iterator *iter);

#endif
