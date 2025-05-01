#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6
#define MAX_STORAGE 5

// Stack for Parts (LIFO) 
char stack[SIZE][20];
int top = -1;

// Push a part onto the stack
void push(char part[]) {
    strcpy(stack[++top], part);
}

// Pop the top part from the stack
void pop(char part[]) {
    strcpy(part, stack[top--]);
}

//  Queue-like Storage for Rovers (FIFO with overwrite) 
char storage[MAX_STORAGE][20];
int count = 0;

// Insert a rover into storage
void insert_rover(const char *rover) {
    if (count < MAX_STORAGE) { // If space is available
        strcpy(storage[count++], rover);
    } else { // Storage full, remove oldest and insert new rover
        printf("Deployed: %s\n", storage[0]);
        for (int i = 1; i < MAX_STORAGE; i++) {
            strcpy(storage[i - 1], storage[i]);
        }
        strcpy(storage[MAX_STORAGE - 1], rover);
    }
}

// Print all stored rovers
void print_storage() {
    printf("Current Storage:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", storage[i]);
    }
}

//  Singly Linked List for Faulty Rovers 
typedef struct Node {
    char name[20];
    struct Node* next;
} Node;

// Insert a faulty rover at the beginning
Node* insert_singly(Node* head, char name[]) {
    Node* new_node = malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->next = head;
    return new_node;
}

// Delete a faulty rover by name
Node* delete_singly(Node* head, char name[]) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return head; // Rover not found
    if (prev) prev->next = temp->next; // Middle or end
    else head = temp->next; // Head node
    free(temp);
    return head;
}

//  Doubly Linked List for Repaired Rovers 
typedef struct DNode {
    char name[20];
    struct DNode* prev;
    struct DNode* next;
} DNode;

// Insert a repaired rover at the front
DNode* insert_doubly(DNode* head, char name[]) {
    DNode* new_node = malloc(sizeof(DNode));
    strcpy(new_node->name, name);
    new_node->prev = NULL;
    new_node->next = head;
    if (head) head->prev = new_node;
    return new_node;
}

// Traverse repaired list forward
void traverse_forward(DNode* head) {
    printf("Forward: ");
    while (head) {
        printf("%s -> ", head->name);
        if (!head->next) break;
        head = head->next;
    }
    printf("NULL\n");
}

// Traverse repaired list backward
void traverse_backward(DNode* tail) {
    printf("Backward: ");
    while (tail) {
        printf("%s -> ", tail->name);
        tail = tail->prev;
    }
    printf("NULL\n");
}

//  Circular Linked List for Upgrades 
typedef struct CNode {
    char name[20];
    struct CNode* next;
} CNode;

// Insert an upgraded rover (after tail)
CNode* insert_circular(CNode* tail, char name[]) {
    CNode* new_node = malloc(sizeof(CNode));
    strcpy(new_node->name, name);
    if (!tail) { // First node, points to itself
        new_node->next = new_node;
        return new_node;
    } else {
        new_node->next = tail->next;
        tail->next = new_node;
        return new_node;
    }
}

// Traverse circular list multiple times
void traverse_circular(CNode* tail, int cycles) {
    if (!tail) return;
    CNode* current = tail->next;
    for (int i = 0; i < cycles; i++) {
        do {
            printf("%s -> ", current->name);
            current = current->next;
        } while (current != tail->next);
        printf("(cycle %d done)\n", i + 1);
    }
}

//  Main Function 
int main() {
    // Stack Demonstration 
    printf("Stack Operations (Parts Repair Order) \n");
    char parts[SIZE][20] = {"Drill", "Wheel", "Camera", "Arm", "Battery", "Sonar"};
    char temp[20];
    
    for (int i = 0; i < SIZE; i++) {
        push(parts[i]);
    }
    
    printf("Repair Order:\n");
    for (int i = 0; i < SIZE; i++) {
        pop(temp);
        printf("%s\n", temp);
    }

    // Storage Demonstration 
    printf("\n Queue Operations (Rover Storage) \n");
    char *rovers[] = {"Rov1", "Rov2", "Rov3", "Rov4", "Rov5", "Rov6", "Rov7"};
    int total = sizeof(rovers) / sizeof(rovers[0]);
    
    for (int i = 0; i < total; i++) {
        insert_rover(rovers[i]);
    }
    print_storage();

    // Linked List Demonstration 
    printf("\n Linked List Operations (Faulty and Repaired Rovers) \n");
    Node* faulty = NULL;
    DNode* repaired = NULL;

    faulty = insert_singly(faulty, "Rov6");
    faulty = insert_singly(faulty, "Rov3");

    faulty = delete_singly(faulty, "Rov3"); // Simulate repairing Rov3
    repaired = insert_doubly(repaired, "Rov3");

    printf("Repaired List (forward):\n");
    traverse_forward(repaired);
    printf("Repaired List (backward):\n");
    traverse_backward(repaired);

    // Circular Linked List Demonstration
    printf("\n Circular Linked List (Upgraded Rovers) \n");
    CNode* upgrades = NULL;
    upgrades = insert_circular(upgrades, "Rov1");
    upgrades = insert_circular(upgrades, "Rov4");

    traverse_circular(upgrades, 2); // Show upgrades in 2 cycles

    return 0;
}
