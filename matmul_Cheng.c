#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

// ChatGPT assisted code to run matrix multiplication and analysis
float** generate_matrix(int rows, int cols) {
    float** matrix = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float*)malloc(cols * sizeof(float));
    }

    // Fill the matrix with random numbers
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (float)rand() / (float)(RAND_MAX);
        }
    }

    return matrix;
}

float** multiply_matrices(float** A, float** B, int size) {
    float** AB = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++) {
        AB[i] = (float*)malloc(size * sizeof(float));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            AB[i][j] = 0;
            for (int l = 0; l < size; l++) {
                AB[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return AB;
}

int main() {
    srand(time(NULL));
    const int size = 5000;

    float** A = generate_matrix(size, size);
    float** B = generate_matrix(size, size);

    // Clock time to measure multiply_matrices time
    struct timeval startTime, endTime;

    // Compute multiplication of matrices and measure time
    gettimeofday(&startTime, NULL);
    float** AB = multiply_matrices(A, B, size);
    gettimeofday(&endTime, NULL);

    // Calculate the amount of time used
    double executionTime = (double)(endTime.tv_sec - startTime.tv_sec) +
                           (double)(endTime.tv_usec - startTime.tv_usec) / 1000000.0;

    // Calculate the number of mflops/s for matrix multiplication
    double Mflops_total = (2 * pow(size, 3) - pow(size, 2)) / pow(10, 6);
    double performance_mflops = Mflops_total / executionTime;
    printf("Total number of Mflops: %f \n", Mflops_total);
    printf("Execution time: %f seconds \n", executionTime);
    printf("Total performance in Mflops/s: %f \n", performance_mflops);

    // Free the allocated memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(AB[i]);
    }
    free(A);
    free(B);
    free(AB);

    return 0;
}
