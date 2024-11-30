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

DynArr *DynArr_new(size_t elementSize) {
    DynArr *arr = malloc(sizeof(DynArr));
    arr->elements = NULL;
    arr->capacity = 0;
    arr->length = 0;
    arr->elementSize = elementSize;

    return arr;
}

void DynArr_free(DynArr *arr) {
    if (arr->elements != NULL) {
        free(arr->elements);
    }
    free(arr);
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

int DynArr_contains(const DynArr *arr, const void *element) {
    if (arr->length == 0) {
        return false;
    }
    for (int i = 0; i < arr->length; i++) {
        void *currentElement = *((void**)arr->elements + i);
        if (memcmp(currentElement, element, arr->elementSize) == 0) {
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
