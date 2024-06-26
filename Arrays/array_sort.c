#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#define MAX_SIZE 1000

typedef struct {
    double bubbleTime;
    double selectionTime;
    double insertionTime;
    double quickTime;
    double mergeTime;
} SortTimes;

void genArray(int array[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }
}

void BubbleSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void SelectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
}

void InsertionSort(int array[], int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void MergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);

        // Merge operation within MergeSort function
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int L[n1], R[n2];

        for (int i = 0; i < n1; i++) {
            L[i] = array[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = array[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            array[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            array[k] = R[j];
            j++;
            k++;
        }
    }
}

void QuickSort(int array[], int low, int high) {
    while (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (array[j] <= pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }

        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        int pi = i + 1;

        QuickSort(array, low, pi - 1);
        low = pi + 1;
    }
}

double getTimeInSeconds() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER t;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t);
    return (double)t.QuadPart / frequency.QuadPart;
}

void automate(int test_sizes[], SortTimes results[], int numtests) {
    srand(time(NULL));

    for (int i = 0; i < numtests; i++) {
        double start, stop;
        int n = test_sizes[i];
        int *a = malloc(n * sizeof(int));
        int *b1 = malloc(n * sizeof(int));
        int *b2 = malloc(n * sizeof(int));
        int *b3 = malloc(n * sizeof(int));
        int *b4 = malloc(n * sizeof(int));
        int *b5 = malloc(n * sizeof(int)); // For Merge Sort

        genArray(a, n);
        for (int j = 0; j < n; j++) {
            b1[j] = a[j];
            b2[j] = a[j];
            b3[j] = a[j];
            b4[j] = a[j];
            b5[j] = a[j];
        }

        start = getTimeInSeconds();
        BubbleSort(b1, n);
        stop = getTimeInSeconds();
        results[i].bubbleTime = stop - start;

        start = getTimeInSeconds();
        SelectionSort(b2, n);
        stop = getTimeInSeconds();
        results[i].selectionTime = stop - start;

        start = getTimeInSeconds();
        InsertionSort(b3, n);
        stop = getTimeInSeconds();
        results[i].insertionTime = stop - start;

        start = getTimeInSeconds();
        QuickSort(b4, 0, n - 1);
        stop = getTimeInSeconds();
        results[i].quickTime = stop - start;

        // Merge Sort timing
        start = getTimeInSeconds();
        MergeSort(b5, 0, n - 1);
        stop = getTimeInSeconds();
        results[i].mergeTime = stop - start;

        free(a);
        free(b1);
        free(b2);
        free(b3);
        free(b4);
        free(b5);
    }
}

int main() {
    srand(time(NULL));
    SortTimes results[MAX_SIZE];

    int numtests = 15;
    int test_sizes[numtests];
    for (int i = 0; i < numtests; i++) {
        test_sizes[i] = (i + 1) * 10000;
    }

    automate(test_sizes, results, numtests);

    printf("\nTest Results:\n");

    printf("Bubble=\n");
    for (int i = 0; i < numtests; i++) {
        printf("(%d, %.6f)\n", (i + 1) * 10000, results[i].bubbleTime);
    }

    printf("Insertion=\n");
    for (int i = 0; i < numtests; i++) {
        printf("(%d, %.6f)\n", (i + 1) * 10000, results[i].insertionTime);
    }

    printf("Selection=\n");
    for (int i = 0; i < numtests; i++) {
        printf("(%d, %.6f)\n", (i + 1) * 10000, results[i].selectionTime);
    }

    printf("Quick=\n");
    for (int i = 0; i < numtests; i++) {
        printf("(%d, %.6f)\n", (i + 1) * 10000, results[i].quickTime);
    }

    printf("Merge=\n");
    for (int i = 0; i < numtests; i++) {
        printf("(%d, %.6f)\n", (i + 1) * 10000, results[i].mergeTime);
    }

    printf("\n");

    return 0;
}
