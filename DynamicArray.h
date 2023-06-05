#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct {
    BoundedQueue* array;
    int capacity;
    int length;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity) ;
void destroyDynamicArray(DynamicArray* dynamicArray);
void append(DynamicArray* dynamicArray, BoundedQueue element);



#endif