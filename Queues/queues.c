#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Include for boolean type

#define MAX_SIZE 100

int front = -1;
int rear = -1;
int queue[MAX_SIZE];

bool isempty(){
    return (front == -1 && rear == -1);
}

bool isfull(){
    return (rear == MAX_SIZE - 1);
}

void enqueue(int data){
    if (isfull()) {
        fprintf(stderr, "\nQueue is full\n");
        return;
    }
    if (front == -1){
        front = 0;
    }
    rear++;
    queue[rear] = data;
}

int dequeue(){
    if (isempty()) {
        fprintf(stderr, "\nQueue is empty\n");
        return -1;
    }
    int data = queue[front];
    front++;
    if (front > rear) {
        front = rear = -1;
    }
    return data;
}

int peek(){
    if (isempty()) {
        fprintf(stderr, "\nQueue is empty\n");
        return -1;
    }
    return queue[front];
}

int main(){
    int choice, data;
    bool empty, full;
    while (1) {
        printf("\n\nEnter the operation you would like to do to queue\n");
        printf("To enqueue, press 1\n");
        printf("To dequeue, press 2\n");
        printf("To peek, press 3\n");
        printf("To check if queue is full, press 4\n");
        printf("To check if queue is empty, press 5\n");
        printf("To exit, press 6\n\n");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("\nEnter the element to be added into the queue: ");
                scanf("%d", &data);
                enqueue(data);
                break;
            case 2:
                data = dequeue();
                if (data != -1) {
                    printf("\nDequeued element: %d\n", data);
                }
                break;
            case 3:
                data = peek();
                if (data != -1) {
                    printf("\nFront element: %d", data);
                }
                break;
            case 4:
                full = isfull();
                if (full) {
                    printf("\nQueue is full\n");
                } else {
                    printf("\nQueue is not full\n");
                }
                break;
            case 5:
                empty = isempty();
                if (empty){
                    printf("\nQueue is empty\n");
                } else {
                    printf("\nQueue is not empty\n");
                }
                break;
            case 6:
                return 0;
            default:
                printf("\nInvalid choice\n");
                break;
        }
    }
}
