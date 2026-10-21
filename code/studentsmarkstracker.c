#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 3

// Structure to hold student details
struct Student {
    int roll_no;
    char name[50];
    float marks[NUM_SUBJECTS];
    float total;
    float percentage;
    char grade;
};

// Function prototypes
char calculateGrade(float percentage);
void addStudents(struct Student students[], int *count);
void displayAll(struct Student students[], int count);
void searchStudent(struct Student students[], int count);

int main() {
    struct Student students[MAX_STUDENTS];
    int student_count = 0;
    int choice;

    do {
        printf("\n====================================");
        printf("\n    STUDENT MARKS TRACKER SYSTEM    ");
        printf("\n====================================");
        printf("\n1. Add Student Records");
        printf("\n2. Display All Student Progress");
        printf("\n3. Search Student by Roll Number");
        printf("\n4. Exit");
        printf("\n====================================");
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudents(students, &student_count);
                break;
            case 2:
                displayAll(students, student_count);
                break;
            case 3:
                searchStudent(students, student_count);
                break;
            case 4:
                printf("\nExiting program. Thank you for using the tracker!\n");
                break;
            default:
                printf("\nInvalid choice! Please select an option between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

// Helper function to assign grades based on percentage thresholds
char calculateGrade(float percentage) {
    if (percentage >= 90) return 'A';
    if (percentage >= 80) return 'B';
    if (percentage >= 70) return 'C';
    if (percentage >= 60) return 'D';
    if (percentage >= 40) return 'E';
    return 'F';
}

// Function to enter and process new student metrics
void addStudents(struct Student students[], int *count) {
    int num;
    printf("\nHow many students do you want to add? ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        if (*count >= MAX_STUDENTS) {
            printf("\nStorage limit reached! Cannot add more students.\n");
            return;
        }

        struct Student s;
        s.total = 0;

        printf("\n--- Entering Details for Student %d ---", *count + 1);
        printf("\nEnter Roll Number: ");
        scanf("%d", &s.roll_no);
        
        // Clear input buffer before reading the name string
        getchar(); 
        printf("Enter Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline character from fgets

        printf("Enter marks for %d subjects (out of 100):\n", NUM_SUBJECTS);
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            do {
                printf("  Subject %d: ", j + 1);
                scanf("%f", &s.marks[j]);
                if (s.marks[j] < 0 || s.marks[j] > 100) {
                    printf("  Invalid marks! Please input a value between 0 and 100.\n");
                }
            } while (s.marks[j] < 0 || s.marks[j] > 100);
            
            s.total += s.marks[j];
        }

        s.percentage = (s.total / (NUM_SUBJECTS * 100)) * 100;
        s.grade = calculateGrade(s.percentage);

        // Store the compiled object into our array tracking mechanism
        students[*count] = s;
        (*count)++;
    }
    printf("\nRecords added successfully!\n");
}

// Function to present all compiled data points in a table format
void displayAll(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records found. Please add records first!\n");
        return;
    }

    printf("\n========================================================================\n");
    printf("%-7s %-20s %-15s %-12s %-6s", "Roll No", "Name", "Total Marks", "Percentage", "Grade");
    printf("\n========================================================================\n");
    
    for (int i = 0; i < count; i++) {
        char marks_str[20];
        sprintf(marks_str, "%.1f/%d", students[i].total, NUM_SUBJECTS * 100);
        printf("%-7d %-20s %-15s %-12.2f %-6c\n", 
               students[i].roll_no, 
               students[i].name, 
               marks_str, 
               students[i].percentage, 
               students[i].grade);
    }
    printf("========================================================================\n");
}

// Function to query a specific student by Roll Number
void searchStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records found to search!\n");
        return;
    }

    int search_roll;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &search_roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == search_roll) {
            printf("\n--- Record Found ---");
            printf("\nRoll Number: %d", students[i].roll_no);
            printf("\nName:        %s", students[i].name);
            printf("\nMarks:       ");
            for(int j = 0; j < NUM_SUBJECTS; j++) {
                printf("[Sub%d: %.1f] ", j + 1, students[i].marks[j]);
            }
            printf("\nPercentage:  %.2f%%", students[i].percentage);
            printf("\nGrade:       %c\n", students[i].grade);
            return;
        }
    }
    printf("\nStudent with Roll Number %d not found.\n", search_roll);
}
