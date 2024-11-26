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

/**
 * Returns a node with the given data and left/right node.
 * NOTE: If you don't have a left/right node, put NULL.
 */
TreeNode *TreeNode_new(size_t dataSize, void *data, TreeNode *rightNode, TreeNode *leftNode);

/*
 * Frees all memory allocated to the given node.
 */
void TreeNode_free(TreeNode *node);

typedef struct BiTreeNode {
    void *data;
    struct BiTreeNode *prevNode;
    struct BiTreeNode *left;
    struct BiTreeNode *right;
} BiTreeNode;

#endif
