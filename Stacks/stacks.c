#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100

int top = -1;
int stack[MAX_SIZE];

void isempty(){
    if (top==MAX_SIZE-1) {
        printf("Stack is full\n");
    } else {
        printf("Stack is not full\n");
    }
}

void isfull(){
    if (top==-1) {
        printf("\nStack is empty\n");
    } else {
        printf("\nStack is not empty\n");
    }
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
                isempty();
                break;
            case 5:
                isfull();
                break;
            case 6:
                return 0;
            default:
                printf("\nInvalid choice\n");
                break;
        }
    }
}
