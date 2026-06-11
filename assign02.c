#include <stdio.h>
#include <stdlib.h>

void space_constant(int n) {
    int a = 0, b = 1, c;
    c = a + b + n;
    printf("Constant space result for n=%d: %d\n", n, c);
}

void space_linear(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed for n=%d\n", n);
        return;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    printf("Linear space: first=%d, last=%d (n=%d)\n", arr[0], arr[n-1], n);
    free(arr);
}

void space_quadratic(int n) {
    int **mat = (int**)malloc(n * sizeof(int*));
    if (!mat) {
        printf("Memory allocation failed for rows, n=%d\n", n);
        return;
    }

    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
        if (!mat[i]) {
            printf("Memory allocation failed for row %d\n", i);
            for (int k = 0; k < i; k++) free(mat[k]);
            free(mat);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = i + j;
        }
    }

    printf("Quadratic space: mat[0][0]=%d, mat[n-1][n-1]=%d (n=%d)\n", 
           mat[0][0], mat[n-1][n-1], n);

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

int main() {
    int sizes[] = {10, 100, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        printf("\n=== For n = %d ===\n", n);
        space_constant(n);
        space_linear(n);
        space_quadratic(n);
    }

    return 0;
}