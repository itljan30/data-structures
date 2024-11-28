#include "dyn_arr2.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        memcpy(newArray + (i * sizeof(void*)), arr->elements + (i * sizeof(void*)), sizeof(void*));
    }

    free(arr->elements);
    arr->elements = newArray;
}

DynArr *DynArr_new(size_t elementSize) {
    DynArr *arr = malloc(sizeof(DynArr));
    arr->elements = NULL;
    arr->capacity = 0;
    arr->length = 0;
    arr->elementSize = elementSize;

    return arr;
}

void DynArr_free(DynArr *arr) {
    free(arr->elements);
    free(arr);
}

void DynArr_pop(DynArr *arr) {
    if (arr->length == 0) {
        printf("ERROR: Attempted to pop an empty DynArr\n");
        exit(EXIT_FAILURE);
    }
    arr->length--;
}

void DynArr_append(DynArr *arr, void *element) {
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    memcpy(arr->elements + (arr->length * sizeof(void*)), element, sizeof(void*));
    arr->length++;
}

void DynArr_insert(DynArr *arr, size_t index, void *element) {
    if (index > arr->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    // move all elements from index onward one to the right
    for (size_t i = index; i < arr->length - 1; i++) {
        memcpy(arr->elements + (index * sizeof(void*)), arr->elements + ((index + 1) * sizeof(void*)), sizeof(void*));
    }
    memcpy(arr->elements + (index * sizeof(void*)), element, sizeof(void*));
    arr->length++;
}

void *DynArr_at(DynArr *arr, size_t index) {
    return arr->elements + (index * sizeof(void*));
}

size_t DynArr_len(DynArr *arr) {
    return arr->length;
}


size_t DynArr_capacity(DynArr *arr) {
    return arr->capacity;
}
