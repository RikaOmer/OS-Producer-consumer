
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BoundedQueue.h"
#include "DynamicArray.h"
#include "linkedlist.c"
#include "UBQ.c"

char* option = {"SPORT", "NEWS", "WEATHER"};
int PRODUCER_NUM = 10;
#define CO_EDIROT_NUM 3;
Node* head;
int size = 0;
UnboundedQueue* sportQueue;
UnboundedQueue* newsQueue;
UnboundedQueue* weatherQueue;

typedef struct {
    BoundedQueue* array;
    pthread_t thread;
}prodMangaer;

prodMangaer* array;

void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }
    char buffer[1024];
    int count, id, numberofproduce, queuesize = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == 1) {
            size++;
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

        detailNode* node = (detailNode*)malloc(sizeof(detailNode));
        node->value.id = id;
        node->value.numberofproduce = numberofproduce;
        node->value.queuesize = queuesize;
        if (head = NULL)
        {
            head = node;
        }
        else if (head->next == NULL)
        {
            head->next = node;
        }
        else
        {
            Node* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;
    }
        count = count % 3;
    }
    fclose(file);
}


void* producer(void* arg){
    Details details = *((Details*)arg);
    int id = details.id;
    int numberOfProduce = details.numberofproduce;
    int queueSize = details.queuesize;
    BoundedQueue* queue = createBoundedQueue(queueSize);
    int i;
    char* element;
    for (i = 0; i < numberOfProduce; i++) {
        int length = snprintf(NULL, 0, "Producer %d %s %d", id, option[i % 3], i / 3);
        char* element = (char*)malloc((length + 1) * sizeof(char));
         snprintf(element, length + 1, "Producer %d %s %d", id, option[i % 3], i / 3);
         enqueue(queue, element); //enqueue the product
        free(element);
    }
    element = "DONE";  // enter DONE into the queue
    enqueue(queue, element);
    append(array, *queue);
}

int main(int argc, char *argv[]) {
    sportQueue = createUnboundedQueue();
    newsQueue = createUnboundedQueue();
    weatherQueue = createUnboundedQueue();
    const char* filename = argv[1];
    readFile(filename);
    array = (prodMangaer*)malloc(size * sizeof(prodMangaer));
    int i = 0;
    detailNode* temp = head;
    Details* details = (Details*)malloc(sizeof(Details)*size);
    while (temp != NULL)
    {
        details[i] = temp->value;
        temp = temp->next;
        i++;
    }
    for (i = 0; i < size; i++)
    {
        array[i].array = createBoundedQueue(temp->value.queuesize);
        pthread_t thread;
        pthread_create(&thread, NULL, producer, &details[i]);
        array[i].thread = thread;
    }

    return 0;


}


// dispatcher(){
//     while (true) {
//         int count = 0;
//         for (i = 0; i < size; i++) {
//             if (count == size) {
//                 sportQueue.enqueue("DONE");
//                 newsQueue.enqueue("DONE");
//                 weatherQueue.enqueue("DONE");
//                 return;
//             }
//             // lock the mutex for the bounded queue
//             char* element = array[i].array.dequeue();
//             if (element == NULL) {
//                 continue;
//             }
//             // unlock the mutex
//             // lock the mutex for the unbounded queue
//             if (element == "DONE") {
//                 array[i].array.destroyBoundedQueue();
//                 count++;
//                 continue;
//             }
//             if (element == "SPORT") {
//                 sportQueue.enqueue(element);
//             }
//             if (element == "NEWS") {
//                 newsQueue.enqueue(element);
//             }
//             if (element == "WEATHER") {
//                 weatherQueue.enqueue(element);
//             }
//         }
//     }
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