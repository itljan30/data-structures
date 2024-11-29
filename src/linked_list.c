#include "linked_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

ListNode *ListNode_new(void *data, ListNode *nextNode) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->nextNode = nextNode ? nextNode : NULL;

    return node;
}

void ListNode_destroy(ListNode *node) {
    // TODO frees all data it points to as well
}

void ListNode_free(ListNode *node) {
    free(node);
}

LinkedList *LinkedList_new(const size_t elementSize) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->elementSize = elementSize;
    list->firstNode = NULL;
    list->length = 0;
    return list;
}

void LinkedList_free(LinkedList *list) {
    if (list->firstNode == NULL) {
        free(list);
        return;
    }
    ListNode *currentNode = list->firstNode;
    ListNode *nextNode = NULL;
    while (true) {
        if (currentNode->nextNode == NULL) {
            ListNode_free(currentNode);
            break;
        }
        nextNode = currentNode->nextNode;
        ListNode_free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}

void LinkedList_append(LinkedList *list, void *element) {
    if (list->firstNode == NULL) {
        list->firstNode = ListNode_new(element, NULL);
    }
    else {
        ListNode *node = ListNode_new(element, NULL);

        ListNode *currentNode = list->firstNode;
        ListNode *nextNode = NULL;
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
        list->firstNode = ListNode_new(element, NULL);
    }
    else {
        list->firstNode = ListNode_new(element, list->firstNode);
    }
    list->length++;
}

void LinkedList_insert(LinkedList *list, void *element, const size_t index) {
    if (index > list->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        list->firstNode = ListNode_new(element, list->firstNode);
        return;
    }

    ListNode *nodeBeforeInsert = list->firstNode;
    for (int i = 1; i < index; i++) {
        nodeBeforeInsert = nodeBeforeInsert->nextNode;
    }

    ListNode *newNode = ListNode_new(element, NULL);
    if (nodeBeforeInsert->nextNode != NULL) {
        newNode->nextNode = nodeBeforeInsert->nextNode;
    }

    nodeBeforeInsert->nextNode = newNode;
    list->length++;
}

void LinkedList_remove(LinkedList *list, const size_t index) {
    if (index >= list->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        ListNode *newHead = list->firstNode->nextNode;
        ListNode_free(list->firstNode);
        list->firstNode = newHead;
        return;
    }

    list->length--;

    ListNode *nodeBeforeRemove = list->firstNode;
    for (int i = 1; i < index; i++) {
        nodeBeforeRemove = nodeBeforeRemove->nextNode;
    }

    if (index == list->length) {
        ListNode_free(nodeBeforeRemove->nextNode);
        nodeBeforeRemove->nextNode = NULL;
        return;
    }

    ListNode *newNextNode = nodeBeforeRemove->nextNode->nextNode;
    ListNode_free(nodeBeforeRemove->nextNode);
    nodeBeforeRemove->nextNode = newNextNode;
}

size_t LinkedList_len(LinkedList *list) {
    return list->length;
}

void *LinkedList_at(LinkedList *list, size_t index) {
    if (index >= list->length) {
        printf("ERROR: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    if (index == 0) {
        return list->firstNode->data;
    }
    
    ListNode *currentNode = list->firstNode;
    for (int currentIndex = 1; currentIndex <= index; currentIndex++) {
        currentNode = currentNode->nextNode;
    }

    return currentNode->data;
}

bool LinkedList_contains(LinkedList *list, void *element) {
    ListNode *currentNode = list->firstNode;
    if (memcmp(currentNode->data, element, list->elementSize) == 0) {
        return true;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
        if (memcmp(currentNode->data, element, list->elementSize) == 0) {
            return true;
        }
    }
    return false;
}
