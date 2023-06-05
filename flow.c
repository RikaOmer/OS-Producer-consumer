#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BoundedQueue.h"

struct Details {
    int number;
    int numbertoproduce;
    int queuesize;
};

void* threadFunction(void* arg) {
    // This function will be executed in the new thread
    int threadId = *((int*)arg);
    printf("Thread %d: Hello, World!\n", threadId);
    pthread_exit(NULL);
}

void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }
    char buffer[1024];
    int count = 0;
    int number = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == 1) {
            number++;
            int id = atoi(buffer) - 1;
        }
        if (count == 2)
        {
            int numbertoproduce = atoi(buffer);
        }
        if (count == 3)
        {
            int queuesize = atoi(buffer);
        }
        
        count = count % 3;
        
        return 0;
    }
    fclose(file);
}


typedef struct {
    BoundedQueue* array;
    int capacity;
    int length;
} DynamicArray;

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



int main(int argc, char *argv[]) {
    const char* filename = argv[1];
    readFile(filename);
    return 0;
}
