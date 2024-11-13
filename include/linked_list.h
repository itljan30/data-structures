#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

#include "node.h"

typedef struct {
    Node *firstNode;
    size_t length;
    const size_t elementSize;
} LinkedList;

/**
 * Returns an empty linked list.
 * Example usage: 
 * `LinkedList list = newLinkedList(sizeof(int));` .
 * WARNING: Be sure to call freeLinkedList() to avoid memory leaks.
 */
LinkedList newLinkedList(const size_t elementSize);

/**
 * Frees the memory allocated to a LinkedList and
 * sets the length to 0.
 */
void freeLinkedList(LinkedList *list);

/**
 * Adds the given element to the end of the given LinkedList.
 */
void appendLL(LinkedList *list, void *element);

/**
 * Adds the given element to the beginning of the given LinkedList.
 */
void prependLL(LinkedList *list, void *element);

#endif
