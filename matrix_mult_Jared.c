//Code written here is for Jared's learning. The program in "matrix_mult.c"
//currently does not function.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ChatGPT assisted in the syntax of the program below

// Create a random nxn matrix
// TODO: Why does initial random values of matrix all the same for each time method is called
int** generate_matrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    // Seed is need to generate a random number
    srand(time(NULL));

    // Fill the matrix with random numbers
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100; // Adjust the range
        }
    }

    return matrix;

}


// The function below is made to print the elements of the nxn matrix
void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

static int** multiply_matrices(int** matrix_a, int** matrix_b, int** matrix_c, int n) {
    // From first example in HPSC textbook page 49
    for (int idx = 0; idx < n; idx++){
        for (int idy = 0; idy < n; idy++){
            for (int idz = 0; idz < n; idz++){
                // TODO: Make sure c is updated accordingly.
                matrix_c[idx][idy] += matrix_a[idx][idz] * matrix_b[idz][idy];
            }
        }
    }
    return matrix_c;
}    


int main() {
    int size = 2; // size of the nxn matrix

    // Create randomly generated matrices
    int** matrix_a = generate_matrix(size);
    int** matrix_b = generate_matrix(size);
    int** matrix_c = generate_matrix(size);

    // Print values of randomly generated matrices
    printf("Initial values of matrix a, b, and c \n");
    print_matrix(matrix_a, size);
    print_matrix(matrix_b, size);
    print_matrix(matrix_c, size);

    // Compute multiplication of matrices
    int** result = multiply_matrices(matrix_a, matrix_b, matrix_c, size);

    // Print result matrix
    print_matrix(result, size);

    return 0;
}
