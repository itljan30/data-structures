#include "hash_map.h"

#include <assert.h>

void set() {
    HashMap *map = HashMap_new(sizeof(char), sizeof(float), NULL);
    char key = 'e';
    float value = 35.2;
    HashMap_set(map, &key, &value);

    float *result = (float*)HashMap_find(map, &key);
    assert(result != NULL);
    assert(*result == value);

    HashMap_free(map);
}

void set1000() {
    char keyBuffer[1000];
    float valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        char key = 'e';
        float value = 35.2;
        keyBuffer[i] = key;
        valueBuffer[i] = value;
    }
    HashMap *map = HashMap_new(sizeof(char), sizeof(float), NULL);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }
    assert(map->usedBuckets == 1);
    char key = 'e';
    float value = 35.2;
    float *result = HashMap_find(map, &key);
    assert(*result == value);

    HashMap_free(map);
}

void set1000Unique() {
    int keyBuffer[1000];
    double valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        keyBuffer[i] = i;
        valueBuffer[i] = i;
    }
    HashMap *map = HashMap_new(sizeof(int), sizeof(double), NULL);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }

    for (int i = 0; i < 1000; i++) {
        double *value = HashMap_find(map, &i);
        assert(value != NULL);
        assert(*value == (double)i);
    }
    assert(map->length == 1000);

    HashMap_free(map);
}

void remove() {
    double keyBuffer[1000];
    float valueBuffer[1000];
    for (int i = 0; i < 1000; i++) {
        keyBuffer[i] = (double)i;
        valueBuffer[i] = (float)i;
    }
    HashMap *map = HashMap_new(sizeof(double), sizeof(float), NULL);
    for (int i = 0; i < 1000; i++) {
        HashMap_set(map, &keyBuffer[i], &valueBuffer[i]);
    }

    HashMap_remove(map, &keyBuffer[500]);

    float *result = HashMap_find(map, &keyBuffer[500]);
    assert(result == NULL);
    assert(map->length == 999);

    HashMap_free(map);

}

int main(void) {
    set();
    set1000();
    set1000Unique();
    remove();
}
