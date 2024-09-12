#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do livro
typedef struct Livro {
    char isdn[60];
    char titulo[40];
    char autor[100];
    char ano[6];
    int disponibilidade;
    struct Livro* proximo;
} Livro;

// Função para criar um novo livro
Livro* criarLivro(char* isdn,char* titulo, char* autor, char* ano) {
    Livro* novoLivro = (Livro*) malloc(sizeof(Livro));
    strcpy(novoLivro->isdn,isdn);
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    strcpy(novoLivro->ano,ano);
    novoLivro->disponibilidade = 1;
    novoLivro->proximo = NULL;
    return novoLivro;
}

// Função para inserir um novo livro no início da lista
void inserirLivro(Livro** lista, char* isdn,char* titulo, char* autor, char* ano) {
    Livro* novoLivro = criarLivro(isdn,titulo,autor,ano);
    
    if (*lista == NULL) {
        // Se a lista estiver vazia, o novo livro será o primeiro
        *lista = novoLivro;
    } else {
        // Percorre a lista até o último livro
        Livro* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // Insere o novo livro no final
        atual->proximo = novoLivro;
    }
}

void imprimirLivro(Livro* livro) {
    if (livro != NULL) {
        printf("ISDN: %s;", livro->isdn);
        printf(" Titulo: %s;", livro->titulo);
        printf(" Autor: %s;", livro->autor);
        printf(" Ano: %s;", livro->ano);
        printf(" Disponibilidade: %d\n", livro->disponibilidade);
    }
}

void buscarLivro(Livro* lista, char* chave) {
    Livro* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->isdn,chave)==0) {
            imprimirLivro(atual);
        } else if(strcmp(atual->titulo,chave)==0){
            imprimirLivro(atual);
        } else if(strcmp(atual->autor,chave)==0) {
            imprimirLivro(atual);
        }
        atual = atual->proximo;
    }
}

void checkInLivro(Livro* lista,char* chave) {
    while (lista != NULL) {
        if (strcmp(lista->isdn,chave)==0) {
            if(lista->disponibilidade==1) {
                printf("livro ja devolvido!\n");
            } else {
                lista->disponibilidade = 1;
                printf("Check In realizado com sucesso\n");
            }
            return;
        }
        lista = lista->proximo;
    }
}

void checkOutLivro(Livro* lista,char* chave) {
    while (lista != NULL) {
        if (strcmp(lista->isdn,chave)==0) {
            if(lista->disponibilidade==0) {
                printf("Livro nao disponivel\n");
            } else {
                lista->disponibilidade = 0;
                printf("Check Out realizado com sucesso\n");
            }
            return;
        }
        lista = lista->proximo;
    }
    if(lista==NULL){
        printf("Livro nao pertence a biblioteca\n");
    }
}

void impimirBiblioteca(Livro *lista){
    printf("\nImprimindo livros da biblioteca!\n\n");
    while(lista!=NULL){
        imprimirLivro(lista);
        lista = lista->proximo;
    }
}

int main() {
    Livro* lista = NULL;

    const char* filename = "ent03.in";

    // Abrindo o arquivo para leitura
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

        // Lendo os dados separados por ';'
        if (sscanf(line, "%s%[^;];%[^;];%[^;];%[^\n]",funcao,isdn,titulo,autor,ano) == 5) {
            // Adiciona o livro à lista
            inserirLivro(&lista,isdn,titulo,autor,ano);
        } 
        else if(sscanf(line, "%s%[^;];",funcao,chave) == 2){
            if(strcmp(funcao,"SEARCH")== 0){
                buscarLivro(lista,chave);
            }
            if(strcmp(funcao,"CHECK_IN")== 0){
                checkInLivro(lista,chave);
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){
                checkOutLivro(lista,chave);
            }
        }
        else {
            printf("Formato invalido na linha: %s\n", line);
        }
    }
    free(file);
    impimirBiblioteca(lista);
    // Liberar memória alocada (se necessário)
    return 0;

}
