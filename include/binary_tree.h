#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "node.h"

typedef int (*CompareFunc)(void *a, void *b);

typedef struct {
    TreeNode *root;
    CompareFunc compareFunc;
    size_t elementSize;
    size_t size;
} BinaryTree;

/**
 * Returns an empty BinaryTree.
 * Example usage: `BinaryTree *tree = BinaryTree_new(sizeof(data), compareData)`.
 * WARNING: Make sure to call `BinaryTree_free()` to avoid memory leaks.
 * 
 * @param compareFunc A comparison function for comparing two elements.
 *                    Function must be in the form `int compareFunc(void *a, void *b)`.
 *                    It should return a negative int if `a < b`, 0 if `a == b`, and a positive int if `a > b`.
 *                    If `compareFunc == NULL`, it will compare values byte by byte.
 */
BinaryTree *BinaryTree_new(size_t elementSize, CompareFunc compareFunc);

/**
 * Inserts the given element into the given tree using the given compare function,
 * or by comparing byte by byte if no compare function is given.
 */
void BinaryTree_insert(BinaryTree *tree, void *element);

/**
 * Frees the allocated memory for the given tree.
 */
void BinaryTree_free(BinaryTree *tree);

/**
 * Searches the tree for an element matching the given value.
 * Returns a pointer to the found element or `NULL` if not found.
 */
void *BinaryTree_search(BinaryTree *tree, void *element);

// TODO void BinaryTree_delete(BinaryTree *tree, void *element);

#endif
