#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void FCFS(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("Process\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int waiting_time = current_time - processes[i].arrival_time;
        if (waiting_time < 0) {
            waiting_time = 0;
        }
        int turnaround_time = waiting_time + processes[i].burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\n", processes[i].id, waiting_time, turnaround_time);

        // Update current time for the next process
        current_time += processes[i].burst_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    printf("\nFCFS Scheduling:\n");
    FCFS(processes, n);

    return 0;
}
