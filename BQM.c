#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

typedef struct {
    char* array;                 // Array to hold the elements
    int front;                  // Front index of the queue
    int length;                 // Current length of the queue
    int capacity;               // Maximum capacity of the queue
    sem_t full;                 // Semaphore to track the number of filled slots
    sem_t empty;                // Semaphore to track the number of empty slots
    pthread_mutex_t mutex;      // Mutex to synchronize access to the queue
} BoundedQueue;

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

void enqueue(BoundedQueue* queue, int element) {
    sem_wait(&(queue->empty));       // Wait for an available empty slot
    pthread_mutex_lock(&(queue->mutex));    // Acquire the mutex lock

    int index = (queue->front + queue->length) % queue->capacity; // Calculate the index for enqueueing
    queue->array[index] = element;
    queue->length++;
    printf("Enqueued element: %d\n", element);

    pthread_mutex_unlock(&(queue->mutex));  // Release the mutex lock
    sem_post(&(queue->full));       // Increment the full semaphore
}

void dequeue(BoundedQueue* queue) {
    sem_wait(&(queue->full));       // Wait for a filled slot
    pthread_mutex_lock(&(queue->mutex));    // Acquire the mutex lock

    int dequeuedElement = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;    // Move the front index
    queue->length--;
    printf("Dequeued element: %d\n", dequeuedElement);

    pthread_mutex_unlock(&(queue->mutex));  // Release the mutex lock
    sem_post(&(queue->empty));      // Increment the empty semaphore
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
