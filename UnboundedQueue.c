#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "UnboundedQueue.h"

UnboundedQueue* createUnboundedQueue() {
    UnboundedQueue* queue = (UnboundedQueue*)malloc(sizeof(UnboundedQueue));
    queue->front = NULL;
    queue->rear = NULL;
    sem_init(&(queue->items), 0, 0);        // Initialize items semaphore to 0
    pthread_mutex_init(&(queue->mutex), NULL);    // Initialize mutex
    return queue;
}

void destroyUnboundedQueue(UnboundedQueue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    sem_destroy(&(queue->items));
    pthread_mutex_destroy(&(queue->mutex));
    free(queue);
}

void uEnqueue(UnboundedQueue* queue, char* element) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = NULL;

    pthread_mutex_lock(&(queue->mutex));   // Acquire the mutex lock

    if (queue->rear == NULL) {
        // The queue is empty
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Add the new node to the end of the queue
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    sem_post(&(queue->items));   // Increment the items semaphore

    pthread_mutex_unlock(&(queue->mutex)); // Release the mutex lock
}

char* uDequeue(UnboundedQueue* queue) {
    sem_wait(&(queue->items));   // Wait for an available item
    pthread_mutex_lock(&(queue->mutex));   // Acquire the mutex lock

    Node* dequeuedNode = queue->front;
    char* dequeuedElement = dequeuedNode->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        // The queue is now empty
        queue->rear = NULL;
    }

    free(dequeuedNode);

    pthread_mutex_unlock(&(queue->mutex)); // Release the mutex lock

    return dequeuedElement;
}
