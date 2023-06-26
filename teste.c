#include <stdio.h>

#define FAIXAS_ETARIAS 6

void imprimeMatriz(double matriz[][FAIXAS_ETARIAS]) {
    int i, j;
    for (i = 0; i < FAIXAS_ETARIAS; i++) {
        for (j = 0; j < FAIXAS_ETARIAS; j++) {
            printf("%.2f\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicaMatriz(double matriz[][FAIXAS_ETARIAS], double vetor[]) {
    int i, j;
    double resultado[FAIXAS_ETARIAS] = {0.0};

    for (i = 0; i < FAIXAS_ETARIAS; i++) {
        for (j = 0; j < FAIXAS_ETARIAS; j++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }

    for (i = 0; i < FAIXAS_ETARIAS; i++) {
        vetor[i] = resultado[i];
    }
}


int main() {
    double matrizLeslie[FAIXAS_ETARIAS][FAIXAS_ETARIAS] = {
        {0.0, 0.0, 0.5, 0.8, 0.3, 0.0},
        {0.8, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.9, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.9, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.8, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.3, 0.0}
    };

    double PopulacaoInicial[FAIXAS_ETARIAS] = {50.0, 40.0, 30.0, 20.0, 10.0, 5.0};

    printf("Matriz Leslie:\n");
    imprimeMatriz(matrizLeslie);

    printf("\nPopulacao Inicial:\n");
    for (int i = 0; i < FAIXAS_ETARIAS; i++) {
        printf("%.2f\t", PopulacaoInicial[i]);
    }
    printf("\n\n");

    for (int mes = 1; mes <= 105; mes++) {
        multiplicaMatriz(matrizLeslie, PopulacaoInicial);

        printf("Mes %d:\n", mes);
        for (int i = 0; i < FAIXAS_ETARIAS; i++) {
            printf("%.2f\t", PopulacaoInicial[i]);
        }
        printf("\n");
    }

    return 0;
}