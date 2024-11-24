#include "linked_list.h"
#include "node.h"

#include <stdlib.h>
#include <stdbool.h>

LinkedList LinkedList_new(const size_t elementSize) {
    LinkedList list = {NULL, elementSize, 0};
    return list;
}

void LinkedList_free(LinkedList *list) {
    if (list->firstNode == NULL) {
        return;
    }
    Node *currentNode = list->firstNode;
    Node *nextNode = NULL;
    while (true) {
        if (currentNode->nextNode == NULL) {
            freeNode(currentNode);
            break;
        }
        nextNode = currentNode->nextNode;
        freeNode(currentNode);
        currentNode = nextNode;
    }
    list->firstNode = NULL;
    list->length = 0;
}

void LinkedList_append(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = newNode(list->elementSize, element, NULL);
    }
    else {
        Node *node = newNode(list->elementSize, element, NULL);

        Node *currentNode = list->firstNode;
        Node *nextNode = NULL;
        for (int i = 0; i < list->length; i++) {
            nextNode = currentNode->nextNode;
            if (nextNode == NULL) {
                currentNode->nextNode = node;
                break;
            }
            currentNode = nextNode;
        }
    }
    list->length++;
}

void LinkedList_prepend(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = newNode(list->elementSize, element, NULL);
    }
    else {
        list->firstNode = newNode(list->elementSize, element, list->firstNode);
    }
    list->length++;
}

void LinkedList_insert(LinkedList *list, void *element, const size_t index) {
    // TODO
}

void LinkedList_remove(LinkedList *list, const size_t element) {
    // TODO
}
