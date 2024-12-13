#include "linked_list.h"
#include "test_struct.h"

#include <assert.h>
#include <stdbool.h>

void firstAppend() {
    LinkedList *list = LinkedList_new(sizeof(long));
    long value = 100;
    LinkedList_append(list, &value);

    long *listAtZero = LinkedList_at(list, 0);
    assert(*listAtZero == value);
    assert(LinkedList_len(list) == 1);

    LinkedList_free(list);
}

void firstPrepend() {
    LinkedList *list = LinkedList_new(sizeof(char));
    char value = 'x';
    LinkedList_prepend(list, &value);

    char *listAtZero = LinkedList_at(list, 0);
    assert(*listAtZero == value);
    assert(LinkedList_len(list) == 1);

    LinkedList_free(list);
}

void append() {
    LinkedList *list = LinkedList_new(sizeof(double));
    double buffer[1000];
    for (double i = 0; i < 1000; i++) {
        buffer[(int)i] = i;
    }
    for (double i = 0; i < 1000; i++) {
        LinkedList_append(list, &buffer[(int)i]);
    }

    double *listAtHundred = LinkedList_at(list, 100);
    assert(*listAtHundred == 100);
    assert(LinkedList_len(list) == 1000);

    LinkedList_free(list);
}

void prepend() {
    LinkedList *list = LinkedList_new(sizeof(float));
    float buffer[1000];
    for (float i = 0; i < 1000; i++) {
        buffer[(int)i] = i;
    }
    for (float i = 0; i < 1000; i++) {
        LinkedList_prepend(list, &buffer[(int)i]);
    }

    float *listAtHundred = LinkedList_at(list, 100);
    assert(*listAtHundred == 899);
    assert(LinkedList_len(list) == 1000);

    LinkedList_free(list);
}

void insert() {
    LinkedList *list = LinkedList_new(sizeof(int));
    int buffer[100];
    for (int i = 0; i < 100; i++) {
        buffer[i] = i;
    }
    for (int i = 0; i < 100; i++) {
        LinkedList_append(list, &buffer[i]);
    }

    int value = 5;

    LinkedList_insert(list, &value, 50);

    int *listAtFifty = LinkedList_at(list, 50);
    assert(*listAtFifty == 5);
    assert(LinkedList_len(list) == 101);

    LinkedList_free(list);
}

void remove() {
    LinkedList *list = LinkedList_new(sizeof(int));
    int buffer[100];
    for (int i = 0; i < 100; i++) {
        buffer[i] = i;
    }
    for (int i = 0; i < 100; i++) {
        LinkedList_append(list, &buffer[i]);
    }
    int value = 5;

    LinkedList_remove(list, 50);

    int *listAtFifty = LinkedList_at(list, 50);
    assert(*listAtFifty == 51);
    assert(LinkedList_len(list) == 99);

    LinkedList_free(list);
}

void contains() {
    LinkedList *list = LinkedList_new(sizeof(int));
    int buffer[100];
    for (int i = 0; i < 100; i++) {
        buffer[i] = i;
    }
    for (int i = 0; i < 100; i++) {
        LinkedList_append(list, &buffer[i]);
    }

    int value = 10;
    int secondValue = 99;
    int thirdValue = 100;
    assert(LinkedList_contains(list, &value) == true);
    assert(LinkedList_contains(list, &secondValue) == true);
    assert(LinkedList_contains(list, &thirdValue) == false);

    LinkedList_free(list);
}

void destroy() {
    LinkedList *list = LinkedList_new(sizeof(TestStruct));
    for (int i = 0; i < 100; i++) {
        TestStruct *testStruct = TestStruct_new();
        LinkedList_prepend(list, testStruct);
    }

    LinkedList_destroy(list, TestStruct_free);
}

int main(void) {
    firstAppend();
    firstPrepend();
    append();
    prepend();
    insert();
    remove();
    contains();
    destroy();
}
