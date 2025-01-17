#include <assert.h>

#include "dyn_arr.h"
#include "test_struct.h"

void customStructs() {
    DynArr *arr = DynArr_new();
    for (int i = 0; i < 100; i++) {
        TestStruct *testStruct = TestStruct_new();
        DynArr_append(arr, testStruct);
        assert(DynArr_at(arr, i) == testStruct);
    }
    int range = DynArr_len(arr);
    for (int i = 0; i < range; i++) {
        TestStruct_free(DynArr_at(arr, i));
    }
    DynArr_free(arr);
}

void append() {
    DynArr *arr = DynArr_new();
    char value = 'i';
    DynArr_append(arr, &value);
    char *answer = (char*)DynArr_at(arr, 0);
    assert(*answer == 'i');

    char value2 = 'j';
    DynArr_append(arr, &value2);
    char *answer2 = (char*)DynArr_at(arr, 1);
    assert(*answer2 == 'j');

    DynArr_free(arr);
}

void resize() {
    DynArr *arr = DynArr_new();
    for (double i = 0; i < 1000; i++) {
        DynArr_append(arr, &i);
    }
    DynArr_free(arr);
}

// I don't know why I made this test, the whole pop function is just `arr->length--;`
void pop() {
    DynArr *arr = DynArr_new();
    for (long i = 0; i < 10; i++) {
        DynArr_append(arr, &i);
    }
    DynArr_pop(arr);
    assert(DynArr_len(arr) == 9);
    DynArr_free(arr);
}

void at() {
    DynArr *arr = DynArr_new();
    float value = 3.0;
    DynArr_append(arr, &value);
    float *otherValue = (float*)DynArr_at(arr, 0);
    assert(*otherValue == value);
    DynArr_free(arr);
}

int compareFunc(void *data1, void *data2) {
    return *(int*)data1 - *(int*)data2;
}

void contains() {
    DynArr *arr = DynArr_new();
    for (int i = 2; i < 1000; i *= 2) {
        size_t value = i;
        DynArr_append(arr, &value);
    }

    size_t newValue = 4;
    assert(DynArr_contains(arr, &newValue, compareFunc) == 1);
    DynArr_free(arr);
}

void insertBasic() {
    DynArr *arr = DynArr_new();
    int value = 5;
    DynArr_append(arr, &value);
    int nextValue = 1;
    DynArr_insert(arr, 0, &nextValue);
    int *indexZero = (int*)DynArr_at(arr, 0);
    int *indexOne = (int*)DynArr_at(arr, 1);
    assert(*indexZero == nextValue);
    assert(*indexOne == value);

    DynArr_free(arr);
}

void insert() {
    DynArr *arr = DynArr_new();
    for (int i = 0; i < 99; i++) {
        int value = i;
        DynArr_append(arr, &value);
    }
    int value = 1000;
    DynArr_insert(arr, 50, &value);
    assert(DynArr_len(arr) == 100);
    int *arrFifty = (int*)DynArr_at(arr, 50);
    assert(*arrFifty == value);

    DynArr_free(arr);
}

void remove() {
    DynArr *arr = DynArr_new();

    int buffer[100];
    for (int i = 0; i < 100; i++) {
        buffer[i] = i;
    }
    for (int i = 0; i < 100; i++) {
        DynArr_append(arr, &buffer[i]);
    }

    DynArr_remove(arr, 50);
    int *arrFifty = (int*)DynArr_at(arr, 50);
    assert(*arrFifty != 50);
    assert(*arrFifty == 51);
    assert(DynArr_len(arr) == 99);

    DynArr_free(arr);
}

void destroy() {
    DynArr *arr = DynArr_new();
    for (int i = 0; i < 100; i++) {
        TestStruct *testStruct = TestStruct_new();
        DynArr_append(arr, testStruct);
    }

    DynArr_destroy(arr, TestStruct_free);
}

int main() {
    append();
    at();
    contains();
    resize();
    pop();
    insertBasic();
    insert();
    remove();
    customStructs();
    destroy();
}
