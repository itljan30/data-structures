#include "binary_tree.h"

#include <assert.h>

void insert() {
    BinaryTree *tree = BinaryTree_new(sizeof(int), NULL);

    int value = 3;
    BinaryTree_insert(tree, &value);
    int otherValue = 5;
    BinaryTree_insert(tree, &otherValue);
    int anotherValue = 1;
    BinaryTree_insert(tree, &anotherValue);

    assert(tree->size == 3);

    BinaryTree_free(tree);
}

void search() {
    BinaryTree *tree = BinaryTree_new(sizeof(float), NULL);

    float value = 1000;
    BinaryTree_insert(tree, &value);
    float otherValue = 420;
    BinaryTree_insert(tree, &otherValue);
    float anotherValue = 5;
    BinaryTree_insert(tree, &anotherValue);

    float *result = (float *)BinaryTree_search(tree, &value);
    assert(result != NULL);

    float randomNum = 69;
    float *otherResult = (float *)BinaryTree_search(tree, &randomNum);
    assert(otherResult == NULL);

    BinaryTree_free(tree);
}

int main(void) {
    insert();
    search();
}
