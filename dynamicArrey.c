#include <stdio.h>
#include <stdlib.h>


// array of bounded queue ******

typedef struct {
    int* array;
    int capacity;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity) {
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamicArray->array = (int*)malloc(capacity * sizeof(int));
    dynamicArray->capacity = capacity;
    return dynamicArray;
}

void destroyDynamicArray(DynamicArray* dynamicArray) {
    /// free to every bounded queue **************
    /// free to every bounded queue **************
    /// free to every bounded queue **************
    free(dynamicArray->array); 
    free(dynamicArray);
}

void append(DynamicArray* dynamicArray, int element, int i) {
    dynamicArray->array[i] = element;
}

int main() {
    int N = 5;  // Input size
    DynamicArray* arr = createDynamicArray(N);

    // Append elements to the array
    append(arr, 1, 1);
    append(arr, 2, 2);
    append(arr, 3, 3);

    // Access elements using index
    printf("%d\n", arr->array[0]);  // Output: 1
    printf("%d\n", arr->array[1]);  // Output: 2
    printf("%d\n", arr->array[2]);  // Output: 3

    // Get the length of the array
    printf("%d\n");  // Output: 3

    destroyDynamicArray(arr);
    return 0;
}
