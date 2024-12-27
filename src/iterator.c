#include "iterator.h"

#include <stdbool.h>

void Iterator_free(Iterator *iter) {
    free(iter);
}

void Iterator_destroy(Iterator *iter, FreeFunc freeFunc) {
    iter->destroyFunc(iter->dataStruct, freeFunc);
    free(iter);
}

void Iterator_begin(Iterator *iter) {
    iter->bucketIndex = 0;
    iter->index = 0;
    iter->currentNode = NULL;
}

void Iterator_end(Iterator *iter) {
    iter->index = iter->length - 1;
}

bool Iterator_hasNext(Iterator *iter) {
    return (iter->index + 1 < iter->length);
}

int Iterator_len(Iterator *iter) {
    return iter->length;
}

void *Iterator_next(Iterator *iter) {
    return iter->next(iter);
}
