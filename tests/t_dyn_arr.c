#include <assert.h>

#include "dyn_arr.h"

void append() {
    DynArr arr = newDynArr(sizeof(char));
    char value = 'i';
    appendDA(&arr, &value);
    char *answer = atDA(&arr, 0);
    assert(*answer == 'i');

    char value2 = 'j';
    appendDA(&arr, &value2);
    char *answer2 = atDA(&arr, 1);
    assert(*answer2 == 'j');

    freeDynArr(&arr);
}

void resize() {
    DynArr arr = newDynArr(sizeof(double));
    for (double i = 0; i < 1000; i++) {
        appendDA(&arr, &i);
    }
    freeDynArr(&arr);
}

// I don't know why I made this test
void pop() {
    DynArr arr = newDynArr(sizeof(long));
    for (long i = 0; i < 10; i++) {
        appendDA(&arr, &i);
    }
    popDA(&arr);
    assert(lenDA(&arr) == 9);
    freeDynArr(&arr);
}

void at() {
    DynArr arr = newDynArr(sizeof(float));
    float value = 3.0;
    appendDA(&arr, &value);
    float *otherValue = atDA(&arr, 0);
    assert(*otherValue == value);
    freeDynArr(&arr);
}

void contains() {
    DynArr arr = newDynArr(sizeof(size_t));
    for (int i = 2; i < 1000; i *= 2) {
        size_t value = i;
        appendDA(&arr, &value);
    }

    size_t newValue = 4;
    assert(containsDA(&arr, &newValue) == 1);
    freeDynArr(&arr);
}

void insert() {
    // TODO
}

void remove() {
    // TODO
}

int main(void) {
    append();
    at();
    contains();
    resize();
    pop();
    insert();
    remove();
}
