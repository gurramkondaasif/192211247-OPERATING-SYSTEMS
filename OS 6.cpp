#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completed;
};

int findHighestPriority(struct Process processes[], int n, int current_time) {
    int highest_priority = -1;
    int highest_priority_index = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].completed == 0) {
            if (processes[i].priority > highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }
    }

    return highest_priority_index;
}

void preemptivePriorityScheduling(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("Process\tWaiting Time\tTurnaround Time\n");

    int completed_processes = 0;
    while (completed_processes < n) {
        int highest_priority_index = findHighestPriority(processes, n, current_time);

        if (highest_priority_index == -1) {
            // No process available, increment time
            current_time++;
        } else {
            struct Process *current_process = &processes[highest_priority_index];

            // Process the selected process
            if (current_process->remaining_time == current_process->burst_time) {
                // First time execution, update waiting time
                int waiting_time = current_time - current_process->arrival_time;
                if (waiting_time < 0) {
                    waiting_time = 0;
                }
                total_waiting_time += waiting_time;
            }

            current_process->remaining_time--;
            current_time++;

            if (current_process->remaining_time == 0) {
                // Process completed
                current_process->completed = 1;
                completed_processes++;

                // Calculate turnaround time
                int turnaround_time = current_time - current_process->arrival_time;
                total_turnaround_time += turnaround_time;

                printf("%d\t%d\t\t%d\n", current_process->id, total_waiting_time, turnaround_time);
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

    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    printf("\nPreemptive Priority Scheduling:\n");
    preemptivePriorityScheduling(processes, n);

    return 0;
}
