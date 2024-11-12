#include "dyn_arr.h"

#include <stdio.h>

int main(void) {
    DynArr arr = newDynArr(sizeof(char));
    for (int i = 0; i < 1000; i++) {
        char value = i;
        appendDA(&arr, &value);

        char *valueAt = atDA(&arr, i);
        printf("%i\n", *valueAt);
    }

    int *lastValue = atDA(&arr, 1000);

    freeDynArr(&arr);
}
