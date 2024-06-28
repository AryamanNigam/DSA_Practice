#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100

int front = -1;
int rear = -1;
int queue[MAX_SIZE];

void isempty(){
    if (front == -1&& rear == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is not empty\n");
    }
}

void isfull(){
    if (rear==MAX_SIZE-1) {
        printf("\nQueue is full\n");
    } else {
        printf("\nQueue is not full\n");
    }
}

void enqueue(int data){
    if (rear==MAX_SIZE-1) {
        fprintf(stderr, "\nQueue is full\n");
        return;
    }
    if (front==-1) {
        front=0;
    }
    rear++;
    queue[rear]=data;
}

int dequeue() {
    if (front == -1 || front > rear) {
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

int peek() {
    if (front == -1) {
        fprintf(stderr, "\nQueue is empty\n");
        return -1;
    }
    return queue[front];
}

int main() {
    int choice, data;
    while (1) {
        printf("\n\nEnter the operation you would like to do to queue\n");
        printf("To enqueue, press 1\n");
        printf("To dequeue, press 2\n");
        printf("To peek, press 3\n");
        printf("To check if queue is full, press 4\n");
        printf("To check if queue is empty, press 5\n");
        printf("To exit, press 6\n\n");
        scanf("%d", &choice);

        switch (choice) {
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
                isfull();
                break;
            case 5:
                isempty();
                break;
            case 6:
                return 0;
            default:
                printf("\nInvalid choice\n");
                break;
        }
    }
}
