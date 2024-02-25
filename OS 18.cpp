#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

HANDLE mutex, full, empty;

DWORD WINAPI producer(LPVOID arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // Produce a random item
        WaitForSingleObject(empty, INFINITE); // Wait if buffer is full
        WaitForSingleObject(mutex, INFINITE); // Acquire lock on the buffer
        buffer[in] = item;
        printf("Producer produced item: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        ReleaseMutex(mutex); // Release lock on the buffer
        ReleaseSemaphore(full, 1, NULL); // Signal that buffer is no longer empty
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        WaitForSingleObject(full, INFINITE); // Wait if buffer is empty
        WaitForSingleObject(mutex, INFINITE); // Acquire lock on the buffer
        item = buffer[out];
        printf("Consumer consumed item: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        ReleaseMutex(mutex); // Release lock on the buffer
        ReleaseSemaphore(empty, 1, NULL); // Signal that buffer is no longer full
        Sleep(1000);
    }
    return 0;
}

int main() {
    HANDLE producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    // Initialize semaphores
    mutex = CreateMutex(NULL, FALSE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producers[i] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumers[i] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    }

    // Wait for producer threads to finish
    WaitForMultipleObjects(NUM_PRODUCERS, producers, TRUE, INFINITE);

    // Wait for consumer threads to finish
    WaitForMultipleObjects(NUM_CONSUMERS, consumers, TRUE, INFINITE);

    // Close handles
    CloseHandle(mutex);
    CloseHandle(full);
    CloseHandle(empty);

    return 0;
}
