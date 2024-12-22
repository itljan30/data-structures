#include "iterator.h"
#include "dyn_arr.h"
#include "linked_list.h"

#include <assert.h>

void dynArr() {
    DynArr *arr = DynArr_new();
    for (int i = 0; i < 1000; i++) {
        int *num = malloc(sizeof(int));
        *num = i;
        DynArr_append(arr, num);
    }

    Iterator *iter = DynArr_iter(arr);

    int i = 0;
    while (Iterator_hasNext(iter)) {
        assert(*(int*)Iterator_next(iter) == i);
        i++;
    }

    Iterator_destroy(iter, free);
}

void linkedList() {
    LinkedList *list = LinkedList_new();

    for (int i = 0; i < 1000; i++) {
        int *num = malloc(sizeof(int));
        *num = i;
        LinkedList_append(list, num);
    }

    Iterator *iter = LinkedList_iter(list);

    int i = 0;
    while (Iterator_hasNext(iter)) {
        assert(*(int*)Iterator_next(iter) == i);
        i++;
    }

    Iterator_destroy(iter, free);
}

int main() {
    dynArr();
    linkedList();
}
