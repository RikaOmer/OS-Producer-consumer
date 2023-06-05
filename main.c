
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include <unistd.h>

char* option = {"SPORT", "NEWS", "WEATHER"};
typedef struct {
int id;
int numberofproduce;
int queuesize;
} Details;
// Define the structure for a linked list element

typedef struct detailNode {
    Details value;
    struct derailNode* next;
} detailNode;
int PRODUCER_NUM = 10;
int CO_EDIROT_NUM = 3;
detailNode* head;
int size = 0;
UnboundedQueue* sportQueue;
UnboundedQueue* newsQueue;
UnboundedQueue* weatherQueue;
BoundedQueue* editorQueue;

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
    int id, numberofproduce, queuesize;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if ((strcmp(buffer, "\n") != 0) )
        {
        id = atoi(buffer) - 1;
        if (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            numberofproduce = atoi(buffer);
        }else{
            CO_EDIROT_NUM = id + 1;
            return;
        }
        fgets(buffer, sizeof(buffer), file);
        queuesize = atoi(buffer);

        detailNode* node = (detailNode*)malloc(sizeof(detailNode));
        node->value.id = id;
        node->value.numberofproduce = numberofproduce;
        node->value.queuesize = queuesize;
        if (head = NULL)
        {
            head->value = node->value;
            head->next = NULL;
        }
        else if (head->next == NULL)
        {
            head->next = node;
            node->next = NULL;
        }
        else
        {
            detailNode* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;
        }
        size++;
    }
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

void* dispatcher(){
    int i, count = 0;
    while (count != size) {
        for (i = 0; i < size; i++) {
            if (count == size) {
                uEnqueue(sportQueue, "DONE");
                uEnqueue(newsQueue, "DONE");
                uEnqueue(weatherQueue, "DONE");
                return;
            }
            char* element = dequeue(array[i].array);
            if (element == NULL) {
                continue;
            }
            if (strcmp(element,"DONE") == 0) {
                destroyBoundedQueue(array[i].array);
                count++;
                continue;
            }
            if (strstr(element, "SPORT") != NULL) {
                uEnqueue(sportQueue, element);
            }
            else if (strstr(element, "NEWS") != NULL) {
                uEnqueue(newsQueue, element);
            }
            else if (strstr(element, "WEATHER") != NULL) {
                uEnqueue(weatherQueue, element);
            }
        }
    }
}

void* sportCoEditor(){
        char* element = uDequeue(sportQueue);
        while (strcmp(element,"DONE") != 0) {
            sleep(0.1);
           enqueue(editorQueue, element);
           element = uDequeue(sportQueue);
        }
        destroyUnboundedQueue(sportQueue);
        enqueue(editorQueue, "DONE");
    }

void* newsCoEditor(){
        char* element = uDequeue(newsQueue);
        while (element != "DONE") {
           enqueue(editorQueue, element);
           element = uDequeue(newsQueue);
        }
        destroyUnboundedQueue(newsQueue);
        enqueue(editorQueue, "DONE");
    }

void* weatherCoEditor(){
        char* element = uDequeue(weatherQueue);
        while (element != "DONE") {
           enqueue(editorQueue, element);
           element = uDequeue(weatherQueue);
        }
        destroyUnboundedQueue(weatherQueue);
        enqueue(editorQueue, "DONE");
    }

void* screenManager(){
    int count = 0;
    while (count < 2) {
        char* element = dequeue(editorQueue);
            if (element == NULL) {
                continue;
            }
            else if (strcmp(element,"DONE") == 0) {
                count++;
                continue;
                }else{
                    printf("%s\n", element);
                }
                
    }
    destroyBoundedQueue(editorQueue);
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
        temp = temp->next; // problem ??
        i++;
    }
    for (i = 0; i < size; i++)
    {
        array[i].array = createBoundedQueue(details[i].queuesize);
        pthread_t thread;
        pthread_create(&thread, NULL, producer, &details[i]); // check the i
        array[i].thread = thread;
    }
    pthread_t dispThread;
    pthread_create(&dispThread, NULL, dispatcher, NULL);

    // sport news wheter full
    editorQueue = createBoundedQueue(CO_EDIROT_NUM);
    pthread_t sportThread;
    pthread_create(&sportThread, NULL, sportCoEditor, NULL);
    pthread_t newsThread;
    pthread_create(&newsThread, NULL, newsCoEditor, NULL);
    pthread_t weatherThread;
    pthread_create(&weatherThread, NULL, weatherCoEditor, NULL);
    pthread_t screenThread;
    pthread_create(&screenThread, NULL, screenManager, NULL);

    return 0;

}
