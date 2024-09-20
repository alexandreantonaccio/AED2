#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

// Função para criar um novo livro
Livro* criarLivro(char* isbn,char* titulo, char* autor, char* ano) {
    Livro* novoLivro = (Livro*) malloc(sizeof(Livro));
    strcpy(novoLivro->isbn,isbn);
    strcpy(novoLivro->titulo,titulo);
    strcpy(novoLivro->autor,autor);
    strcpy(novoLivro->ano,ano);
    novoLivro->exemplares_disp = 1;
    novoLivro->proximo = NULL;
    return novoLivro;
}

void imprimirLivro(Livro* livro,int numLivros) { //Imprime Livro chamado
    if (livro != NULL) {
        printf("Livro n%d;",numLivros);
        printf(" ISBN:%s;", livro->isbn);
        printf(" Titulo:%s;", livro->titulo);
        printf(" Autor:%s;", livro->autor);
        printf(" Ano:%s;", livro->ano);
        printf(" Exemplares disponiveis: %d\n", livro->exemplares_disp);
    }
}

// Função para inserir um novo livro no início da lista
void inserirLivro(Livro** lista, char* isbn,char* titulo, char* autor, char* ano) {
    Livro* novoLivro = criarLivro(isbn,titulo,autor,ano);
    int numLivro = 1;
    if (*lista == NULL) {
        *lista = novoLivro;
        printf("Livro inserido :");
        imprimirLivro(*lista,numLivro);
    } else {
        // Percorre a lista até o último livro
        Livro* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
            numLivro++;
        }
        if (strcmp(atual->isbn,isbn)==0) { //Caso de duplicata
            if((strcmp(atual->autor,autor)==0) && (strcmp(atual->titulo,titulo)==0) && (strcmp(atual->ano,ano)==0)) {
                atual->exemplares_disp++;
                printf("Exemplar adicionado a %s\n",atual->isbn);
                return;
            }else {
                printf("ERRO, livro com este ISBN ja foi inserido, dois livros diferentes nao podem possuir o mesmo ISBN\n");
                return;
            }
        }
        numLivro++;
        atual->proximo = novoLivro;
        printf("Livro inserido :");
        imprimirLivro(atual->proximo,numLivro);
    }
}

void buscarLivro(Livro* lista, char* chave) { 
    Livro* atual = lista;
    int numLivro = 0;
    while (atual != NULL) { //Percorre lista até encontrar isbn/titulo/autor = chave
        if (strcmp(atual->isbn,chave)==0) {
            imprimirLivro(atual,numLivro);
        } else if(strcmp(atual->titulo,chave)==0){
            imprimirLivro(atual,numLivro);
        } else if(strcmp(atual->autor,chave)==0) {
            imprimirLivro(atual,numLivro);
        }
        atual = atual->proximo;
        numLivro++;
    }
}

void checkInLivro(Livro* lista,char* chave) {
    Livro* aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->isbn,chave)==0) {
            lista->exemplares_disp++; //Adiciona unidade ao livro especificado  
            printf("Check in de%s realizado com sucesso, exemplares disponiveis:%d\n",chave,aux->exemplares_disp);
            return;
        }
        aux = aux->proximo;
    }
    if(aux==NULL){
        printf("Livro nao pertence a biblioteca\n");
    }
}

void checkOutLivro(Livro* lista,char* chave) {
    Livro* aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->isbn,chave)==0) {
            if(aux->exemplares_disp==0) {
                printf("Livro nao disponivel\n");
            } else {
                lista->exemplares_disp--; //Reduz uma unidade em caso de check out
                printf("Check out de%s realizado com sucesso, exemplares disponiveis:%d\n",chave),lista->exemplares_disp;
            }
            return;
        }
        aux = aux->proximo;
    }
    if(aux==NULL){
        printf("Livro nao pertence a biblioteca\n");
    }
}

void impimirBiblioteca(Livro *lista){ //Impressao dos livros em ordem de inserção
    printf("\nImprimindo livros da biblioteca!\n\n");
    int numLivros = 1;
    while(lista!=NULL){
        imprimirLivro(lista,numLivros);
        lista = lista->proximo;
        numLivros++;
    }
}