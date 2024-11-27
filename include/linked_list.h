#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "callbacks.h"

typedef struct {
    Node *firstNode;
    size_t length;
    size_t elementSize;
    FreeFunc freeFunc;
} LinkedList;

/**
 * Returns an empty linked list.
 * Example usage: 
 * `LinkedList *list = LinkedList_new(sizeof(int));`.
 * WARNING: Be sure to call LinkedList_free() to avoid memory leaks.
 */
LinkedList *LinkedList_new(const size_t elementSize, FreeFunc freeFunc);

/**
 * Frees the memory allocated to the LinkedList.
 * Uses `free()` if no custom free function was given during construction.
 *
 * @param list is assumed to be a LinkedList *.
 */
void LinkedList_free(void *list);

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
void LinkedList_remove(LinkedList *list, const size_t index);

/**
 * Returns the current length of the given LinkedList.
 */
size_t LinkedList_len(LinkedList *list);

/**
 * Returns the element at the given index;
 */
void *LinkedList_at(LinkedList *list, size_t index);

/**
 * Returns true if the given element is in the given list, else it returns false.
 */
bool LinkedList_contains(LinkedList *list, void *element);

// TODO LinkedList_find

#endif
