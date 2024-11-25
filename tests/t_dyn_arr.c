#include <assert.h>

#include "dyn_arr.h"

void append() {
    DynArr *arr = DynArr_new(sizeof(char));
    char value = 'i';
    DynArr_append(arr, &value);
    char *answer = DynArr_at(arr, 0);
    assert(*answer == 'i');

    char value2 = 'j';
    DynArr_append(arr, &value2);
    char *answer2 = DynArr_at(arr, 1);
    assert(*answer2 == 'j');

    DynArr_free(arr);
}

void resize() {
    DynArr *arr = DynArr_new(sizeof(double));
    for (double i = 0; i < 1000; i++) {
        DynArr_append(arr, &i);
    }
    DynArr_free(arr);
}

// I don't know why I made this test, the whole pop function is just `arr->length--;`
void pop() {
    DynArr *arr = DynArr_new(sizeof(long));
    for (long i = 0; i < 10; i++) {
        DynArr_append(arr, &i);
    }
    DynArr_pop(arr);
    assert(DynArr_len(arr) == 9);
    DynArr_free(arr);
}

void at() {
    DynArr *arr = DynArr_new(sizeof(float));
    float value = 3.0;
    DynArr_append(arr, &value);
    float *otherValue = DynArr_at(arr, 0);
    assert(*otherValue == value);
    DynArr_free(arr);
}

void contains() {
    DynArr *arr = DynArr_new(sizeof(size_t));
    for (int i = 2; i < 1000; i *= 2) {
        size_t value = i;
        DynArr_append(arr, &value);
    }

    size_t newValue = 4;
    assert(DynArr_contains(arr, &newValue) == 1);
    DynArr_free(arr);
}

void insertBasic() {
    DynArr *arr = DynArr_new(sizeof(int));
    int value = 5;
    DynArr_append(arr, &value);
    int nextValue = 1;
    DynArr_insert(arr, 0, &nextValue);
    int *indexZero = DynArr_at(arr, 0);
    int *indexOne = DynArr_at(arr, 1);
    assert(*indexZero == nextValue);
    assert(*indexOne == value);

    DynArr_free(arr);
}

void insert() {
    DynArr *arr = DynArr_new(sizeof(int));
    for (int i = 0; i < 99; i++) {
        DynArr_append(arr, &i);
    }
    int value = 1000;
    DynArr_insert(arr, 50, &value);
    assert(DynArr_len(arr) == 100);
    int *arrFifty = DynArr_at(arr, 50);
    assert(*arrFifty == value);

    DynArr_free(arr);
}

void remove() {
    DynArr *arr = DynArr_new(sizeof(int));

    for (int i = 0; i < 100; i++) {
        DynArr_append(arr, &i);
    }
    DynArr_remove(arr, 50);
    int *arrFifty = DynArr_at(arr, 50);
    assert(*arrFifty == 51);
    assert(DynArr_len(arr) == 99);

    DynArr_free(arr);
}

int main(void) {
    append();
    at();
    contains();
    resize();
    pop();
    insertBasic();
    insert();
    remove();
}
