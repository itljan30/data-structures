#include "test_struct.h"

#include <stdlib.h>
#include <string.h>

TestStruct *TestStruct_new() {
    TestStruct *testStruct = (TestStruct*)malloc(sizeof(TestStruct));
    testStruct->data1 = malloc(sizeof(int));
    testStruct->data2 = malloc(sizeof(double));
    int intValue = 10;
    double doubleValue = 100;
    memcpy(testStruct->data1, &intValue, sizeof(int));
    memcpy(testStruct->data2, &doubleValue, sizeof(double));

    return testStruct;
}

void TestStruct_free(void *data) {
    TestStruct *testStruct = (TestStruct*)data;
    free(testStruct->data1);
    free(testStruct->data2);
    free(data);
}
