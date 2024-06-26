#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX_SIZE 1000

void genIncreasingArray(int array[], int n) {
    srand(time(NULL));
    array[0] = rand() % 10;
    for (int i = 1; i < n; i++) {
        array[i] = array[i - 1] + rand() % 10;
    }
}

int LinearSearch(int array[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (array[i] == x) {
            return i;
        }
    }
    return -1;
}

int BinarySearch(int array[], int n, int y) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == y) {
            return mid;
        } else if (array[mid] > y) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1;
}

typedef struct {
    int n;
    double LinearTime;
    double BinaryTime;
} TestResult;

double getTimeInSeconds() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER t;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t);
    return (double)t.QuadPart / frequency.QuadPart;
}

void automate(int test_sizes[], TestResult results[MAX_SIZE], int numtests) {
    srand(time(NULL));

    for (int i = 0; i < numtests; i++) {
        double start, stop;
        int n = test_sizes[i];
        int *a = malloc(n * sizeof(int));

        genIncreasingArray(a, n);

        int targetIndex = n - 100;
        if (targetIndex < 0) targetIndex = 0; 
        int x = a[targetIndex];


        start = getTimeInSeconds();
        LinearSearch(a, n, x);
        stop = getTimeInSeconds();
        double linearTime = stop - start;

        start = getTimeInSeconds();
        BinarySearch(a, n, x);
        stop = getTimeInSeconds();
        double binaryTime = stop - start;

        results[i].n = n;
        results[i].LinearTime = linearTime;
        results[i].BinaryTime = binaryTime;

        free(a);
    }
}

int main() {
    srand(time(NULL));
    TestResult results[MAX_SIZE];

    int numtests = 15;
    int test_sizes[numtests];
    for (int i = 0; i < numtests; i++) {
        test_sizes[i] = (i + 1) * 100000;
    }

    automate(test_sizes, results, numtests);

    printf("\n\nTest Results:\n");
    for (int i = 0; i < numtests; i++) {
        printf("\nn = %d, Linear Search Time = %f seconds, Binary Search Time = %f seconds\n", results[i].n, results[i].LinearTime, results[i].BinaryTime);
    }

    return 0;
}
