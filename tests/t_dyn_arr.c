#include <assert.h>
#include <stdio.h>

#include "dyn_arr.h"

void append() {
    DynArr arr = newDynArr(sizeof(char));
    char value = 'i';
    appendDA(&arr, &value);
    char *answer = atDA(&arr, 0);
    assert(*answer == 'i');
}

void pop() {
    DynArr arr = newDynArr(sizeof(long));
    for (long i = 0; i < 10; i++) {
        appendDA(&arr, &i);
    }
    popDA(&arr);
    assert(lenDA(&arr) == 9);
}

void contains() {
    DynArr arr = newDynArr(sizeof(float));
    float value = 3.0;
    appendDA(&arr, &value);
    float *otherValue = atDA(&arr, 0);

    assert(*otherValue == value);
    printf("containsDA succeeded\n");
}

int main(void) {
    contains();
    pop();

    return 0;
}
