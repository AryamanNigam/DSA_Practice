#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* link;
} node;

node* add_beg(node* head, int element) {
    node* temp = malloc(sizeof(node));
    temp->data = element;
    temp->link = head;
    return temp; 
}

node* add_end(node* head, int element) {
    node* current = head;
    while (current->link != NULL) {
        current = current->link;
    }

    node* temp = malloc(sizeof(node));
    temp->data = element;
    temp->link = NULL;
    current->link = temp;

    return head; 
}

void insert(node* head, int element, int pos) {
    node* current = head;
    pos--;
    while (pos != 1 && current != NULL) {
        current = current->link;
        pos--;
    }

    if (current == NULL) {
        printf("Position is out of limits\n");
        return;
    }

    node* temp = malloc(sizeof(node));
    temp->data = element;
    temp->link = current->link;
    current->link = temp;
}

node* remove_beg(node* head) {
    node* temp = head;
    head = head->link;
    free(temp);
    return head;
}

node* remove_end(node* head) {
    if (head->link == NULL) {
        free(head);
        return NULL;
    }

    node* temp = head;
    while (temp->link->link != NULL) {
        temp = temp->link;
    }

    free(temp->link);
    temp->link = NULL;
    return head; 
}

void delete(node** head, int pos) {

    node* prev = NULL;
    node* current = *head;
    int count = 1;

    while (current != NULL && count != pos) {
        prev = current;
        current = current->link;
        count++;
    }

    if (current == NULL) {
        printf("Position is out of limits\n");
        return;
    }

    if (prev == NULL) { 
        *head = current->link;
    } else {
        prev->link = current->link;
    }

    free(current);
}

int search(node* head, int element) {
    int count = 1;
    node* current = head;
    while (current != NULL) {
        if (current->data == element) {
            return count;
        }
        current = current->link;
        count++;
    }

    return -1; 
}

void show(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }
    printf("\n");
}

int main() {
    node* head = NULL;
    int pos, element, choice;

    while (1) {
        printf("\nEnter the operation you would like to perform on the linked list:\n");
        printf("1. Add element to beginning\n");
        printf("2. Add element to end\n");
        printf("3. Add element to specific position\n");
        printf("4. Remove element from beginning\n");
        printf("5. Remove element from end\n");
        printf("6. Remove element from specific position\n");
        printf("7. Search for an element\n");
        printf("8. Show the linked list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to be added to the beginning: ");
                scanf("%d", &element);
                head = add_beg(head, element);
                break;
            case 2:
                printf("Enter the element to be added to the end: ");
                scanf("%d", &element);
                head = add_end(head, element);
                break;
            case 3:
                printf("Enter the element to be added: ");
                scanf("%d", &element);
                printf("Enter the position: ");
                scanf("%d", &pos);
                insert(head, element, pos);
                break;
            case 4:
                head = remove_beg(head);
                break;
            case 5:
                head = remove_end(head);
                break;
            case 6:
                printf("Enter the position to delete: ");
                scanf("%d", &pos);
                delete(&head, pos);
                break;
            case 7:
                printf("Enter the element to search for: ");
                scanf("%d", &element);
                int pos = search(head, element);
                if (pos == -1) {
                    printf("Element not found\n");
                } else {
                    printf("Element found at position %d\n", pos);
                }
                break;
            case 8:
                printf("\nLinked list: ");
                show(head);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}