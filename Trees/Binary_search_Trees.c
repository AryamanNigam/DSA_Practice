#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

node* get_new_node(int element) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = element;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

node* insert(node* root, int element) {
    if (root == NULL) {
        root = get_new_node(element);
    } 
    
    else if (element <= root->data) {
        root->left = insert(root->left, element);
    } 
    
    else {
        root->right = insert(root->right, element);
    }

    return root;
}

bool search(node* root, int element) {
    if (root == NULL) {
        return false;
    } 
    
    else if (root->data == element) {
        return true;
    } 
    
    else if (element <= root->data) {
        return search(root->left, element);
    } 
    
    else {
        return search(root->right, element);
    }
}

node* find_min(node* root) {
    while (root->left != NULL){
        root = root->left;
    }
    return root;
}

node* delete(node* root, int element) {
    if (root == NULL) {
        return root;
    } 
    else if (element < root->data) {
        root->left = delete(root->left, element);
    } 
    else if (element > root->data) {
        root->right = delete(root->right, element);
    } 
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } 
        
        else if (root->left == NULL) {
            node* temp = root;
            root = root->right;
            free(temp);
        } 
        
        else if (root->right == NULL) {
            node* temp = root;
            root = root->left;
            free(temp);
        } 
        
        else {
            node* temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

void in_order_traversal(node* root, int* result, int* pos) {
    if (root != NULL) {
        in_order_traversal(root->left, result, pos);
        result[(*pos)++] = root->data;
        in_order_traversal(root->right, result, pos);
    }
}

node* array_to_tree(int* arr, int size, int index) {
    if (index >= size || arr[index] == -1) {
        return NULL;
    }

    node* root = get_new_node(arr[index]);
    root->left = array_to_tree(arr, size, 2 * index + 1);
    root->right = array_to_tree(arr, size, 2 * index + 2);

    return root;
}

int* convert(node* root, int* returnSize) {
    int n;
    printf("Enter number of elements in the array you want to convert: ");
    scanf("%d", &n);
    int* arr =malloc(n * sizeof(int));
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    root = array_to_tree(arr, n, 0);

    int* result = (int*)malloc(n * sizeof(int));
    int pos = 0;
    in_order_traversal(root, result, &pos);
    *returnSize = pos;

    free(arr);
    return result;
}

void show_in_order(node* root) {
    if (root != NULL) {
        show_in_order(root->left);
        printf("%d ", root->data);
        show_in_order(root->right);
    }
}

int main() {
    node* root = NULL;
    int choice, element, returnSize;
    int* result;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert an element\n");
        printf("2. Search for an element\n");
        printf("3. Delete an element\n");
        printf("4. Convert array to in-order traversal array\n");
        printf("5. Print in-order traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                root = insert(root, element);
                break;
            case 2:
                printf("Enter element to search: ");
                scanf("%d", &element);
                if (search(root, element)) {
                    printf("Element found.\n");
                } else {
                    printf("Element not found.\n");
                }
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &element);
                root = delete(root, element);
                break;
            case 4:
                result = convert(root, &returnSize);
                printf("In-order traversal array: ");
                for (int i = 0; i < returnSize; i++) {
                    printf("%d ", result[i]);
                }
                printf("\n");
                free(result);
                break;
            case 5:
                printf("In-order traversal: ");
                show_in_order(root);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
