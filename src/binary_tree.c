#include "binary_tree.h"
#include "callbacks.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

static int RIGHT = 0;
static int LEFT = 1;

static void recursiveFree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    recursiveFree(node->left);
    recursiveFree(node->right);
    TreeNode_free(node);
}

static void removeLeaf(BinaryTree *tree, TreeNode *replacedNode, TreeNode *replacedParent, int direction) {
    if (replacedParent == NULL) {
        TreeNode_free(tree->root);
    }
    else if (direction == RIGHT) {
        replacedParent->right = NULL;
    }
    else {
        replacedParent->left = NULL;
    }
    TreeNode_free(replacedNode);
}

// assumes replaced node has only a right child
static void replaceWithRightChild(BinaryTree *tree, TreeNode *replacedNode, TreeNode *replacedParent, int direction) {
    if (replacedParent == NULL) {
        tree->root = replacedNode->right;
    }
    else if (direction == RIGHT) {
        replacedParent->right = replacedNode->right;
    }
    else {
        replacedParent->left = replacedNode->right;
    }
    TreeNode_free(replacedNode);
}

// assumes replaced node has only a left child
static void replaceWithLeftChild(BinaryTree *tree, TreeNode *replacedNode, TreeNode *replacedParent, int direction) {
    if (replacedParent == NULL) {
        tree->root = replacedNode->left;
    }
    else if (direction == RIGHT) {
        replacedParent->right = replacedNode->left;
    }
    else {
        replacedParent->left = replacedNode->left;
    }
    TreeNode_free(replacedNode);
}

// assumes replaced node has 2 children
static void replaceWithSuccessor(BinaryTree *tree, TreeNode *replacedNode, TreeNode *replacedParent, int direction) {
    TreeNode *successorParent = NULL;
    TreeNode *successorNode = replacedNode->right;
    while (successorNode->left != NULL) {
            successorParent = successorNode;
            successorNode = successorNode->left;
    }

    if (successorParent != NULL) {
        if (successorNode->right != NULL) {
            successorParent->left = successorNode->right;
        }
        else {
            successorParent->left = NULL;
        }
    }
    
    if (replacedParent == NULL) {
        tree->root = successorNode;
        successorNode->right = replacedNode->right;
        successorNode->left = replacedNode->left;
    }
    else if (direction == RIGHT) {
        replacedParent->right = successorNode;
    }
    else {
        replacedParent->left = successorNode;
    }

    if (successorParent == NULL) {
        successorNode->left = replacedNode->left;
    }
    else {
        successorNode->right = replacedNode->right;
        successorNode->left = replacedNode->left;
    }
    
    TreeNode_free(replacedNode);
}

BinaryTree *BinaryTree_new(CompareFunc compareFunc) {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->compareFunc = compareFunc;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void BinaryTree_free(BinaryTree *tree) {
    recursiveFree(tree->root);
    free(tree);
}

void BinaryTree_insert(BinaryTree *tree, void *element) {
    tree->size++;
    if (tree->root == NULL) {
        TreeNode *node = TreeNode_new(element, NULL, NULL);
        tree->root = node;
        return;
    }

    TreeNode *currentNode = tree->root;
    while (true) {
        int comparison = tree->compareFunc(element, currentNode->data);

        if (comparison < 0) {
            if (currentNode->left == NULL) {
                TreeNode *node = TreeNode_new(element, NULL, NULL);
                currentNode->left = node;
                return;
            }
            currentNode = currentNode->left;
        }
        else {
            if (currentNode->right == NULL) {
                TreeNode *node = TreeNode_new(element, NULL, NULL);
                currentNode->right = node;
                return;
            }
            currentNode = currentNode->right;
        }
    }
}

void *BinaryTree_search(BinaryTree *tree, void *element) {
    TreeNode *currentNode = tree->root;
    while (currentNode != NULL) {
        int comparison = tree->compareFunc(element, currentNode->data);

        if (comparison < 0) {
            currentNode = currentNode->left;
        }
        else if (comparison > 0) {
            currentNode = currentNode->right; 
        }
        else {
            return currentNode->data;
        }
    }
    return NULL;
}

int BinaryTree_delete(BinaryTree *tree, void *element) {
    if (tree->root == NULL) {
        return -1;
    }

    int direction = -1;
    TreeNode *prevNode = NULL;
    TreeNode *currentNode = tree->root;
    while (currentNode != NULL) {
        int comparison = tree->compareFunc(element, currentNode->data);

        if (comparison < 0) {
            direction = LEFT;
            prevNode = currentNode;
            currentNode = currentNode->left;
        }
        else if (comparison > 0) {
            direction = RIGHT;
            prevNode = currentNode;
            currentNode = currentNode->right; 
        }
        else {
            break;
        }
    }

    if (currentNode == NULL) {
        return -1;
    }

    if (currentNode->left == NULL && currentNode->right == NULL) {
        removeLeaf(tree, currentNode, prevNode, direction);
    }
    else if (currentNode->left == NULL && currentNode->right != NULL) {
        replaceWithRightChild(tree, currentNode, prevNode, direction);
    }
    else if (currentNode->left != NULL && currentNode->right == NULL) {
        replaceWithLeftChild(tree, currentNode, prevNode, direction);
    }
    else if (currentNode->left != NULL && currentNode->right != NULL) {
        replaceWithSuccessor(tree, currentNode, prevNode, direction);
    }

    tree->size--;
    return 0;
}

size_t BinaryTree_size(BinaryTree *tree) {
    return tree->size;
}
