#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid, parent_pid;

    // Create a new process
    child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", child_pid);
    } else {
        // Fork failed
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}
