#include "linked_list.h"

#include <stdlib.h>

#include "node.h"

LinkedList newLinkedList(const size_t elementSize) {
    LinkedList list = {NULL, elementSize, 0};
    return list;
}

void freeLinkedList(LinkedList *list) {
    Node *currentNode = list->firstNode;
    Node *nextNode = NULL;
    for (int i = 0; i < list->length; i++) {
        nextNode = currentNode->nextNode;
        freeNode(currentNode);
        currentNode = nextNode;
    }
    list->firstNode = NULL;
    list->length = 0;
}

void appendLL(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = newNode(list->elementSize, element, NULL);
    }
    else {
        Node *currentNode = list->firstNode;
        
        for (int i = 0; i < list->length; i++) {
            // TODO walk through list until find one with nextNode = NULL;
        }
    }
    list->length++;
}

void prependLL(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = newNode(list->elementSize, element, NULL);
    }
    else {
        list->firstNode = newNode(list->elementSize, element, list->firstNode);
    }
    list->length++;
}
