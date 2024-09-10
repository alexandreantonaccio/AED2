#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FUNCAO 100
#define MAX_ISDN 100
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_LIVROS 200
#define MAX_LINE_LENGTH 256

// Estrutura para armazenar as informações de um livro
typedef struct {
    char isdn[MAX_ISDN];
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    int disponibilidade;
} Livro;

// Função para adicionar um livro à lista
void addLivro(Livro livros[], int *numLivros,const char* isdn ,const char* titulo, const char* autor, int ano) {
    if (*numLivros < MAX_LIVROS) {
        strcpy(livros[*numLivros].isdn,isdn);
        strcpy(livros[*numLivros].titulo, titulo);
        strcpy(livros[*numLivros].autor, autor);
        livros[*numLivros].ano = ano;
        livros[*numLivros].disponibilidade = 1;
        (*numLivros)++;
    } else {
        printf("Capacidade máxima de livros atingida!\n");
    }
}

// Função para buscar um livro pela chave
void searchLivro(Livro livros[], int *numLivros, const char* chave) {
    int found = 0;
    for (int i = 0; i < *numLivros; i++) {
        if (strcmp(livros[i].isdn, chave) == 0) {
            printf("Livro encontrado: ");
            printf(" ISDN:%s;", livros[i].isdn);
            printf("  Título: %s;", livros[i].titulo);
            printf("  Autor: %s;", livros[i].autor);
            printf("  Ano: %d;", livros[i].ano);
            printf(" Disponibilidade: %d\n", livros[i].disponibilidade);
            found = 1;
        }
        if (strcmp(livros[i].titulo, chave) == 0) {
            printf("Livro encontrado: ");
            printf(" ISDN:%s;", livros[i].isdn);
            printf("  Título: %s;", livros[i].titulo);
            printf("  Autor: %s;", livros[i].autor);
            printf("  Ano: %d;", livros[i].ano);
            printf(" Disponibilidade: %d\n", livros[i].disponibilidade);
            found = 1;
        }
        if (strcmp(livros[i].autor, chave) == 0) {
            printf("Livro encontrado: ");
            printf(" ISDN:%s;", livros[i].isdn);
            printf("  Título: %s;", livros[i].titulo);
            printf("  Autor: %s;", livros[i].autor);
            printf("  Ano: %d;", livros[i].ano);
            printf(" Disponibilidade: %d\n", livros[i].disponibilidade);
            found = 1;
        }
    }
    if (!found) {
        printf("Livro com a chave '%s' não encontrado.\n", chave);
    }
}

void checkInLivro(Livro livros[], int *numLivros, const char* chave) {
    int found = 0;
    for (int i = 0; i < *numLivros; i++) {
        if (strcmp(livros[i].isdn, chave) == 0) {
            if(livros[i].disponibilidade == 1){
                printf("Livro ja foi devolvido\n");
            }
            else {
                livros[i].disponibilidade = 1;
                printf("Check in do livro Realizado\n");
            }
            found = 1;
        }
    }
    if (!found) {
        printf("Livro com a chave '%s' não encontrado.\n", chave);
    }
}

void checkOutLivro(Livro livros[], int *numLivros, const char* chave) {
    int found = 0;
    for (int i = 0; i < *numLivros; i++) {
        if (strcmp(livros[i].isdn, chave) == 0) {
            if(livros[i].disponibilidade == 0){
                printf("Livro nao esta deisponível\n");
            }
            else {
                printf("Check out do livro realizado\n");
                livros[i].disponibilidade = 0;
            }
            found = 1;
        }
    }
    if (!found) {
        printf("Livro com a chave '%s' não encontrado.\n", chave);
    }
}

// Função para imprimir os livros cadastrados
void printLivros(Livro livros[], int numLivros) {
    for (int i = 0; i < numLivros; i++) {
        printf("Livro %d:\n", i + 1);
        printf(" ISDN:%s;",livros[i].isdn);
        printf("  Titulo: %s;", livros[i].titulo);
        printf("  Autor: %s;", livros[i].autor);
        printf("  Ano: %d;\n", livros[i].ano);
    }
}

int main() {
    // Definindo o caminho do arquivo
    const char* filename = "ent02.in";
    
    // Array para armazenar os livros
    Livro livros[MAX_LIVROS];
    int numLivros = 0;

    // Abrindo o arquivo para leitura
    FILE *file = fopen(filename, "r");

    // Variáveis para armazenar os dados do arquivo
    char line[MAX_LINE_LENGTH];
    char funcao[MAX_FUNCAO];
    char isdn[MAX_ISDN];
    char titulo[MAX_TITULO], autor[MAX_AUTOR];
    char chave[MAX_TITULO];
    int ano;

    // Lendo o arquivo linha por linha
    while (fgets(line, sizeof(line), file)) {
        // Remover o '\n' do final da linha, se houver
        line[strcspn(line, "\n")] = '\0';

        // Lendo os dados separados por ';'
        if (sscanf(line, "%s %[^;];%[^;];%[^;];%d",funcao,isdn, titulo, autor, &ano) == 5) {
            // Adiciona o livro à lista
            addLivro(livros, &numLivros,isdn, titulo, autor, ano);
        } 
        else if(sscanf(line, "%s %[^;];",funcao,chave) == 2){
            if(strcmp(funcao,"SEARCH")== 0){
                searchLivro(livros,&numLivros,chave);
            }
            if(strcmp(funcao,"CHECK_IN")== 0){
                checkInLivro(livros,&numLivros,chave);
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){
                checkOutLivro(livros,&numLivros,chave);
            }
        }
        else {
            printf("Formato invalido na linha: %s\n", line);
        }
    }

    // Fechando o arquivo
    fclose(file);

    // Exibir os livros cadastrados
    printLivros(livros, numLivros);

    return 0;
}
