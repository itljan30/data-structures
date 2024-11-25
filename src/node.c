#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

Node *Node_new(size_t dataSize, void *data, Node *nextNode) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->data = malloc(dataSize);
    if (node->data == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(node->data, data, dataSize);
    node->nextNode = nextNode ? nextNode : NULL;

    return node;
}

void Node_free(Node *node) {
    free(node->data);
    free(node);
}

TreeNode *TreeNode_new(size_t dataSize, void *data, TreeNode *rightNode, TreeNode *leftNode) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->data = malloc(dataSize);
    if (node->data == NULL) {
        printf("Error: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(node->data, data, dataSize);
    node->right = rightNode ? rightNode : NULL;
    node->left = leftNode ? leftNode : NULL;

    return node;
}

void TreeNode_free(TreeNode *node) {
    free(node->data);
    free(node);
}
