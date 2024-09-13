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
            numLivros++;
        } 
        else if(sscanf(line, "%s%[^;];",funcao,chave) == 2){ 
            if(strcmp(funcao,"SEARCH")== 0){ //Caso SEARCH
                buscarLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_IN")== 0){ //Caso CHECK_IN
                checkInLivro(*lista,chave);
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){ //Caso CHECK_OUT
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
        printf("1 - Adcionar um livro\n");
        printf("2 - Buscar um livro\n");
        printf("3 - Check in de um livro\n");
        printf("4 - Check out de um livro\n");
        printf("5 - Ler arquivo de teste\n");
        printf("6 - Imprimir bibilioteca\n");
        printf("7 - Finalizar execucao\n");
        scanf("%d",&opcao); 
        
        switch(opcao) {
            case 1 :
                printf("isbn do livro:\n");
                scanf("%s",isbn);
                printf("titulo do livro:\n");
                scanf("%s",titulo);
                printf("autor do livro:\n");
                scanf("%s", autor);
                printf("ano do livro:\n");
                scanf("%s",ano);
                inserirLivro(&lista,isbn,titulo,autor,ano);
                numLivros++;
            break;
            case 2 :
                printf("Livro a ser buscado\n");
                scanf("%s",chave);
                buscarLivro(lista,chave);
            break;
            case 3 :
                printf("Livro para check in:\n");
                scanf("%s",chave);
                checkInLivro(lista,chave);
            break;
            case 4 :
                printf("Livro para check out\n");
                scanf("%s",chave);
                checkOutLivro(lista,chave);
            break;
            case 5 :
                printf("Nome do arquivo a ser lido\n");
                scanf("%s",nomeArquivo);
                LerArquivos(nomeArquivo,&lista,&numLivros);
            break;
            case 6 :
                impimirBiblioteca(lista,numLivros);
            break;
            case 7 : 
                printf("Fim do programa!");
                break;
            default :
                printf("Opcao invalida");
            break;
        }

    }while(opcao != 7);
    return 0;
}