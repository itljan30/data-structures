#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

#include "node.h"

typedef struct {
    Node *firstNode;
    size_t elementSize;
    size_t length;
} LinkedList;

LinkedList newLinkedList(const size_t elementSize);
void freeLinkedList(LinkedList *list);
void appendLL(LinkedList *list, void *element);
void prependLL(LinkedList *list, void *element);

#endif
