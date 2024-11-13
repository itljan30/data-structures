#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

Node *newNode(size_t dataSize, void *data, Node *nextNode) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->data = malloc(dataSize);
    if (node->data == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    if (data == NULL) {
        printf("Error: NULL data provided to LinkedList\n");
        exit(EXIT_FAILURE);
    }
    memcpy(node->data, data, dataSize);

    if (nextNode == NULL) {
        node->nextNode = NULL;
    }
    else {
        node->nextNode = nextNode;
    }
    return node;
}

void freeNode(Node *node) {
    free(node->data);
    free(node);
}
