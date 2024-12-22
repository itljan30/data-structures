#include "callbacks.h"

#include <string.h>
int compareInt(void *a, void *b) {
    return *(int*)a - *(int*)b;
}

int compareLong(void *a, void *b) {
    return *(long*)a - *(long*)b;
}

int compareShort(void *a, void *b) {
    return *(short*)a - *(short*)b;
}

int compareChar(void *a, void *b) {
    return *(char*)a - *(char*)b;
}

int compareString(void *a, void *b) {
    return strcmp(*(char**)a, *(char**)b);
}
