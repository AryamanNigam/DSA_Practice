#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

int top = -1;
int stack[MAX_SIZE];

bool isempty() {
    return (top ==-1);
}

bool isfull() {
    return (top == MAX_SIZE-1);
}

void push(int data){
    if (top ==MAX_SIZE-1) {
        fprintf(stderr, "\nStack Overflow\n");
        return;
    } else {
        top = top+1;
        stack[top] = data;
    }
}

int pop(){
    if (top==-1) {
        fprintf(stderr, "\nStack is empty\n");
        return -1;
    } else {
        int data = stack[top];
        top = top-1;
        return data;
    }
}

int peek(){
    if (top==-1) {
        fprintf(stderr, "\nStack is empty\n");
        return-1;
    } else {
        return stack[top];
    }
}

int main(){
    int choice, data;
    bool empty, full;
    while (1){
        printf("\nEnter the operation you would like to do to stack\n");
        printf("To push press 1\n");
        printf("To pop press 2\n");
        printf("To peek press 3\n");
        printf("To check if stack is full press 4\n");
        printf("To check if stack is empty press 5\n");
        printf("To exit, press 6\n\n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("\nEnter the element to be added onto the stack: ");
                scanf("%d", &data);
                push(data);
                break;
            case 2:
                data = pop();
                if (data!=-1) {
                    printf("\nPopped element: %d\n", data);
                }
                break;
            case 3:
                data = peek();
                if (data != -1) {
                    printf("\nTop element: %d", data);
                }
                break;
            case 4:
                full = isfull();
                if (full) {
                    printf("\nStack is full\n");
                } else {
                    printf("\nStack is not full\n");
                }
                break;
            case 5:
                empty = isempty();
                if (empty) {
                    printf("\nStack is empty\n");
                } else {
                    printf("\nStack is not empty\n");
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
