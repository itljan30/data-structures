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

int main(void) {
    firstAppend();
    firstPrepend();
}
