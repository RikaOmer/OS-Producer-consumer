#include <stdio.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    // This function will be executed in the new thread
    int threadId = *((int*)arg);
    printf("Thread %d: Hello, World!\n", threadId);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int threadId = 1;

    // Create a new thread
    int result = pthread_create(&thread, NULL, threadFunction, (void*)&threadId);
    if (result != 0) {
        printf("Failed to create thread.\n");
        return 0;
    }

    // Wait for the thread to finish execution
    result = pthread_join(thread, NULL);
    if (result != 0) {
        printf("Failed to join thread.\n");
        return 0;
    }

    printf("Main thread: Thread execution finished.\n");

    return 0;
}
