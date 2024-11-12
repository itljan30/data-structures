#include "dyn_arr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void resize(DynArr *arr) {
    arr->capacity *= 2;

    void *newArray = malloc(arr->elementSize * arr->capacity);
    if (newArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < arr->length; i++) {
        memcpy((char*)newArray + (i * arr->elementSize), 
               (char*) arr->elements + (i * arr->elementSize), arr->elementSize);
    }

    free(arr->elements);
    arr->elements = newArray;
}

DynArr newDynArr(size_t elementSize) {
    void *elements = malloc(5 * sizeof(elementSize));
    DynArr list = {elements, 5, 0, elementSize};
    return list;
}

void freeDynArr(DynArr *arr) {
    free(arr->elements);
}

void popDA(DynArr *arr) {
    if (arr->length != 0) {
        arr->length--;
    }
    else {
        perror("Attempted to pop an empty dynamic array");
        exit(EXIT_FAILURE);
    }
}

void appendDA(DynArr *arr, void *element) {
    if (arr->length >= arr->capacity - 1) {
        resize(arr);
    }
    memcpy((char*)arr->elements + (arr->length * arr->elementSize), (char*)element, arr->elementSize);
    arr->length++;
}

void *atDA(DynArr *arr, size_t index) {
    if (index >= arr->length) {
        perror("Index out of range");
        exit(EXIT_FAILURE);
    }
    return (char*)arr->elements + (index * arr->elementSize);
}
