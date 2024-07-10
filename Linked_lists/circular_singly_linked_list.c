#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node* add_beg(node *tail, int element) {
    node *current = malloc(sizeof(node));
    current->data = element;
    
    if (tail == NULL) {
        tail = current;
        tail->next = tail;
    } else {
        current->next = tail->next;
        tail->next = current;
    }
    return tail;
}

node* add_end(node *tail, int element) {
    node *current = malloc(sizeof(node));
    current->data = element;

    if (tail == NULL) {
        tail = current;
        tail->next = tail;
    } else {
        current->next = tail->next;
        tail->next = current;
        tail = current;
    }
    return tail;
}

node* insert(node *tail, int element, int pos) {
    if (tail == NULL) {
        printf("List is empty\n");
        return tail;
    }

    node *current = tail->next;
    node *current2 = malloc(sizeof(node));
    current2->data = element;

    while (pos > 1 && current != tail) {
        current = current->next;
        pos--;
    }

    current2->next = current->next;
    current->next = current2;

    if (current == tail) {
        tail = current2;
    }

    return tail;
}

node* remove_beg(node *tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return tail;
    }

    node* current = tail->next;

    if (tail == current) {
        free(tail);
        tail = NULL;
    } else {
        tail->next = current->next;
        free(current);
    }

    return tail;
}

node* remove_end(node *tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return tail;
    }

    node *current = tail->next;

    if (tail == current) {
        free(tail);
        tail = NULL;
    } else {
        while (current->next != tail) {
            current = current->next;
        }

        current->next = tail->next;
        free(tail);
        tail = current;
    }

    return tail;
}

node* delete(node *tail, int pos) {
    if (tail == NULL) {
        printf("List is empty\n");
        return tail;
    }

    node *current = tail->next;

    if (pos == 1) {
       if (tail == current) { 
            free(tail);
            tail = NULL;
        } else {
            tail->next = current->next;
            free(current);
        }
        return tail;
    }

    if (tail == current && pos == 1) {
        free(tail);
        tail = NULL;
        return tail;
    }

    while (pos > 1 && current->next != tail) {
        current = current->next;
        pos--;
    }

    node *current2 = current->next;

    current->next = current2->next;

    if (current2 == tail) {
        tail = current;
    }

    free(current2);

    return tail;
}

void show(node *tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return;
    }

    node *current = tail->next;

    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != tail->next);

    printf("\n");
}

int search(node *tail, int element) {
    if (tail == NULL) {
        return -1;
    }

    node *current = tail->next;
    int count = 0;

    do {
        if (current->data == element) {
            return count;
        }
        current = current->next;
        count++;
    } while (current != tail->next);

    return -1;
}

int main() {
    node* tail = NULL;
    int pos, element, choice;

    while (1) {
        printf("\nEnter the operation you would like to perform on the Circular Singly linked list:\n");
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
                tail = add_beg(tail, element);
                break;
            case 2:
                printf("Enter the element to be added to the end: ");
                scanf("%d", &element);
                tail = add_end(tail, element);
                break;
            case 3:
                printf("Enter the element to be added: ");
                scanf("%d", &element);
                printf("Enter the position: ");
                scanf("%d", &pos);
                tail = insert(tail, element, pos);
                break;
            case 4:
                tail = remove_beg(tail);
                break;
            case 5:
                tail = remove_end(tail);
                break;
            case 6:
                printf("Enter the position to delete: ");
                scanf("%d", &pos);
                tail = delete(tail, pos);
                break;
            case 7:
                printf("Enter the element to search for: ");
                scanf("%d", &element);
                pos = search(tail, element);
                if (pos == -1) {
                    printf("Element not found\n");
                } else {
                    printf("Element found at position %d\n", pos);
                }
                break;
            case 8:
                printf("\nLinked list: ");
                show(tail);
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
