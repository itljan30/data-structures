#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *nextNode;
} Node;

/**
 * Returns a node with the given data and next node. 
 * NOTE: If you don't have a next node, put NULL.
 */
Node *Node_new(size_t dataSize, void *data, Node *nextNode);

/**
 * Frees the memory allocated to the node.
 */
void Node_free(Node *node);

typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct BiNode {
    void *data;
    struct Node *nextNode;
    struct Node *prevNode;
} BiNode;

#endif
