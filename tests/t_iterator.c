#include "hash_map.h"
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
    assert(i == 999);

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
    assert(i == 999);

    Iterator_destroy(iter, free);
}

void hashMap() {
    HashMap *map = HashMap_new(sizeof(char), compareChar);
    for (int i = 0; i < 200; i++) {
        char *c = malloc(sizeof(char));
        *c = (char)i;
        int *num = malloc(sizeof(int));
        *num = i;
        HashMap_set(map, c, num);
    }

    Iterator *iter = HashMap_iterData(map);

    int i = 0;
    while (Iterator_hasNext(iter)) {
        Iterator_next(iter);
        i++;
    }
    
    assert(i == 199);

    Iterator_free(iter);
    HashMap_destroy(map, free, free);
}

int main() {
    dynArr();
    linkedList();
    hashMap();
}
