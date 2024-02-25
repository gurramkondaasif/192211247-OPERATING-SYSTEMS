#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    FILE *source_fp, *dest_fp;
    size_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    // Open source file for reading
    source_fp = fopen(argv[1], "rb");
    if (source_fp == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file for writing (create it if it doesn't exist)
    dest_fp = fopen(argv[2], "wb");
    if (dest_fp == NULL) {
        perror("Error opening destination file");
        fclose(source_fp);
        return 1;
    }

    // Copy contents
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_fp)) > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, dest_fp);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            fclose(source_fp);
            fclose(dest_fp);
            return 1;
        }
    }

    if (ferror(source_fp)) {
        perror("Error reading from source file");
        fclose(source_fp);
        fclose(dest_fp);
        return 1;
    }

    // Close files
    fclose(source_fp);
    fclose(dest_fp);

    printf("File copied successfully.\n");

    return 0;
}
