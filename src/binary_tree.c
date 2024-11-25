#include "binary_tree.h"
#include "node.h"

#include <string.h>
#include <stdbool.h>

static int defaultCompare(void *a, void *b, size_t elementSize) {
    return memcmp(a, b, elementSize);
}

static void recursiveFree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    recursiveFree(node->left);
    recursiveFree(node->right);
    TreeNode_free(node);
}

BinaryTree *BinaryTree_new(const size_t elementSize, CompareFunc compareFunc) {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->elementSize = elementSize;
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
        TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL);
        tree->root = node;
        return;
    }

    TreeNode *currentNode = tree->root;
    while (true) {
        int comparison = tree->compareFunc ? tree->compareFunc(element, currentNode->data)
                                           : defaultCompare(element, currentNode->data, tree->elementSize);

        if (comparison < 0) {
            if (currentNode->left == NULL) {
                TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL);
                currentNode->left = node;
                return;
            }
            currentNode = currentNode->left;
        }
        else {
            if (currentNode->right == NULL) {
                TreeNode *node = TreeNode_new(tree->elementSize, element, NULL, NULL);
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
        else if (comparison == 0) {
            return currentNode->data;
        }
    }
    return NULL;
}
