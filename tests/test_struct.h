#ifndef TEST_STRUCT_H
#define TEST_STRUCT_H

typedef struct {
    int *data1;
    float *data2;
} TestStruct;

TestStruct *TestStruct_new();

void TestStruct_free(void *testStruct);

#endif
