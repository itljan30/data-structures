#include "node.h"
#include "callbacks.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

Node *Node_new(void *data, Node *nextNode) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->nextNode = nextNode ? nextNode : NULL;

    return node;
}

void Node_destroy(Node *node) {
    // TODO frees all data it contains as well
}

void Node_free(Node *node) {
    free(node);
}

TreeNode *TreeNode_new(void *data, TreeNode *rightNode, TreeNode *leftNode) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->right = rightNode ? rightNode : NULL;
    node->left = leftNode ? leftNode : NULL;

    return node;
}

void TreeNode_free(TreeNode *node) {
    free(node);
}
