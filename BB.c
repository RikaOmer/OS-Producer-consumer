#include <stdio.h>
#include <stdlib.h>
#include "BoundedQueue.h"

BoundedQueue* createBoundedQueue(int capacity) {
    BoundedQueue* queue = (BoundedQueue*)malloc(sizeof(BoundedQueue));
    queue->array = (char*)malloc(capacity * sizeof(char));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->length = 0;
    return queue;
}

void destroyBoundedQueue(BoundedQueue* queue) {
    free(queue->array);
    free(queue);
}

int isFull(BoundedQueue* queue) {
    return queue->length == queue->capacity;
}

int isEmpty(BoundedQueue* queue) {
    return queue->length == 0;
}

void enqueue(BoundedQueue* queue, char* element) {
    if (isFull(queue)) {
        printf("Queue is full. Unable to enqueue element %d.\n", element);
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = element;
    queue->length++;
    printf("Enqueued element: %d\n", element);
}

void dequeue(BoundedQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Unable to dequeue.\n");
        return;
    }
    int dequeuedElement = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->length--;
    printf("Dequeued element: %d\n", dequeuedElement);
}

int main() {
    int capacity = 5;  // Maximum capacity of the queue
    BoundedQueue* queue = createBoundedQueue(capacity);

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
