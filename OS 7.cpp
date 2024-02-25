#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completed;
};

void nonPreemptiveSJF(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("Process\tWaiting Time\tTurnaround Time\n");

    int completed_processes = 0;
    while (completed_processes < n) {
        int shortest_index = -1;
        int shortest_burst = 99999; // Initial shortest burst time set to a large value

        // Find the process with the shortest burst time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completed == 0) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            // No process available, increment time
            current_time++;
        } else {
            // Process the selected process
            processes[shortest_index].completed = 1;
            int waiting_time = current_time - processes[shortest_index].arrival_time;
            if (waiting_time < 0) {
                waiting_time = 0;
            }
            int turnaround_time = waiting_time + processes[shortest_index].burst_time;

            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;

            printf("%d\t%d\t\t%d\n", processes[shortest_index].id, waiting_time, turnaround_time);

            // Update current time
            current_time += processes[shortest_index].burst_time;
            completed_processes++;
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
        processes[i].completed = 0;
    }

    printf("\nNon-preemptive SJF Scheduling:\n");
    nonPreemptiveSJF(processes, n);

    return 0;
}
