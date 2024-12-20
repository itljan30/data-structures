#include "binary_tree.h"

#include <assert.h>
#include <stddef.h>

int compareInt(void *data1, void *data2) {
    return *(int*)data1 - *(int*)data2;
}

void insert() {
    BinaryTree *tree = BinaryTree_new(compareInt);

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
    BinaryTree *tree = BinaryTree_new(compareInt);

    int value = 420;
    BinaryTree_insert(tree, &value);
    int otherValue = 1000;
    BinaryTree_insert(tree, &otherValue);
    int anotherValue = 5;
    BinaryTree_insert(tree, &anotherValue);

    int *result = (int *)BinaryTree_search(tree, &value);
    assert(result != NULL);

    int randomNum = 69;
    int *otherResult = (int *)BinaryTree_search(tree, &randomNum);
    assert(otherResult == NULL);

    BinaryTree_free(tree);
}

void delete() {
    BinaryTree *tree = BinaryTree_new(compareInt);

    /*   
     *  resulting tree
     *         5
     *        / \
     *       /   \
     *      2     8
     *     / \   / \
     *    1   3 6   9
     *   /     \ \   \
     *  0       4 7   10
     */

    int value = 5;
    BinaryTree_insert(tree, &value);
    value = 2;
    BinaryTree_insert(tree, &value);
    value = 1;
    BinaryTree_insert(tree, &value);
    value = 0;
    BinaryTree_insert(tree, &value);
    value = 3;
    BinaryTree_insert(tree, &value);
    value = 4;
    BinaryTree_insert(tree, &value);
    value = 8;
    BinaryTree_insert(tree, &value);
    value = 6;
    BinaryTree_insert(tree, &value);
    value = 7;
    BinaryTree_insert(tree, &value);
    value = 9;
    BinaryTree_insert(tree, &value);
    value = 10;
    BinaryTree_insert(tree, &value);

    // no children
    value = 4;
    int result = BinaryTree_delete(tree, &value);
    assert(result == 0);
    void *searchResult = BinaryTree_search(tree, &value);
    assert(searchResult == NULL);

    // only left child
    value = 1;
    result = BinaryTree_delete(tree, &value);
    assert(result == 0);
    searchResult = BinaryTree_search(tree, &value);
    assert(searchResult == NULL);
    int checkFor = 0;
    searchResult = BinaryTree_search(tree, &checkFor);
    assert(searchResult != NULL);

    // only right child
    value = 6;
    result = BinaryTree_delete(tree, &value);
    assert(result == 0);
    searchResult = BinaryTree_search(tree, &value);
    assert(searchResult == NULL);
    checkFor = 7;
    searchResult = BinaryTree_search(tree, &checkFor);
    assert(searchResult != NULL);

    // has 2 children
    value = 8;
    result = BinaryTree_delete(tree, &value);
    assert(result == 0);
    searchResult = BinaryTree_search(tree, &value);
    assert(searchResult == NULL);
    checkFor = 10;
    searchResult = BinaryTree_search(tree, &checkFor);
    assert(searchResult != NULL);

    // root
    value = 5;
    result = BinaryTree_delete(tree, &value);
    assert(result == 0);
    searchResult = BinaryTree_search(tree, &value);
    assert(searchResult == NULL);
    checkFor = 9;
    searchResult = BinaryTree_search(tree, &checkFor);
    assert(searchResult != NULL);
    checkFor = 0;
    searchResult = BinaryTree_search(tree, &checkFor);
    assert(searchResult != NULL);

    BinaryTree_free(tree);
}

int main(void) {
    insert();
    search();
    /* delete(); */ // TODO finish test
}
