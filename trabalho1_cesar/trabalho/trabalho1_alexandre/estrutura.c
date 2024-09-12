#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do tipo Livro
typedef struct Livro {
    char isdn[60];
    char titulo[40];
    char autor[100];
    char ano[6];
    int Exemplares;
    struct Livro* proximo;
} Livro;
