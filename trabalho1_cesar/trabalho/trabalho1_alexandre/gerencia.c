#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.c"

void LerArquivos(const char* filename,Livro** lista,int *numLivros) {
    FILE *file = fopen(filename, "r");
    // Variáveis para armazenar os dados do arquivo
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
                printf("Buscando...\n");
                buscarLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_IN")== 0){ //Caso CHECK_IN
                printf("Check in...\n");
                checkInLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){ //Caso CHECK_OUT
                printf("Check out...\n");
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


int main() {
    Livro* lista = NULL;
    int numLivros = 0;
    int opcao = 0;
    char chave[100];
    char isbn[100];
    char titulo[100]; 
    char autor[100];
    char ano[6];
    char nomeArquivo[50];
    do {
        printf("1 - Ler arquivo de teste\n");
        printf("2 - Finalizar execucao\n");
        scanf("%d",&opcao); 
        
        switch(opcao) {
            case 1 :
                printf("Nome do arquivo a ser lido\n");
                scanf("%s",nomeArquivo);
                LerArquivos(nomeArquivo,&lista,&numLivros);
            break;
            case 2 : 
                printf("Fim do programa...");
                break;
            default :
                printf("Opcao invalida");
            break;
        }
    }while(opcao != 2);
    return 0;
}