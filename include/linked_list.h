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
 * `LinkedList list = LinkedList_new(sizeof(int));` .
 * WARNING: Be sure to call LinkedList_free() to avoid memory leaks.
 */
LinkedList LinkedList_new(const size_t elementSize);

/**
 * Frees the memory allocated to a LinkedList and
 * sets the length to 0.
 */
void LinkedList_free(LinkedList *list);

/**
 * Adds the given element to the end of the given LinkedList.
 */
void LinkedList_append(LinkedList *list, void *element);

/**
 * Adds the given element to the beginning of the given LinkedList.
 */
void LinkedList_prepend(LinkedList *list, void *element);

/**
 * Adds the given element at the given index.
 * Shifts elements to the right as needed.
 */
void LinkedList_insert(LinkedList *list, void *element, const size_t index);

/**
 * Removes the element at the given index.
 * Shifts elements to the left as needed.
 */
void LinkedList_remove(LinkedList *list, const size_t element);

#endif
