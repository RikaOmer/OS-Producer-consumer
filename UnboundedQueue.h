#ifndef UNBOUNDEDQUEUE_H
#define UNBOUNDEDQUEUE_H
#include "semaphore.h"         
#include <pthread.h>          

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct UnboundedQueue{
    Node* front;
    Node* rear;
    sem_t items;                
    pthread_mutex_t mutex;      
} UnboundedQueue;

UnboundedQueue* createUnboundedQueue() ;
void destroyUnboundedQueue(UnboundedQueue* queue);
void uEnqueue(UnboundedQueue* queue, char* element);
char* uDequeue(UnboundedQueue* queue);

#endif
