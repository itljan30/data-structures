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

    node->data = malloc(sizeof(void*));
    if (node->data == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(node->data, data, sizeof(void*));
    node->nextNode = nextNode ? nextNode : NULL;

    return node;
}

void Node_free(Node *node) {
    free(node->data);
    free(node);
}

TreeNode *TreeNode_new(size_t dataSize, void *data, TreeNode *rightNode, TreeNode *leftNode, FreeFunc freeFunc) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->data = malloc(dataSize);
    if (node->data == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(node->data, data, dataSize);
    node->right = rightNode ? rightNode : NULL;
    node->left = leftNode ? leftNode : NULL;
    node->freeFunc = freeFunc;

    return node;
}

void TreeNode_free(void *data) {
    TreeNode *node = (TreeNode*)data;
    if (node->freeFunc != NULL) {
        node->freeFunc(node->data);
    }
    free(node->data);
    free(node);
}
