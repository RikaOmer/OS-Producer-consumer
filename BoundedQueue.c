#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "BoundedQueue.h"

#define BUFFER_SIZE 5


BoundedQueue* createBoundedQueue(int capacity) {
    BoundedQueue* queue = (BoundedQueue*)malloc(sizeof(BoundedQueue));
    queue->array = (char*)malloc(capacity * sizeof(char));
    queue->front = 0;
    queue->length = 0;
    queue->capacity = capacity;
    sem_init(&(queue->full), 0, 0);              // Initialize full semaphore to 0
    sem_init(&(queue->empty), 0, capacity);      // Initialize empty semaphore to capacity
    pthread_mutex_init(&(queue->mutex), NULL);   // Initialize mutex
    return queue;
}

void destroyBoundedQueue(BoundedQueue* queue) {
    free(queue->array);
    sem_destroy(&(queue->full));
    sem_destroy(&(queue->empty));
    pthread_mutex_destroy(&(queue->mutex));
    free(queue);
}

void enqueue(BoundedQueue* queue, char* element) {
    sem_wait(&(queue->empty));       // Wait for an available empty slot
    pthread_mutex_lock(&(queue->mutex));    // Acquire the mutex lock

    int index = (queue->front + queue->length) % queue->capacity; // Calculate the index for enqueueing
    queue->array[index] = element;
    queue->length++;
    printf("Enqueued element: %d\n", element);

    pthread_mutex_unlock(&(queue->mutex));  // Release the mutex lock
    sem_post(&(queue->full));       // Increment the full semaphore
}

char* dequeue(BoundedQueue* queue) {
    sem_wait(&(queue->full));       // Wait for a filled slot
    pthread_mutex_lock(&(queue->mutex));    // Acquire the mutex lock

    char* dequeuedElement = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;    // Move the front index
    queue->length--;
    pthread_mutex_unlock(&(queue->mutex));  // Release the mutex lock
    sem_post(&(queue->empty));      // Increment the empty semaphore
    return dequeuedElement;
}

int main() {
    BoundedQueue* queue = createBoundedQueue(BUFFER_SIZE);

    // Enqueue elements
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    // Dequeue elements
    dequeue(queue);
    dequeue(queue);

    destroyBoundedQueue(queue);
    return 0;
}
