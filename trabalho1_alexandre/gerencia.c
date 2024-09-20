#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

void LerArquivo(const char* filename,Livro** lista,int *numLivros) {
    FILE *file = fopen(filename, "r");
    char line[256];
    char funcao[40];
    char chave[100];
    char isbn[100];
    char titulo[100]; 
    char autor[100];
    char ano[6];

    // Lendo o arquivo linha por linha
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s%[^;];%[^;];%[^;];%[^\n]",funcao,isbn,titulo,autor,ano) == 5) { //Caso ADD
            // Adiciona o livro à lista
            inserirLivro(lista,isbn,titulo,autor,ano);
        } 
        else if(sscanf(line, "%s%[^;];",funcao,chave) == 2){ 
            if(strcmp(funcao,"SEARCH")== 0){ //Caso SEARCH
                printf("Buscando '%s'\n",chave);
                buscarLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_IN")== 0){ //Caso CHECK_IN
                printf("Check in '%s'\n",chave);
                checkInLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){ //Caso CHECK_OUT
                printf("Check out '%s'\n",chave);
                checkOutLivro(*lista,chave);
            }
        else if (sscanf(line,"%s",funcao) == 1) { //Caso END
            if(strcmp(funcao,"END")==0) {
                return;
            }
        }
        }
        else {
            printf("Formato invalido na linha: %s\n", line); 
        }
    }
    free(file);
}


int main(int agrc, char *argv[]) {
    Livro* lista = NULL;
    int numLivros = 0;
    LerArquivo(argv[1],&lista,&numLivros);
    return 0;
}