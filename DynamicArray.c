#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "BoundedQueue.h"



DynamicArray* createDynamicArray(int capacity) {
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamicArray->array = (BoundedQueue*)malloc(capacity * sizeof(BoundedQueue));
    dynamicArray->capacity = capacity;
    dynamicArray->length = 0;
    return dynamicArray;
}

void destroyDynamicArray(DynamicArray* dynamicArray) {
    free(dynamicArray->array);
    free(dynamicArray);
}

void append(DynamicArray* dynamicArray, BoundedQueue element) {
    if (dynamicArray->length == dynamicArray->capacity) {
        dynamicArray->capacity *= 2;  // Double the capacity if array is full
        dynamicArray->array = (BoundedQueue*)realloc(dynamicArray->array, dynamicArray->capacity * sizeof(BoundedQueue));
    }
    dynamicArray->array[dynamicArray->length] = element;
    dynamicArray->length++;
}

int main() {
    int N = 5;  // Input size
    DynamicArray* arr = createDynamicArray(N);

    // Append elements to the array
    // append(arr, 1);
    // append(arr, 2);
    // append(arr, 3);

    // Access elements using index
    printf("%d\n", arr->array[0]);  // Output: 1
    printf("%d\n", arr->array[1]);  // Output: 2
    printf("%d\n", arr->array[2]);  // Output: 3

    // Get the length of the array
    printf("%d\n", arr->length);  // Output: 3

    destroyDynamicArray(arr);
    return 0;
}
