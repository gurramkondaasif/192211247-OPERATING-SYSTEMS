#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"
#define MAX_EMPLOYEES 100
#define NAME_LENGTH 50

typedef struct {
    int emp_id;
    char emp_name[NAME_LENGTH];
    float emp_salary;
} Employee;

void addEmployee() {
    FILE *fp;
    Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.emp_id);
    printf("Enter employee name: ");
    scanf("%s", emp.emp_name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.emp_salary);

    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&emp, sizeof(Employee), 1, fp);
    fclose(fp);

    printf("Employee added successfully.\n");
}

void displayEmployees() {
    FILE *fp;
    Employee emp;

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEmployee details:\n");
    printf("ID\tName\t\tSalary\n");
    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printf("%d\t%s\t\t%.2f\n", emp.emp_id, emp.emp_name, emp.emp_salary);
    }
    fclose(fp);
}

void updateEmployee() {
    FILE *fp;
    Employee emp;
    int empId, found = 0;

    printf("Enter employee ID to update: ");
    scanf("%d", &empId);

    fp = fopen(FILENAME, "r+b");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.emp_id == empId) {
            printf("Enter new name for employee: ");
            scanf("%s", emp.emp_name);
            printf("Enter new salary for employee: ");
            scanf("%f", &emp.emp_salary);
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Employee details updated successfully.\n");
    } else {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

void deleteEmployee() {
    FILE *fp, *temp;
    Employee emp;
    int empId, found = 0;

    printf("Enter employee ID to delete: ");
    scanf("%d", &empId);

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error opening file!\n");
        fclose(fp);
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.emp_id != empId) {
            fwrite(&emp, sizeof(Employee), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("Employee details deleted successfully.\n");
    } else {
        printf("Employee not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new employee\n");
        printf("2. Display all employees\n");
        printf("3. Update employee details\n");
        printf("4. Delete employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
