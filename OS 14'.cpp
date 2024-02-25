#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100
#define ALLOCATED 1
#define FREE 0

typedef struct {
    int start;
    int size;
    int status;
} Block;

Block memory[MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].start = i;
        memory[i].size = 1;
        memory[i].status = FREE;
    }
}

void displayMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("[%d] ", memory[i].status);
    }
    printf("\n");
}

void allocateFirstFit(int processSize) {
    int found = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].status == FREE && memory[i].size >= processSize) {
            memory[i].status = ALLOCATED;
            found = 1;
            printf("Allocated using First Fit starting at index %d\n", memory[i].start);
            break;
        }
    }
    if (!found) {
        printf("Memory allocation failed for process size %d using First Fit\n", processSize);
    }
}

void allocateBestFit(int processSize) {
    int minSize = MEMORY_SIZE + 1;
    int index = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].status == FREE && memory[i].size >= processSize && memory[i].size < minSize) {
            minSize = memory[i].size;
            index = i;
        }
    }
    if (index != -1) {
        memory[index].status = ALLOCATED;
        printf("Allocated using Best Fit starting at index %d\n", memory[index].start);
    } else {
        printf("Memory allocation failed for process size %d using Best Fit\n", processSize);
    }
}

void allocateWorstFit(int processSize) {
    int maxSize = -1;
    int index = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].status == FREE && memory[i].size >= processSize && memory[i].size > maxSize) {
            maxSize = memory[i].size;
            index = i;
        }
    }
    if (index != -1) {
        memory[index].status = ALLOCATED;
        printf("Allocated using Worst Fit starting at index %d\n", memory[index].start);
    } else {
        printf("Memory allocation failed for process size %d using Worst Fit\n", processSize);
    }
}

int main() {
    initializeMemory();
    displayMemory();

    printf("\nAllocating process of size 10...\n");
    allocateFirstFit(10);
    displayMemory();

    printf("\nAllocating process of size 20...\n");
    allocateBestFit(20);
    displayMemory();

    printf("\nAllocating process of size 30...\n");
    allocateWorstFit(30);
    displayMemory();

    printf("\nAllocating process of size 5...\n");
    allocateFirstFit(5);
    displayMemory();

    return 0;
}
