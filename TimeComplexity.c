#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int linear(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x) {
            printf("found");
            return 1;
        }
    }
    return 0;
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int getlast(int a[], int n) {
    return a[n - 1];
}

int main() {
    clock_t start, end;
    int n, x, m;
    double c_time;

    printf("Input\nEnter size of array: ");
    if (scanf("%d", &n) != 1) return 1;

    int *a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("here automatically stores values in array.");
    for (int i = 0; i < n; i++) {
        a[i] = n - i;
    }

    printf("\nEnter value of x to be search: ");
    if (scanf("%d", &x) != 1) {
        free(a);
        return 1;
    }

    start = clock();
    linear(a, n, x);
    end = clock();
    c_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nOutput\nTime taken by linear search O(n): %lf\n", c_time);

    start = clock();
    bubbleSort(a, n);
    end = clock();
    c_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by bubble sort O(n^2): %lf\n", c_time);

    start = clock();
    m = getlast(a, n);
    end = clock();
    c_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by constant O(1): %lf\n\n", c_time);

    free(a);
    return 0;
}