#include "binary_tree.h"

#include <string.h>

static int defaultCompare(void *a, void *b, size_t elementSize) {
    return memcmp(a, b, elementSize);
}

BinaryTree *BinaryTree_new(const size_t elementSize, CompareFunc compareFunc) {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->elementSize = elementSize;
    tree->compareFunc = compareFunc;
    tree->root = NULL;
    tree->length = 0;
    return tree;
}
