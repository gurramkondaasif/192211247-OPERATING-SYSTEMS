#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_INCREMENTS 1000000

int shared_variable = 0;
pthread_mutex_t mutex;

void *increment(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex
        shared_variable++; // Increment the shared variable
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the value of the shared variable
    printf("Shared variable value: %d\n", shared_variable);

    return 0;
}
