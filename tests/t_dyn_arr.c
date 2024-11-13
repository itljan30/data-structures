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

void contains() {
    DynArr arr = newDynArr(sizeof(float));
    float value = 3.0;
    appendDA(&arr, &value);
    float *otherValue = atDA(&arr, 0);
    assert(*otherValue == value);
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
    contains();
    resize();
    pop();
    insert();
    remove();
}
