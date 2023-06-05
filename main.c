
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BoundedQueue.h"
#include "DynamicArray.h"

char* option = {"sport", "news", "weather"};

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
    int count, id, numberofproduce, queuesize = 0;
    int number = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == 1) {
            number++;
            id = atoi(buffer) - 1;
        }
        if (count == 2)
        {
            numberofproduce = atoi(buffer);
        }
        if (count == 3)
        {
            queuesize = atoi(buffer);
        }
        producer(id, numberofproduce, queuesize);
        count = count % 3;
        
        return 0;
    }
    fclose(file);
}


producer(int id, int numProducts, int queueSize){
    BoundedQueue* queue = createBoundedQueue(queueSize);
    int i;
    char* element;
    char str[10];
    sprintf(str, "%d", id);
    for (i = 0; i < numProducts; i++) {
        int length = snprintf(NULL, 0, "Producer %d %s %d", id, option[i % 3], i / 3);
        char* result = (char*)malloc((length + 1) * sizeof(char));
         snprintf(result, length + 1, "Producer %d %s %d", id, option[i % 3], i / 3);
         queue.append(result); 
       
        //enqueue the product
        free(result);
    }
    // enter DONE into the queue
    
}
// for (i = 0; i < N; i++) { 
    // read from the input file the number of products and the queue size
    // pthred producer(i, numProducts, queueSize);
// }

 // sportquere = new unbounded queue
 // newsquere = new unbounded queue
 // weatherquere = new unbounded queue

// dispatcher(){
    // while (true) {
        // int count = 0;
        // for (i = 0; i < N; i++) {
            // if (count == N) {
                // sportquere.enqueue("DONE");
                // newsquere.enqueue("DONE");
                // weatherquere.enqueue("DONE");
                // return;
            // lock the mutex for the bounded queue
            // char* element = array[i].dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // lock the mutex for the unbounded queue
            // if (element == DONE) {
                // destroy the bounded queue
                // count++;
                // continue;
            // }
            // if (element == SPORT) {
                // sportquere.enqueue(element);
            // }
            // if (element == NEWS) {
                // newsquere.enqueue(element);
            // }
            // if (element == WEATHER) {
                // weatherquere.enqueue(element);
            // }
        // }
    // }

    // thrhead dispatcher

    // mixedquere = new bounded queue(size = CO_EDITOR_QUEUE_SIZE)

    //sportCoEditor(sportquere){
        // count = 0;
        // while (count < 3) {
            // lock the mutex for the unbounded queue
            // char* element = sportquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // count++;
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }
    //newsCoEditor(newsquere){
        // while (true) {
            // lock the mutex for the unbounded queue
            // char* element = newsquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }
    //weatherquereCoEditor(weatherquere){
        // while (true) {
            // lock the mutex for the unbounded queue
            // char* element = weatherquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }

        //thread screenManager(mixedquere){
            // int count = 0;
            // while (count < 3) {
                // lock the mutex for the bounded queue
                // char* element = mixedquere.dequeue();
                // if (element == NULL) {
                    // continue;
                // }
                // unlock the mutex
                // if (element == DONE) {
                    // count++;
                    // return;
                // }
                // print the element
            // }

//     PRODUCER 1
// [number of products]
// queue size = [size]


// PRODUCER 2
// [number of products]
// queue size = [size]

// …
// …
// …
// PRODUCER n
// [number of products]
// queue size = [size]

// Co-Editor queue size = [size]

int PRODUCER_NUM = 10;
#define CO_EDIROT_NUM 3;
DynamicArray* array;

int main(int argc, char *argv[]) {
    DynamicArray* array = createDynamicArray(PRODUCER_NUM);
    const char* filename = argv[1];
    readFile(filename);
    return 0;
}