#include "linked_list.h"

void firstAppend() {
    LinkedList list = newLinkedList(sizeof(long));
    long value = 100;
    appendLL(&list, &value);

    freeLinkedList(&list);
}

void firstPrepend() {
    LinkedList list = newLinkedList(sizeof(char));
    char value = 'x';
    prependLL(&list, &value);

    freeLinkedList(&list);
}

void append() {
    LinkedList list = newLinkedList(sizeof(double));
    for (double i = 0; i < 1000; i++) {
        appendLL(&list, &i);
    }

    freeLinkedList(&list);
}

void prepend() {
    LinkedList list = newLinkedList(sizeof(float));
    for (float i = 0; i < 1000; i++) {
        prependLL(&list, &i);
    }

    freeLinkedList(&list);
}

int main(void) {
    firstAppend();
    firstPrepend();
    append();
    prepend();
}
