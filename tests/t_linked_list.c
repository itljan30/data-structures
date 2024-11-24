#include "linked_list.h"

void firstAppend() {
    LinkedList list = LinkedList_new(sizeof(long));
    long value = 100;
    LinkedList_append(&list, &value);

    LinkedList_free(&list);
}

void firstPrepend() {
    LinkedList list = LinkedList_new(sizeof(char));
    char value = 'x';
    LinkedList_prepend(&list, &value);

    LinkedList_free(&list);
}

void append() {
    LinkedList list = LinkedList_new(sizeof(double));
    for (double i = 0; i < 1000; i++) {
        LinkedList_append(&list, &i);
    }

    LinkedList_free(&list);
}

void prepend() {
    LinkedList list = LinkedList_new(sizeof(float));
    for (float i = 0; i < 1000; i++) {
        LinkedList_prepend(&list, &i);
    }

    LinkedList_free(&list);
}

int main(void) {
    firstAppend();
    firstPrepend();
    append();
    prepend();
}
