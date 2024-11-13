#include "linked_list.h"

void firstAppend() {
    // TODO
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
