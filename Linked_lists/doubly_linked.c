#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    struct node *prev;
    int data;
    struct node *next;   
}node;

node* add_beg (node* head, int element){
    struct node *temp=malloc(sizeof(node));
    temp->prev=NULL;
    temp->next=NULL;

    temp->data=element;

    temp->next=head;
    if (head != NULL) {
        head->prev = temp;
    }
    head = temp;
    return head;
}

node* add_end(node *head, int element){
    struct node *current = head;
    struct node *temp = malloc(sizeof(node));

    temp->prev = NULL;
    temp->next = NULL;
    temp->data = element;

    if (head == NULL) {
        return temp;
    }

    while(current->next != NULL){
        current = current->next;
    }

    current->next = temp;
    temp->prev = current;

    return head;
}

node* insert(node* head, int element, int pos){
    struct node *current, *current2, *ptr;
    current = head;
    
    ptr = malloc(sizeof(node));
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->data = element;

    if(pos == 1){
        ptr->next = head;
        if(head != NULL){
            head->prev = ptr;
        }
        head = ptr;
        return head;
    }

    while(pos != 1 && current != NULL){
        current = current->next;
        pos--;
    }

    if (current == NULL) {
        printf("Position is out of limits\n");
        free(ptr);
        return head;
    }

    if(current->next == NULL){
        current->next = ptr;
        ptr->prev = current;
    } else {
        current2 = current->next;
        current->next = ptr;
        ptr->prev = current;
        ptr->next = current2;
        current2->prev = ptr;
    }
    return head;
}

node* remove_beg(node* head) {
    if (head == NULL) {
        printf("Linked list is empty\n");
        return NULL;
    }
    node* current = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(current);
    return head;
}

node* remove_end(node* head) {
    if (head == NULL) {
        printf("Linked list is empty\n");
        return NULL;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    node *current2 = current->prev;
    current2->next = NULL;

    free(current);
    return head;
}

node* delete(node* head, int pos) {
    if (head == NULL) {
        printf("Linked list is empty\n");
        return NULL;
    }

    node *current = head;
    if (pos == 1) {
        return remove_beg(head);
    }

    while (pos > 1 && current != NULL) {
        current = current->next;
        pos--;
    }

    if (current == NULL) {
        printf("Position is out of limits\n");
        return head;
    }

    if (current->next == NULL) {
        return remove_end(head);
    }

    node *current2 = current->prev;
    current2->next = current->next;
    current->next->prev = current2;

    free(current);
    return head;
}

void show(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int search(node *head, int element) {
    int count = 1;
    node *current = head;
    while (current != NULL) {
        if (current->data == element) {
            printf("Element is found at position %d\n", count);
            return count;
        }
        current = current->next;
        count++;
    }
    printf("Element not found\n");
    return -1;
}

int main() {
    node* head = NULL;
    int pos, element, choice;

    while (1) {
        printf("\nEnter the operation you would like to perform on the doubly linked list:\n");
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
                head = insert(head, element, pos);
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
                head = delete(head, pos);
                break;
            case 7:
                printf("Enter the element to search for: ");
                scanf("%d", &element);
                pos = search(head, element);
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
