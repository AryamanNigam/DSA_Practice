#include <stdio.h>
#include <math.h>
#define MAX 256

typedef struct node{
    int key;
    int value;

    struct node *next;
}node;

typedef struct hashMap{
    int capacity, num;
    struct node **arr;
}hashMap;


void init(hashMap *mp){
    mp->capacity = 256;
    mp->num = 0;

    mp->arr = (node **)malloc(sizeof(node*) * mp->capacity);
    return;
}

void setValues(node *head, int k, int v){
    head->key = k;
    head->value = v;
    head->next = NULL;
}

int hashFunction(int key){
    double a = 1.0 / 3.14;
    double i;

    double f = modf(key * a, &i);

    float m = 256 * f;

    modf(m, &i);
    int index = (int) i;

    return index;
}

void insert(hashMap *mp, int key, int value){
    int bucketIndex = hashFunction(key);

    node *newnode = malloc(sizeof(node));

    setValues(newnode, key, value);
    
    if(mp->arr[bucketIndex] == NULL){
        mp->arr[bucketIndex] = newnode;
    }
    else{
        newnode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newnode;
    }
    return;
}

void delete(hashMap *mp, int key){
    int bucketIndex = hashFunction(key);
    node *prev = NULL;
    node *current = mp->arr[bucketIndex];
    while (current != NULL){
        if(key == current->key){
            if(current = mp->arr[bucketIndex]){
                mp->arr[bucketIndex] = current->next;
            }
            else{
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    return;
}

int search(hashMap *mp, int key){
    int bucketIndex = hashFunction(key);
    node *current = mp->arr[bucketIndex];
    int flag = 0;

    while(current != NULL){
        if(current->key == key){
            flag = 1;
            return current->value;
        }
        current = current->next;
    }

    if(flag == 0){
        return -1;
    }
}

void show(hashMap *mp){
    for(int i = 0; i < MAX; i++){
        node *current = mp->arr[i];
        while(current != NULL){
            printf("%d ", current->value);
            current = current->next;
        }
    }
}

int main(){
    struct hashMap *mp = (hashMap*)malloc(sizeof(hashMap));
    init(mp);
    int choice;
    int key, value;

    while (1) {
        printf("\nEnter the operation you would like to perform on the hash table:\n");
        printf("1. Add element\n");
        printf("2. Delete element\n");
        printf("3. Search for an element\n");
        printf("4. Show the elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter the key \n");
                scanf("%d", &key);
                printf("Enter the value\n");
                scanf("%d", &value);
                insert(mp, key, value);
                break;
            case 2:
                printf("Enter the key\n");
                scanf("%d", &key);
                delete(mp, key);
                break;
            case 3:
                printf("Enter the key\n");
                scanf("%d", &key);
                int result = search(mp, key);
                if(result == -1){
                    printf("No such element is present\n");
                }
                else{
                    printf("The value of the key is: %d \n", result);
                }
                break;
            case 4:
                show(mp);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}