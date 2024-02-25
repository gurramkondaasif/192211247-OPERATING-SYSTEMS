#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> // Include this header for intptr_t

#define NUM_THREADS 5

// Function to be executed by each thread
void *thread_function(void *thread_id) {
    intptr_t tid; // Use intptr_t for storing pointer values
    tid = (intptr_t)thread_id;
    printf("Hello, World! It's me, thread #%ld!\n", (long)tid); // Cast back to long for printing
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    intptr_t t; // Use intptr_t for storing pointer values

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", (long)t); // Cast to long for printing
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have completed their execution. Exiting...\n");

    pthread_exit(NULL);
}
