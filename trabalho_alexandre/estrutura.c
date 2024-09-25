#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do tipo Livro
typedef struct Livro {
    char isbn[100];
    char titulo[100];
    char autor[100];
    char ano[6];
    int exemplares_disp;
    struct Livro* proximo;
} Livro;
