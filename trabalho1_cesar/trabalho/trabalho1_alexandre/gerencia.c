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
    char isdn[100];
    char titulo[100]; 
    char autor[100];
    char ano[6];

    // Lendo o arquivo linha por linha
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s%[^;];%[^;];%[^;];%[^\n]",funcao,isdn,titulo,autor,ano) == 5) { //Caso ADD
            // Adiciona o livro à lista
            inserirLivro(lista,isdn,titulo,autor,ano);
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
    LerArquivos("ent01.in",&lista,&numLivros); //Chamada dos arquivos de teste
    LerArquivos("ent02.in",&lista,&numLivros);
    LerArquivos("ent03.in",&lista,&numLivros);
    impimirBiblioteca(lista,numLivros); //Imprime todos os livros armazenados na lista
    return 0;
}