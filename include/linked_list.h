#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "callbacks.h"

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
 * Uses `free()` if no custom free function was given.
 *
 * @param node is assumed to be a ListNode *.
 */
void ListNode_free(ListNode *node);

void ListNode_destroy(ListNode *node, FreeFunc freeFunc);

typedef struct {
    ListNode *firstNode;
    size_t length;
} LinkedList;

/**
 * Returns an empty linked list.
 * Example usage: 
 * `LinkedList *list = LinkedList_new(sizeof(int));`.
 * WARNING: Be sure to call LinkedList_free() to avoid memory leaks.
 */
LinkedList *LinkedList_new();

/**
 * Frees the memory allocated to the LinkedList.
 * Uses `free()` if no custom free function was given during construction.
 *
 * @param list is assumed to be a LinkedList *.
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

void LinkedList_destroy(LinkedList *list, FreeFunc freeFunc);

// TODO LinkedList_find

#endif
