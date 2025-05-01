#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Part Delivery and Arm
#define MAX 6
char queue[MAX][20];
char stack[MAX][20];
int front = 0, rear = 0, top = -1;

void enqueue(char part[]) {
    strcpy(queue[rear++], part);
}
void push(char part[]) {
    strcpy(stack[++top], part);
}
void partDeliveryAndArm() {
    char* parts[] = {"Drill", "Wheel", "Camera", "Arm", "Battery", "Sonar"};
    for (int i = 0; i < MAX; i++) enqueue(parts[i]);
    for (int i = 0; i < MAX; i++) push(queue[i]);
    printf("Repair Order (LIFO):\n");
    for (int i = top; i >= 0; i--) printf("%s\n", stack[i]);
}

// Assembly Storage Unit
#define BAY_SIZE 5
char bay[BAY_SIZE][10];
int bayCount = 0;

void addRover(char rover[]) {
    if (bayCount == BAY_SIZE) {
        printf("Deploying oldest: %s\n", bay[0]);
        for (int i = 1; i < BAY_SIZE; i++) strcpy(bay[i - 1], bay[i]);
        bayCount--;
    }
    strcpy(bay[bayCount++], rover);
}
void assemblyStorage() {
    char* rovers[] = {"Rov1", "Rov2", "Rov3", "Rov4", "Rov5", "Rov6", "Rov7"};
    for (int i = 0; i < 7; i++) addRover(rovers[i]);
    printf("Rovers in Bay:\n");
    for (int i = 0; i < bayCount; i++) printf("%s\n", bay[i]);
}

// Faulty Rover Tracker
typedef struct Node {
    char name[10];
    struct Node *next, *prev;
} Node;

Node *faultyList = NULL, *repairedHead = NULL, *repairedTail = NULL;

void insertFaulty(char name[]) {
    Node* n = malloc(sizeof(Node));
    strcpy(n->name, name);
    n->next = faultyList;
    faultyList = n;
}
void moveToRepaired(char name[]) {
    Node *prev = NULL, *curr = faultyList;
    while (curr && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;
    if (prev) prev->next = curr->next;
    else faultyList = curr->next;

    curr->prev = repairedTail;
    curr->next = NULL;
    if (repairedTail) repairedTail->next = curr;
    else repairedHead = curr;
    repairedTail = curr;
}
void showRepaired() {
    printf("Repaired (forward):\n");
    for (Node* n = repairedHead; n; n = n->next) printf("%s\n", n->name);
    printf("Repaired (backward):\n");
    for (Node* n = repairedTail; n; n = n->prev) printf("%s\n", n->name);
}

//  Priority Upgrades 
Node* priority = NULL;

void insertPriority(char name[]) {
    Node* n = malloc(sizeof(Node));
    strcpy(n->name, name);
    if (!priority) {
        n->next = n;
        priority = n;
    } else {
        n->next = priority->next;
        priority->next = n;
    }
}
void showPriority(int times) {
    if (!priority) return;
    Node* curr = priority->next;
    printf("Priority Cycle:\n");
    for (int i = 0; i < times; i++) {
        printf("%s\n", curr->name);
        curr = curr->next;
    }
}

// Main Function
int main() {
    printf(" Part Delivery and Arm \n");
    partDeliveryAndArm();

    printf("\nAssembly Storage \n");
    assemblyStorage();

    printf("\n Faulty Rover Tracker\n");
    insertFaulty("Rov3");
    insertFaulty("Rov6");
    moveToRepaired("Rov3");
    showRepaired();

    printf("\n Priority Upgrades\n");
    insertPriority("Rov1");
    insertPriority("Rov4");
    showPriority(4);  // 2 full cycles

    return 0;
}
