#include "test_struct.h"

#include <stdlib.h>
#include <string.h>

TestStruct *TestStruct_new() {
    TestStruct *testStruct = (TestStruct*)malloc(sizeof(TestStruct));
    testStruct->data1 = malloc(sizeof(int));
    testStruct->data2 = malloc(sizeof(float));

    int value1 = 5;
    memcpy(testStruct->data1, &value1, sizeof(int));
    float value2 = 5.3;
    memcpy(testStruct->data2, &value2, sizeof(float));

    return testStruct;
}

void TestStruct_free(void *data) {
    TestStruct *testStruct = (TestStruct*)data;
    free(testStruct->data1);
    free(testStruct->data2);
    free(testStruct);
}
