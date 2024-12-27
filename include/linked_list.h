#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "callbacks.h"
#include "iterator.h"

typedef struct ListNode {
    void *data;
    struct ListNode *nextNode;
} ListNode;

/**
 * Returns a node with the given data and next node. 
 * NOTE: If you don't have a next node, put NULL.
 */
ListNode *ListNode_new(void *data, ListNode *nextNode);

/**
 * Frees the memory allocated to the node.
 * WARNING: Does not free the data stored inside.
 */
void ListNode_free(ListNode *node);

/**
 * Frees the memory allocated to the node as well as all data stored within.
 * NOTE: freeFunc must be in form `void freeFunc(void *element)`
 */
void ListNode_destroy(ListNode *node, FreeFunc freeFunc);

typedef struct {
    ListNode *firstNode;
    size_t length;
} LinkedList;

/**
 * Returns an empty linked list.
 * Example usage: `LinkedList *list = LinkedList_new();`.
 * WARNING: Be sure to call LinkedList_free() or LinkedList_destroy to avoid memory leaks.
 */
LinkedList *LinkedList_new();

/**
 * Frees the memory allocated to the LinkedList.
 * WARNING: Does not free memory of data stored within.
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
int LinkedList_contains(LinkedList *list, void *element, CompareFunc compareFunc);

/**
 * Frees the memory allocated to the LinkedList as well as all data stored within.
 * NOTE: freeFunc must be in form `void freeFunc(void *element)`
 */
void LinkedList_destroy(LinkedList *list, FreeFunc freeFunc);

Iterator *LinkedList_iter(LinkedList *list);

int LinkedList_find(LinkedList *list, void *data, CompareFunc compareFunc);

#endif
