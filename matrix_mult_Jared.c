//Code written here is for Jared's learning. The program in "matrix_mult.c"
//currently does not function.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "get_walltime.c"
#include <sys/time.h>

// Sources:
// ChatGPT assisted in the syntax of the program below
// https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
// Also assisted in writing to CSV files in the main

// Create a random nxn matrix
// TODO: Why does initial random values of matrix all the same for each time method is called
float** generate_matrix(int size) {
    float** matrix = (float**)malloc(size * sizeof(int*));
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (float*)malloc(size * sizeof(int));
    }

    // Random seed for number generation
    srand(time(0));

    // Fill the matrix with random numbers
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // matrix[i][j] = rand() % 100; // Adjust the range
            matrix[i][j] =  (float)rand()/(float)(RAND_MAX);
        }
    }

    return matrix;

}


// The function below is made to print the elements of the nxn matrix
void print_matrix(float** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function that multiplies matrix_a and matrix_b. Then adds the product to elements in matrix_c
static float** multiply_matrices(float** matrix_a, float** matrix_b, float** matrix_c, int size) {
    // From first example in HPSC textbook page 49
    for (int idx = 0; idx < size; idx++){
        for (int idy = 0; idy < size; idy++){
            for (int idz = 0; idz < size; idz++){
                // TODO: Make sure c is updated accordingly.
                matrix_c[idx][idy] += matrix_a[idx][idz] * matrix_b[idz][idy];
            }
        }
    }
    return matrix_c;
}    


// Function that frees memory for matrix_a, matrix_b, and matrix_c
void free_matrix_memory(float** matrix_a, float**matrix_b, float** matrix_c, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix_a[i]);
        free(matrix_b[i]);
        free(matrix_c[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(matrix_c);
}

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 1 and 500
    int size = 1 + rand() % (500); // size of the nxn matrix

    // Print the random number
    printf("Random Number: %d\n", size);

    // Create randomly generated matrices
    float** matrix_a = generate_matrix(size);
    float** matrix_b = generate_matrix(size);
    float** matrix_c = generate_matrix(size);

    // Print values of randomly generated matrices
    // printf("Initial values of matrix a, b, and c \n");
    // print_matrix(matrix_a, size);
    // printf("\n");
    // print_matrix(matrix_b, size);
    // printf("\n");
    // print_matrix(matrix_c, size);
    // printf("\n");

    // Clock time to measure multipy_matrices time
    struct timeval startTime, endTime;

    // Compute multiplication of matrices and measure time
    gettimeofday(&startTime, NULL);
    float** result = multiply_matrices(matrix_a, matrix_b, matrix_c, size);
    gettimeofday(&endTime, NULL);

    // Calculate the amount of time used
    double executionTime = (double)(endTime.tv_sec - startTime.tv_sec) +
                           (double)(endTime.tv_usec - startTime.tv_usec) / 1000000.0;


    // Calculate the number of mflops/s for matrix multiplication
    double Mflops_total = (2*pow(size,3) - pow(size,2)) / pow(10,6);
    double performance_mflops = ((double) Mflops_total) / ((double) executionTime);
    printf("Total number of Mflops: %f \n", Mflops_total);
    printf("Excution time: %f in seconds \n", executionTime);
    printf("Total performance flops in Mflops/s: %f \n", performance_mflops);

    // Print result matrix
    // printf("Result of Matrix Multiplication \n");
    // print_matrix(result, size);

    printf("Wall time take for matrix multiplication: %f seconds for N = %d. \n", executionTime, size);
    printf("Performance for matrix multiplication in Mflop/s: %f for N = %d. \n", performance_mflops, size);

    // Open the CSV file for writing
    FILE *csvFile = fopen("matrix_multiplication_team_8.csv", "a");

    if (csvFile == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // Write header to the CSV file
    fprintf(csvFile, "N,Time,Flops,Performance\n");

    // Write data to the CSV file
    fprintf(csvFile, "%d,%f,%f,%f\n", size, executionTime, Mflops_total, performance_mflops);

    // Close the CSV file
    fclose(csvFile);

    printf("CSV file written successfully.\n");

    // Free the memory for matrices
    free_matrix_memory(matrix_a, matrix_b, matrix_c, size);

    return 0;
}
