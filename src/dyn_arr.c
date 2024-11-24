#include "dyn_arr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void resize(DynArr *arr) {
    if (arr->capacity == 0) {
        arr->capacity = 1;
    }
    else {
        arr->capacity *= 2;
    }

    void *newArray = malloc(arr->elementSize * arr->capacity);
    if (newArray == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < arr->length; i++) {
        memcpy(newArray + (i * arr->elementSize), arr->elements + (i * arr->elementSize), arr->elementSize);
    }

    free(arr->elements);
    arr->elements = newArray;
}

DynArr DynArr_new(const size_t elementSize) {
    DynArr arr = {NULL, 0, 0, elementSize};
    return arr;
}

void DynArr_free(DynArr *arr) {
    free(arr->elements);
    arr->length = 0;
    arr->capacity = 0;
}

void DynArr_pop(DynArr *arr) {
    if (arr->length == 0) {
        printf("Error: Attempted to pop an empty dynamic array\n");
        exit(EXIT_FAILURE);
    }
    arr->length--;
}

void DynArr_append(DynArr *arr, const void *element) {
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    memcpy(arr->elements + (arr->length * arr->elementSize), element, arr->elementSize);
    arr->length++;
}

void *DynArr_at(const DynArr *arr, const size_t index) {
    if (index >= arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return (char*)arr->elements + (index * arr->elementSize);
}

void DynArr_insert(DynArr *arr, const size_t index, const void *element) {
    if (index > arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    for (int i = arr->length; i > index; i--) {
        memcpy(arr->elements + (i * arr->elementSize), arr->elements + ((i - 1) * arr->elementSize), arr->elementSize);
    }
    memcpy(arr->elements + (index * arr->elementSize), element, arr->elementSize);
    arr->length++;
}

void DynArr_remove(DynArr *arr, const size_t index) {
    if (index > arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    for (int i = index; i < arr->length - 1; i++) {
        memcpy(arr->elements + (i * arr->elementSize), arr->elements + ((i + 1) * arr->elementSize), arr->elementSize);
    }
    arr->length--;
}

bool DynArr_contains(const DynArr *arr, const void *element) {
    for (int i = 0; i < arr->length; i++) {
        const void *currentElement = (char*)arr->elements + (i * arr->elementSize);
        if (memcmp(currentElement, element, arr->elementSize) == 0) {
            return true;
        }
    }
    return false;
}

size_t DynArr_len(const DynArr *arr) {
    return arr->length;
}
