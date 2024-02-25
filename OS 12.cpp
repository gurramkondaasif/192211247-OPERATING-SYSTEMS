#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>


CRITICAL_SECTION chopstick[NUM_CHOPSTICKS];

// Function to simulate philosopher behavior
unsigned int __stdcall philosopher(void *arg) {
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // To avoid deadlock, always pick up the lower-numbered chopstick first
    if (left > right) {
        int temp = left;
        left = right;
        right = temp;
    }

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        Sleep(1000);

        printf("Philosopher %d is hungry\n", id);
        EnterCriticalSection(&chopstick[left]);
        printf("Philosopher %d picked up chopstick %d\n", id, left);
        EnterCriticalSection(&chopstick[right]);
        printf("Philosopher %d picked up chopstick %d\n", id, right);

        printf("Philosopher %d is eating\n", id);
        Sleep(1000);

        printf("Philosopher %d is done eating\n", id);
        LeaveCriticalSection(&chopstick[left]);
        printf("Philosopher %d put down chopstick %d\n", id, left);
        LeaveCriticalSection(&chopstick[right]);
        printf("Philosopher %d put down chopstick %d\n", id, right);
    }

    return 0;
}

int main() {
    HANDLE philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize critical sections
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        InitializeCriticalSection(&chopstick[i]);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        philosophers[i] = (HANDLE)_beginthreadex(NULL, 0, philosopher, &ids[i], 0, NULL);
        if (philosophers[i] == NULL) {
            printf("Error creating philosopher %d\n", i);
            exit(1);
        }
    }

    // Wait for philosopher threads to finish (which they won't)
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE);

    // Destroy critical sections
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        DeleteCriticalSection(&chopstick[i]);
    }

    return 0;
}
