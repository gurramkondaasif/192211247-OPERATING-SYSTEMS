#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_SLICE 2 // Time quantum for Round Robin scheduling

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completed;
};

void roundRobin(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("Process\tWaiting Time\tTurnaround Time\n");

    int completed_processes = 0;
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int execute_time = (processes[i].remaining_time < TIME_SLICE) ? processes[i].remaining_time : TIME_SLICE;
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;

                if (processes[i].remaining_time == 0) {
                    completed_processes++;

                    // Calculate waiting time
                    int waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
                    if (waiting_time < 0) {
                        waiting_time = 0;
                    }
                    total_waiting_time += waiting_time;

                    // Calculate turnaround time
                    int turnaround_time = waiting_time + processes[i].burst_time;
                    total_turnaround_time += turnaround_time;

                    printf("%d\t%d\t\t%d\n", processes[i].id, waiting_time, turnaround_time);
                }
            }
        }
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
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    printf("\nRound Robin Scheduling:\n");
    roundRobin(processes, n);

    return 0;
}
