#ifndef NODE_H
#define NODE_H

#include "callbacks.h"

#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *nextNode;
    FreeFunc freeFunc;
} Node;

/**
 * Returns a node with the given data and next node. 
 * NOTE: If you don't have a next node, put NULL.
 */
Node *Node_new(size_t dataSize, void *data, Node *nextNode, FreeFunc freeFunc);

/**
 * Frees the memory allocated to the node.
 * Uses `free()` if no custom free function was given.
 *
 * @param node is assumed to be a Node *.
 */
void Node_free(void *node);

typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
    FreeFunc freeFunc;
} TreeNode;

/**
 * Returns a node with the given data and left/right node.
 * NOTE: If you don't have a left/right node, put NULL.
 */
TreeNode *TreeNode_new(size_t dataSize, void *data, TreeNode *rightNode, TreeNode *leftNode, FreeFunc freeFunc);

/**
 * Frees all memory allocated to the given node.
 * Uses `free()` if no custom free function was given.
 *
 * @param node is assumed to be a Node *.
 */
void TreeNode_free(void *node);

typedef struct BiTreeNode {
    void *data;
    struct BiTreeNode *prevNode;
    struct BiTreeNode *left;
    struct BiTreeNode *right;
} BiTreeNode;

#endif
