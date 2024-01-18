#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate random dimensions for matrices A and B, with dimensions m * n, n * k
    // To begin with, the dimensions will be between 1 and 5
    int m = rand() % 5 + 1;  
    int n = rand() % 5 + 1;  
    int k = rand() % 5 + 1; 

    // Declare matrices A, B, and result
    int A[m][n], B[n][k], AB[m][k];

    // Initialize the resulting matri AB to zeros
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            AB[i][j] = 0;
        }
    }

    // Fill matrix A with random numbers
    // To begin with, the elements will be between 0 and 9
    printf("Matrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10; 
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    // For matrix B similarly
    printf("\nMatrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            B[i][j] = rand() % 10; 
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Perform matrix multiplication A * B
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < n; l++) {
                AB[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    // Print the result matrix
    printf("\nResult (A * B):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", AB[i][j]);
        }
        printf("\n");
    }

    return 0;
}
