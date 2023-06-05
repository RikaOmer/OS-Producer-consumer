#ifndef BOUNDEDQUEUE_H
#define BOUNDEDQUEUE_H

typedef struct {
    char* array;                 // Array to hold the elements
    int front;                  // Front index of the queue
    int length;                 // Current length of the queue
    int capacity;               // Maximum capacity of the queue
    sem_t full;                 // Semaphore to track the number of filled slots
    sem_t empty;                // Semaphore to track the number of empty slots
    pthread_mutex_t mutex;      // Mutex to synchronize access to the queue
} BoundedQueue;

BoundedQueue* createBoundedQueue(int capacity);
void destroyBoundedQueue(BoundedQueue* queue);
int isFull(BoundedQueue* queue);
int isEmpty(BoundedQueue* queue);
void enqueue(BoundedQueue* queue, char* element);
void dequeue(BoundedQueue* queue);







#endif
