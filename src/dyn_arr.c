#include "dyn_arr.h"
#include "iterator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void *DynArr_next(Iterator *iter) {
    void *element = DynArr_at(iter->dataStruct, iter->index);
    iter->index++;
    return element;
}

static void resize(DynArr *arr) {
    if (arr->capacity == 0) {
        arr->capacity = 1;
    }
    else {
        arr->capacity *= 2;
    }

    void *newArray = malloc(sizeof(void*) * arr->capacity);
    if (newArray == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < arr->length; i++) {
        *((void**)newArray + i) = *((void**)arr->elements + i);
    }

    free(arr->elements);
    arr->elements = newArray;
}



DynArr *DynArr_new() {
    DynArr *arr = malloc(sizeof(DynArr));
    arr->elements = NULL;
    arr->capacity = 0;
    arr->length = 0;

    return arr;
}

void DynArr_free(DynArr *arr) {
    DynArr_destroy(arr, NULL);
}

void DynArr_pop(DynArr *arr) {
    if (arr->length == 0) {
        printf("ERROR: Attempted to pop an empty dynamic array\n");
        exit(EXIT_FAILURE);
    }
    arr->length--;
}

void DynArr_append(DynArr *arr, void *element) {
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    *((void**)arr->elements + arr->length) = element;
    arr->length++;
}

void *DynArr_at(const DynArr *arr, const size_t index) {
    if (index >= arr->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return *((void**)arr->elements + index);
}

void DynArr_insert(DynArr *arr, const size_t index, void *element) {
    if (index > arr->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    // move all elements from index onward one to the right
    for (size_t i = arr->length; i > index; i--) {
        *((void**)arr->elements + i) = *((void**)arr->elements + (i - 1));
    }
    *((void**)arr->elements + index) = element;
    arr->length++;
}

void DynArr_remove(DynArr *arr, const size_t index) {
    if (index >= arr->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    // move elements after removed element one left
    for (int i = index; i < arr->length - 1; i++) {
        *((void**)arr->elements + i) = *((void**)arr->elements + (i + 1));
    }
    arr->length--;
}

int DynArr_contains(DynArr *arr, void *element, CompareFunc compareFunc) {
    if (arr->length == 0) {
        return false;
    }

    for (int i = 0; i < arr->length; i++) {
        void *currentElement = *((void**)arr->elements + i);
        if (compareFunc(currentElement, element) == 0) {
            return true;
        }
    }
    return false;
}

size_t DynArr_len(const DynArr *arr) {
    return arr->length;
}

void *DynArr_resizeNoCopy(DynArr *arr) {
    if (arr->capacity == 0) {
        arr->capacity = 1;
    }
    else {
        arr->capacity *= 2;
    }

    void *newArray = malloc(sizeof(void*) * arr->capacity);
    if (newArray == NULL) {
        printf("ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    arr->length = 0;

    return newArray;
}

size_t DynArr_capacity(DynArr *arr) {
    return arr->capacity;
}

void DynArr_set(DynArr *arr, size_t index, void *element) {
    *((void**)arr->elements + index) = element;
}

void DynArr_destroy(void *data, FreeFunc freeFunc) {
    DynArr *arr = (DynArr*)data;

    if (freeFunc != NULL) {
        for (int i = 0; i < arr->length; i++) {
            freeFunc(DynArr_at(arr, i));
        }
    }

    free(arr->elements);
    free(arr);
}

Iterator *DynArr_iter(DynArr *arr) {
    Iterator *iter = malloc(sizeof(Iterator));
    iter->dataStruct = arr;
    iter->destroyFunc = DynArr_destroy;
    iter->length = arr->length;
    iter->index = 0;
    iter->next = DynArr_next;
    iter->currentNode = NULL;
    iter->bucketIndex = 0;

    return iter;
}

int DynArr_index(DynArr *arr, void *element, CompareFunc compareFunc) {
    for (int i = 0; i < arr->length; i++) {
        void *data = DynArr_at(arr, i);
        if (compareFunc(data, element) == 0) {
            return i;
        }
    }

    return -1;
}

DynArr *DynArr_clone(DynArr *arr) {
    Iterator *iter = DynArr_iter(arr);
    DynArr *newArr = DynArr_new();
    while (Iterator_hasNext(iter)) {
        DynArr_append(newArr, Iterator_next(iter));
    }

    return newArr;
}
