#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *nextNode;
} Node;

// TODO delete this if I never actually use it
typedef struct BiNode {
    void *data;
    struct Node *nextNode;
    struct Node *prevNode;
} BiNode;

Node *newNode(size_t dataSize, void *data, Node *nextNode);
void freeNode(Node *node);

#endif
