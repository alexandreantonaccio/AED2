#include <stdio.h>

#define SIZE 6

void multiplicaMatriz(double matrix[SIZE][SIZE], double vector[SIZE], double result[SIZE]) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (j = 0; j < SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

double calculateReproductionRate(double matrix[SIZE][SIZE]) {
    int i;
    double eigenvalue = 1.0;
    double eigenvector[SIZE];
    double nextVector[SIZE];

    // Initialize the initial population vector
    for (i = 0; i < SIZE; i++) {
        eigenvector[i] = 1.0;
    }

    // Perform matrix multiplication until convergence
    while (1) {
        multiplicaMatriz(matrix, eigenvector, nextVector);

        // Normalize the vector
        double sum = 0.0;
        for (i = 0; i < SIZE; i++) {
            sum += nextVector[i];
        }
        for (i = 0; i < SIZE; i++) {
            nextVector[i] /= sum;
        }

        // Check for convergence
        int converged = 1;
        for (i = 0; i < SIZE; i++) {
            if (nextVector[i] != eigenvector[i]) {
                converged = 0;
                break;
            }
        }

        // If converged, calculate the dominant eigenvalue
        if (converged) {
            double sumEigen = 0.0;
            double sumNext = 0.0;
            for (i = 0; i < SIZE; i++) {
                sumEigen += eigenvector[i];
                sumNext += nextVector[i];
            }
            eigenvalue = sumNext / sumEigen;
            break;
        }

        // Update the eigenvector for the next iteration
        for (i = 0; i < SIZE; i++) {
            eigenvector[i] = nextVector[i];
        }
    }

    return eigenvalue;
}

int main() {
    double leslieMatrix[SIZE][SIZE] = {
        {0, 1.2, 1.1, 1.05, 1.0, 0.8},
        {0.9, 0, 0, 0, 0, 0},
        {0, 0.8, 0, 0, 0, 0},
        {0, 0, 0.7, 0, 0, 0},
        {0, 0, 0, 0.6, 0, 0},
        {0, 0, 0, 0, 0.5, 0}
    };

    double reproductionRate = calculateReproductionRate(leslieMatrix);
    printf("Reproduction rate: %lf\n", reproductionRate);

    return 0;
}