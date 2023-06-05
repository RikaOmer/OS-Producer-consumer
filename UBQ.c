#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    sem_t items;                // Semaphore to track the number of items in the queue
    pthread_mutex_t mutex;      // Mutex to synchronize access to the queue
} UnboundedQueue;

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

void enqueue(UnboundedQueue* queue, int element) {
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

int dequeue(UnboundedQueue* queue) {
    sem_wait(&(queue->items));   // Wait for an available item
    pthread_mutex_lock(&(queue->mutex));   // Acquire the mutex lock

    Node* dequeuedNode = queue->front;
    int dequeuedElement = dequeuedNode->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        // The queue is now empty
        queue->rear = NULL;
    }

    free(dequeuedNode);

    pthread_mutex_unlock(&(queue->mutex)); // Release the mutex lock

    return dequeuedElement;
}

int main() {
    UnboundedQueue* queue = createUnboundedQueue();

    // Enqueue elements
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    // Dequeue elements
    int element1 = dequeue(queue);
    int element2 = dequeue(queue);

    printf("Dequeued elements: %d, %d\n", element1, element2);

    destroyUnboundedQueue(queue);
    return 0;
}
