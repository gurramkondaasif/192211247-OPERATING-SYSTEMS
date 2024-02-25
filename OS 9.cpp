#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define BUF_SIZE 256
#define FILE_MAP_NAME "Local\\MyFileMappingObject"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        BUF_SIZE,                // Maximum object size (low-order DWORD)
        FILE_MAP_NAME);          // Name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n",
               GetLastError());
        return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // Handle to map object
                                   FILE_MAP_ALL_ACCESS, // Read/write permission
                                   0,
                                   0,
                                   BUF_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n",
               GetLastError());

        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter a message to write to shared memory: ");
    fgets((char*)pBuf, BUF_SIZE, stdin);

    printf("Press any key to read from shared memory...\n");
    _getch();

    printf("Message read from shared memory: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
