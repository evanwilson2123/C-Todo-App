#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*This is a CLI Todo List / Task Tracker app built with C. 
 * In this project I reinforced my understanding of Memory management in C.
 * I also reinforced my knowlege of both Linked Lists and File operations.*/

// Task struct to store task data for representation and storage
typedef struct Task {
    int ID;
    char title[20];
    char description[256];
    int done; // 0 = not done, 1 = done
} Task;

// Node struct to manage linked list with Task as data
typedef struct Node {
    Task* data;
    struct Node* next;
} Node;


// Initialize the head of the linked list of tasks
struct Node* head = NULL;

// to keep track of the tasks
int taskCount = 0;

// Foward declarations of functions
void addTask();
void listTasks();
void markTaskDone(int taskID);
void saveToFile();
void loadFromFile();
void freeAllTasks();

// Function to add a task to the Linked-List of tasks
void addTask() {
    Task *newTask = (Task *)malloc(sizeof(Task));
    newTask->done = 0;

    newTask->ID = taskCount + 1;

    printf("Enter the title of your task: \n");
    fgets(newTask->title, sizeof(newTask->title), stdin);
    newTask->title[strcspn(newTask->title, "\n")] = '\0';

    printf("Enter the descrption of your task: \n");
    fgets(newTask->description, sizeof(newTask->description), stdin);
    newTask->description[strcspn(newTask->description, "\n")] = '\0';
    
    // Logging
    printf("\ntitle: %s\n", newTask->title);
    printf("description: %s\n", newTask->description);

    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newTask;
    if (head == NULL) {
        head = newNode;
        head->next = NULL;
        taskCount++;
        return;
    }
    newNode->next = head;
    head = newNode;
    
    taskCount++;

    return;
}

// Function to linearly traverse the list and print its contents
void listTasks() {
    Node* current = head;

    printf("\n");
    while (current != NULL) {
        printf("%d. %s -> %s Done? ", current->data->ID, current->data->title, current->data->description);
        if (current->data->done == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        current = current->next;
    }
}

// A function to mark a task as completed
void markTaskDone(int taskID) {
    Node *current = head;
    
    while (current != NULL && current->data->ID != taskID) {
        current = current->next;
    }
    if (current->data->ID == taskID) {
        current->data->done = 1;
    } else {
        printf("Invalid ID, Task not found\n");
        return;
    }
    printf("Task %s marked Done: %d\n", current->data->title, current->data->done);
    return;
}

void saveToFile() {
    
    // Open the file
    FILE *fp;
    fp = fopen("tasks.txt", "w");
    if (fp == NULL) {
        printf("Could not open file 'tasks.txt' for writing.\n");
        exit(1);
    }

    // - Iterate over each Task
    Node* current = head;
    while (current != NULL) {
        fprintf(fp, "%d|%s|%s|%d\n",
                current->data->ID,
                current->data->title,
                current->data->description,
                current->data->done);
        current = current->next;
    }
    
    fclose(fp);
    printf("Saved %d tasks to 'tasks.txt'\n", taskCount);
    return;
}

void loadFromFile() {
    // TODO
    return;
}

void freeAllTasks() {
    // TODO
    return;
}

int main() {
    int choice, taskID;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add a new task\n");
        printf("2. List all tasks\n");
        printf("3. Mark task as done\n");
        printf("4. Save tasks to file\n");
        printf("5. Load tasks from file\n");
        printf("6. Exit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                printf("Enter the ID of the task you wish to mark DONE (0 to exit): \n");
                scanf("%d", &taskID);
                if (taskID == 0) {
                    break;
                }
                markTaskDone(taskID);
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                loadFromFile();
                break;
            case 6:
                freeAllTasks();
                return 0;
            default:
                printf("Invalid choice, try again\n");
                break;
        }
    }

    return 0;
}
