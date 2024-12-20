#include "hash_map.h"
#include "test_struct.h"

#include <assert.h>
#include <string.h>

int stringcmpr(void *data1, void *data2) {
    return strcmp((char*)data1, (char*)data2);
}

void set() {
    HashMap *map = HashMap_new(sizeof(char*), stringcmpr);
    char *key = "e";
    float value = 35.2;
    HashMap_set(map, &key, &value);

    float *result = (float*)HashMap_find(map, &key);
    assert(result != NULL);
    assert(*result == value);

    HashMap_free(map);
}

void set1000() {
    char *keyBuffer[1000];
    float valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        char *key = "e";
        float value = 35.2;
        keyBuffer[i] = key;
        valueBuffer[i] = value;
    }
    HashMap *map = HashMap_new(sizeof(char*), stringcmpr);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }
    assert(map->usedBuckets == 1);
    char *key = "e";
    float value = 35.2;
    float *result = HashMap_find(map, &key);
    assert(*result == value);

    HashMap_free(map);
}

int compareInts(void *data1, void *data2) {
    return *(int*)data1 - *(int*)data2;
}

void set1000Unique() {
    int keyBuffer[1000];
    int valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        keyBuffer[i] = i;
        valueBuffer[i] = i;
    }
    HashMap *map = HashMap_new(sizeof(int), compareInts);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }

    for (int i = 0; i < 1000; i++) {
        int *value = HashMap_find(map, &i);
        assert(value != NULL);
        assert(*value == i);
    }
    assert(map->length == 1000);

    HashMap_free(map);
}

void remove() {
    int keyBuffer[1000];
    float valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        keyBuffer[i] = (int)i;
        valueBuffer[i] = (float)i;
    }
    HashMap *map = HashMap_new(sizeof(int), compareInts);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }

    HashMap_remove(map, &keyBuffer[500]);

    float *result = HashMap_find(map, &keyBuffer[500]);
    assert(result == NULL);
    assert(map->length == 999);

    HashMap_free(map);
}

void destroy() {
    int keyBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        keyBuffer[i] = i;
    }
    HashMap *map = HashMap_new(sizeof(int), compareInts);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], TestStruct_new());
    }

    HashMap_destroy(map, NULL, TestStruct_free);
}

int main(void) {
    set();
    set1000();
    set1000Unique();
    remove();
    destroy();
}
