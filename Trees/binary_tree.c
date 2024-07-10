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
        return get_new_node(element);
    }

    if (root->left == NULL) {
        root->left = insert(root->left, element);
    } 
    else if (root->right == NULL) {
        root->right = insert(root->right, element);
    } 
    else {
        root->left = insert(root->left, element);
    }

    return root;
}


bool search(node* root, int element) {
    if (root == NULL) {
        return false;
    }
    if (root->data == element) {
        return true;
    }

    bool found_in_left = search(root->left, element);
    if (found_in_left) {
        return true;
    }
    return search(root->right, element);
}

node* delete(node* root, int element) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == element) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        if (root->left != NULL) {
            root->data = root->left->data;
            root->left = delete(root->left, root->left->data);
        } 
        else if (root->right != NULL) {
            root->data = root->right->data;
            root->right = delete(root->right, root->right->data);
        }
    } 
    
    else {
        root->left = delete(root->left, element);
        root->right = delete(root->right, element);
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


node* array_to_tree(int* arr, int size) {
    node* root = NULL;
    for (int i = 0; i < size; i++) {
        if (arr[i] != -1) {
            root = insert(root, arr[i]);
        }
    }
    return root;
}


int* convert(node* root, int* returnSize) {
    int n;
    printf("Enter number of elements in the array you want to convert: ");
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    root = array_to_tree(arr, n);

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
