#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_CLASSES 30

// Structure to store student data
typedef struct {
    int id;
    char name[100];
    int attendance[MAX_CLASSES];
    int total_classes;
    int attended_classes;
} Student;

// Function to calculate attendance percentage
float calculate_attendance(Student *student) {
    student->attended_classes = 0;
    for (int i = 0; i < student->total_classes; i++) {
        student->attended_classes += student->attendance[i];
    }
    return ((float)student->attended_classes / student->total_classes) * 100;
}



// Function to input student data
void input_student_data(Student *student, int total_classes) {
    student->total_classes = total_classes;
    printf("\033[1;33mEnter student ID: \033[0m");
    scanf("%d", &student->id);
    getchar(); // to consume the newline character
    printf("\033[1;33mEnter student name: \033[0m");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = 0; // Remove newline character

    printf("\033[1;33mEnter attendance for %d classes (1 for present, 0 for absent):\033[0m\n", total_classes);
    for (int i = 0; i < total_classes; i++) {
        printf("Class %d: ", i + 1);
        while (1) {
            int status;
            scanf("%d", &status);
            if (status == 0 || status == 1) {
                student->attendance[i] = status;
                break;
            } else {
                printf("\033[1;31mInvalid input! Please enter 1 (present) or 0 (absent).\033[0m\n");
            }
        }
    }
}

// Function to display the attendance list of students
void display_attendance_list(Student students[], int num_students) {
    printf("\033[1;36m\nAttendance List:\033[0m\n");
    printf("\033[1;37m-------------------------------------------------------------\033[0m\n");
    printf("| \033[1;33m%-10s\033[0m | \033[1;33m%-25s\033[0m | \033[1;33m%-10s\033[0m | \033[1;33m%-10s\033[0m |\n", "Student ID", "Student Name", "Attendance", "Percentage");
    printf("\033[1;37m-------------------------------------------------------------\033[0m\n");

    for (int i = 0; i < num_students; i++) {
        // Calculate attendance percentage
        float percentage = calculate_attendance(&students[i]);

        // Check if attendance is below 75% and highlight
        if (percentage < 75) {
            // Print in red for low attendance
            printf("\033[1;31m");  // Set text color to red
        } else {
            // Print in green for good attendance
            printf("\033[1;32m");  // Set text color to green
        }

        // Print the student info
        printf("| %-10d | %-25s | ", students[i].id, students[i].name);
        for (int j = 0; j < students[i].total_classes; j++) {
            printf("%d ", students[i].attendance[j]);
        }

        // Print the attendance percentage
        printf("| %-10.2f |\n", percentage);

        // Reset to default color
        printf("\033[0m");  // Reset to default color
    }

    printf("\033[1;37m-------------------------------------------------------------\033[0m\n");
}


    

// Function to show the main menu
void show_menu() {
    printf("\033[1;36m\n---------- Attendance Management System ----------\033[0m\n");
    printf("1. Enter student data\n");
    printf("2. Display attendance list\n");
    
    printf("3. Exit\n");
    printf("\033[1;36m--------------------------------------------------\033[0m\n");
    printf("\033[1;33mPlease choose an option: \033[0m");
}

int main() {
    int num_students = 0, total_classes = 0;
    Student students[MAX_STUDENTS];
    int choice;

    // Display menu
    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\033[1;33mEnter the total number of students: \033[0m");
                scanf("%d", &num_students);
                printf("\033[1;33mEnter the total number of classes: \033[0m");
                scanf("%d", &total_classes);

                for (int i = 0; i < num_students; i++) {
                    printf("\nEnter data for student %d:\n", i + 1);
                    input_student_data(&students[i], total_classes);
                }
                break;

            case 2:
                display_attendance_list(students, num_students);
                break;

            

            case 3:
                printf("\033[1;32mExiting the system...\033[0m\n");
                exit(0);
                break;

            default:
                printf("\033[1;31mInvalid option! Please try again.\033[0m\n");
        }
    }

    return 0;
}
