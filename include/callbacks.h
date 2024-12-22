#ifndef CALLBACKS_H
#define CALLBACKS_H

typedef void (*FreeFunc)(void *data);

typedef int (*CompareFunc)(void *a, void *b);

int compareInt(void *a, void *b);
int compareLong(void *a, void *b);
int compareShort(void *a, void *b);
int compareChar(void *a, void *b);
int compareString(void *a, void *b);

// TODO
// int compareFloat(void *a, void *b);
// int compareDouble(void *a, void *b);
// int compareUInt(void *a, void *b);
// int compareULong(void *a, void *b);
// int compareUShort(void *a, void *b);

#endif
