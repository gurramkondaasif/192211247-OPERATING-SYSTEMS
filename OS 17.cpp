#include <stdio.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int finish[NUMBER_OF_CUSTOMERS];

void init() {
    // Initialize available resources
    printf("Enter the number of available resources:\n");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources needed for each customer
    printf("Enter the maximum demand of each customer:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("For customer %d:\n", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
        finish[i] = 0;
    }

    // Initialize allocated resources for each customer
    printf("Enter the allocated resources for each customer:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("For customer %d:\n", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }
}

int check(int customer) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (need[customer][i] > available[i]) {
            return 0;
        }
    }
    return 1;
}

void banker() {
    int work[NUMBER_OF_RESOURCES];
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }

    int safe = 0;
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (!finish[i] && check(i)) {
            for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                work[j] += allocation[i][j];
            }
            finish[i] = 1;
            safe = 1;
            printf("Customer %d allocated resources.\n", i);
        }
    }

    if (!safe) {
        printf("Unsafe state detected, unable to allocate resources.\n");
        return;
    }

    printf("Safe state detected, resources allocated successfully.\n");
}

int main() {
    init();
    banker();
    return 0;
}
