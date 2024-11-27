#include "binary_tree.h"
#include "node.h"
#include "callbacks.h"

#include <stdbool.h>

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

BinaryTree *BinaryTree_new(const size_t elementSize, CompareFunc compareFunc, FreeFunc freeFunc) {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->elementSize = elementSize;
    tree->compareFunc = compareFunc;
    tree->root = NULL;
    tree->size = 0;
    tree->freeFunc = freeFunc;
    return tree;
}

void BinaryTree_free(void *data) {
    BinaryTree *tree = (BinaryTree*)data;
    recursiveFree(tree->root);
    free(tree);
}

void BinaryTree_insert(BinaryTree *tree, void *element) {
    tree->size++;
    if (tree->root == NULL) {
        TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL, tree->freeFunc);
        tree->root = node;
        return;
    }

    TreeNode *currentNode = tree->root;
    while (true) {
        int comparison = tree->compareFunc ? tree->compareFunc(element, currentNode->data)
                                           : defaultCompare(element, currentNode->data, tree->elementSize);

        if (comparison < 0) {
            if (currentNode->left == NULL) {
                TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL, tree->freeFunc);
                currentNode->left = node;
                return;
            }
            currentNode = currentNode->left;
        }
        else {
            if (currentNode->right == NULL) {
                TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL, tree->freeFunc);
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
        int comparison = tree->compareFunc ? tree->compareFunc(element, currentNode->data)
                                           : defaultCompare(element, currentNode->data, tree->elementSize);

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
        int comparison = tree->compareFunc ? tree->compareFunc(element, currentNode->data)
                                           : defaultCompare(element, currentNode->data, tree->elementSize);

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
