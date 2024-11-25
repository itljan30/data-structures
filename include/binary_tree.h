#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "node.h"

typedef int (*CompareFunc)(void *a, void *b);

typedef struct {
    TreeNode *root;
    CompareFunc compareFunc;
    size_t elementSize;
    size_t length;
} BinaryTree;

/**
 * Returns an empty BinaryTree.
 * Example usage: `BinaryTree *tree = BinaryTree_new(sizeof(data), compareData)`.
 * WARNING: Make sure to call `BinaryTree_free()` to avoid memory leaks.
 * 
 * @param compareFunc A comparison function for comparing two elements.
 *                    Function must be in the form `int compareFunc(void *a, void *b)`.
 *                    It should return a negative int if `a < b`, 0 if `a == b`, and a positive int if `a > b`.
 *                    If `compareFunc == NULL`, it will use `memcmp` by default.
 */
BinaryTree *BinaryTree_new(size_t elementSize, CompareFunc compareFunc);

#endif
