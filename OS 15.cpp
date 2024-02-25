#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 10
#define MAX_FILES_PER_DIR 10
#define MAX_FILENAME_LEN 50
#define MAX_DIRNAME_LEN 50

typedef struct {
    char name[MAX_FILENAME_LEN];
} File;

typedef struct {
    char name[MAX_DIRNAME_LEN];
    int num_files;
    File files[MAX_FILES_PER_DIR];
} Directory;

Directory directories[MAX_DIRS];
int num_dirs = 0;

Directory* findDirectory(const char* dirname) {
    for (int i = 0; i < num_dirs; i++) {
        if (strcmp(directories[i].name, dirname) == 0) {
            return &directories[i];
        }
    }
    return NULL;
}

void createDirectory(const char* dirname) {
    if (num_dirs >= MAX_DIRS) {
        printf("Cannot create directory. Maximum directories reached.\n");
        return;
    }
    strcpy(directories[num_dirs].name, dirname);
    directories[num_dirs].num_files = 0;
    num_dirs++;
    printf("Directory '%s' created successfully.\n", dirname);
}

void listDirectoriesAndFiles() {
    printf("Directories:\n");
    for (int i = 0; i < num_dirs; i++) {
        printf("- %s\n", directories[i].name);
        printf("  Files:\n");
        for (int j = 0; j < directories[i].num_files; j++) {
            printf("  - %s\n", directories[i].files[j].name);
        }
    }
}

void createFileInDirectory(const char* dirname, const char* filename) {
    Directory* dir = findDirectory(dirname);
    if (dir == NULL) {
        printf("Directory '%s' not found.\n", dirname);
        return;
    }
    if (dir->num_files >= MAX_FILES_PER_DIR) {
        printf("Cannot create file in directory '%s'. Maximum files reached.\n", dirname);
        return;
    }
    strcpy(dir->files[dir->num_files].name, filename);
    dir->num_files++;
    printf("File '%s' created successfully in directory '%s'.\n", filename, dirname);
}

int main() {
    int choice;
    char dirname[MAX_DIRNAME_LEN];
    char filename[MAX_FILENAME_LEN];

    printf("Welcome to Two Level Directory Management System\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create directory\n");
        printf("2. List directories and files\n");
        printf("3. Create file in directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the name of the directory to create: ");
                scanf("%s", dirname);
                createDirectory(dirname);
                break;
            case 2:
                printf("\nListing directories and files:\n");
                listDirectoriesAndFiles();
                break;
            case 3:
                printf("\nEnter the name of the directory to create the file in: ");
                scanf("%s", dirname);
                printf("Enter the name of the file to create: ");
                scanf("%s", filename);
                createFileInDirectory(dirname, filename);
                break;
            case 4:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
