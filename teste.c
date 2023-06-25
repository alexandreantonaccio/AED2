#include <stdio.h>

#define NUM_AGE_CLASSES 6

void printMatrix(double matrix[][NUM_AGE_CLASSES]) {
    int i, j;
    for (i = 0; i < NUM_AGE_CLASSES; i++) {
        for (j = 0; j < NUM_AGE_CLASSES; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrix(double matrix[][NUM_AGE_CLASSES], double vector[]) {
    int i, j;
    double result[NUM_AGE_CLASSES] = {0.0};

    for (i = 0; i < NUM_AGE_CLASSES; i++) {
        for (j = 0; j < NUM_AGE_CLASSES; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    for (i = 0; i < NUM_AGE_CLASSES; i++) {
        vector[i] = result[i];
    }
}

int main() {
    double leslieMatrix[NUM_AGE_CLASSES][NUM_AGE_CLASSES] = {
        {0.0, 0.0, 0.5, 0.8, 0.3, 0.0},
        {0.8, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.9, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.9, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.8, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.3, 0.0}
    };

    double initialPopulation[NUM_AGE_CLASSES] = {50.0, 40.0, 30.0, 20.0, 10.0, 5.0};

    printf("Leslie Matrix:\n");
    printMatrix(leslieMatrix);

    printf("\nInitial Population:\n");
    for (int i = 0; i < NUM_AGE_CLASSES; i++) {
        printf("%.2f\t", initialPopulation[i]);
    }
    printf("\n\n");

    for (int year = 1; year <= 101; year++) {
        multiplyMatrix(leslieMatrix, initialPopulation);

        printf("Year %d:\n", year);
        for (int i = 0; i < NUM_AGE_CLASSES; i++) {
            printf("%.2f\t", initialPopulation[i]);
        }
        printf("\n");
    }

    return 0;
}