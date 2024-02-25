#include <stdio.h>
#include <windows.h>

#define BUF_SIZE 256
#define QUEUE_NAME L"\\\\.\\pipe\\MyMessageQueue" // Pipe name format for local namespaces

int main() {
    HANDLE hQueue;
    WCHAR buffer[BUF_SIZE];
    DWORD dwBytesRead;

    // Create a message queue
    hQueue = CreateNamedPipeW(
        QUEUE_NAME,               // Name of the pipe
        PIPE_ACCESS_DUPLEX,       // Read and write access
        PIPE_TYPE_MESSAGE |       // Message type pipe
        PIPE_READMODE_MESSAGE |   // Message-read mode
        PIPE_WAIT,                // Blocking mode
        PIPE_UNLIMITED_INSTANCES, // Max. instances
        BUF_SIZE,                 // Output buffer size
        BUF_SIZE,                 // Input buffer size
        0,                        // Client time-out
        NULL                      // Default security attribute
    );

    if (hQueue == INVALID_HANDLE_VALUE) {
        printf("Error creating named pipe. Exiting...\n");
        return 1;
    }

    printf("Named pipe created successfully. Waiting for client...\n");

    // Wait for client to connect
    if (ConnectNamedPipe(hQueue, NULL)) {
        printf("Client connected. Waiting for message...\n");

        // Read from the pipe
        if (ReadFile(hQueue, buffer, BUF_SIZE * sizeof(WCHAR), &dwBytesRead, NULL)) {
            wprintf(L"Received message from client: %s\n", buffer);
        } else {
            printf("Error reading from pipe. Exiting...\n");
            return 1;
        }
    } else {
        printf("Error connecting to client. Exiting...\n");
        return 1;
    }

    // Close the pipe handle
    CloseHandle(hQueue);

    return 0;
}
