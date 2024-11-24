#include "linked_list.h"
#include "node.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

LinkedList LinkedList_new(const size_t elementSize) {
    LinkedList list = {NULL, 0, elementSize};
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
            Node_free(currentNode);
            break;
        }
        nextNode = currentNode->nextNode;
        Node_free(currentNode);
        currentNode = nextNode;
    }
    list->firstNode = NULL;
    list->length = 0;
}

void LinkedList_append(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = Node_new(list->elementSize, element, NULL);
    }
    else {
        Node *node = Node_new(list->elementSize, element, NULL);

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
        list->firstNode = Node_new(list->elementSize, element, NULL);
    }
    else {
        list->firstNode = Node_new(list->elementSize, element, list->firstNode);
    }
    list->length++;
}

void LinkedList_insert(LinkedList *list, void *element, const size_t index) {
    if (index > list->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        Node *newFirstNode = Node_new(list->elementSize, element, list->firstNode);
        list->firstNode = newFirstNode;
        return;
    }

    Node *nodeBeforeInsert = list->firstNode;
    for (int i = 1; i < index; i++) {
        nodeBeforeInsert = nodeBeforeInsert->nextNode;
    }

    Node *newNode = Node_new(list->elementSize, element, NULL);
    if (nodeBeforeInsert->nextNode != NULL) {
        newNode->nextNode = nodeBeforeInsert->nextNode;
    }
    nodeBeforeInsert->nextNode = newNode;
    list->length++;
}

void LinkedList_remove(LinkedList *list, const size_t index) {
    if (index >= list->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        Node *newHead = list->firstNode->nextNode;
        Node_free(list->firstNode);
        list->firstNode = newHead;
        return;
    }

    list->length--;

    Node *nodeBeforeRemove = list->firstNode;
    for (int i = 1; i < index; i++) {
        nodeBeforeRemove = nodeBeforeRemove->nextNode;
    }

    if (index == list->length) {
        Node_free(nodeBeforeRemove->nextNode);
        nodeBeforeRemove->nextNode = NULL;
        return;
    }

    Node *newNextNode = nodeBeforeRemove->nextNode->nextNode;
    Node_free(nodeBeforeRemove->nextNode);
    nodeBeforeRemove->nextNode = newNextNode;
}

size_t LinkedList_len(LinkedList *list) {
    return list->length;
}

void *LinkedList_at(LinkedList *list, size_t index) {
    if (index >= list->length) {
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        return list->firstNode->data;
    }
    
    Node *currentNode = list->firstNode;
    for (int currentIndex = 1; currentIndex <= index; currentIndex++) {
        currentNode = currentNode->nextNode;
    }

    return currentNode->data;
}
