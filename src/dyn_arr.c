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
        memcpy((char*)newArray + (i * arr->elementSize), 
               (char*) arr->elements + (i * arr->elementSize), arr->elementSize);
    }

    free(arr->elements);
    arr->elements = newArray;
}

DynArr newDynArr(const size_t elementSize) {
    DynArr arr = {NULL, 0, 0, elementSize};
    return arr;
}

void freeDynArr(DynArr *arr) {
    free(arr->elements);
    arr->length = 0;
    arr->capacity = 0;
}

void popDA(DynArr *arr) {
    if (arr->length == 0) {
        printf("Error: Attempted to pop an empty dynamic array\n");
        exit(EXIT_FAILURE);
    }
    arr->length--;
}

void appendDA(DynArr *arr, const void *element) {
    if (arr->length >= arr->capacity) {
        resize(arr);
    }
    memcpy(arr->elements + (arr->length * arr->elementSize), element, arr->elementSize);
    arr->length++;
}

void *atDA(const DynArr *arr, const size_t index) {
    if (index < 0 || index >= arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return (char*)arr->elements + (index * arr->elementSize);
}

void insertDA(DynArr *arr, const size_t index, const void *element) {
    if (index < 0 || index >= arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    // TODO
}

void removeDA(DynArr *arr, const size_t index) {
    if (index < 0 || index >= arr->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    // TODO
}

size_t containsDA(const DynArr *arr, const void *element) {
    for (int i = 0; i < arr->length; i++) {
        const void *currentElement = (char*)arr->elements + (i * arr->elementSize);
        if (memcmp(currentElement, element, arr->elementSize) == 0) {
            return i;
        }
    }
    return -1;
}

size_t lenDA(const DynArr *arr) {
    return arr->length;
}
