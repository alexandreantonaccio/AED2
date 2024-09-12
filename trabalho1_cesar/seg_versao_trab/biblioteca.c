#include "lse_neutra.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"


typedef struct livro{
    char isdn[60];
    char titulo[40];
    char autor[40];
    int ano;
    int disponibilidade;
}t_livro;

t_livro* criar_livro(char isdn[], char titulo[],char autor[], int ano){
    t_livro* nova = malloc(sizeof(t_livro));
    strcpy(nova->isdn, isdn);
    strcpy(nova->titulo, titulo);
    strcpy(nova->autor, autor);
    nova->ano = ano;
    nova->disponibilidade = 1;

    return nova;
}

void imprimir_livro(t_livro livro){
    printf("Livro :\n");
    printf(" ISDN:%s;",livro.isdn);
    printf("  Titulo: %s;", livro.titulo);
    printf("  Autor: %s;", livro.autor);
    printf("  Ano: %d;\n", livro.ano);

}

int comparar_isdn(t_livro* l1, t_livro* l2){
    return strcmp(l1->isdn, l2->isdn);
}

int comparar_autor(t_livro* l1, t_livro* l2){
    return strcmp(l1->autor, l2->autor);
}

int comparar_titulo(t_livro* l1, t_livro* l2){
    return strcmp(l1->titulo, l2->titulo);
}

void destroy_musica(t_livro* m){
    assert(m!=NULL);
    free(m);
}

typedef struct biblioteca{
    t_lse* livros;
}t_biblioteca;

t_biblioteca* criar_biblioteca(int lim_mais_bibliotecadas){
    t_biblioteca *t = malloc(sizeof(t_biblioteca));
    t->livros = criar_lse( imprimir_livro, comparar_isdn );

    return t;
}



void ligar_biblioteca(t_biblioteca* biblioteca){
    const char* filename = "ent01.in";
    char funcao[30];
    char isdn[60];
    char titulo[40];
    char autor[40];
    char linha[256];
    int ano;
    int disponibilidade;
    
    FILE *file = fopen(filename, "r");


    // Lendo o arquivo linha por linha
    while (fgets(linha, sizeof(linha), file)) {
        // Remover o '\n' do final da linha, se houver
        linha[strcspn(linha, "\n")] = '\0';

        // Lendo os dados separados por ';'
        if (sscanf(linha, "%s %[^;];%[^;];%[^;];%d",funcao,isdn, titulo, autor, &ano) == 5) {
            // Adiciona o livro à lista
            t_livro* novo = criar_livro(isdn,titulo,autor,ano);
            inserir_inicio_lse(biblioteca->livros, novo);
        } 
        else if(sscanf(linha, "%s %[^;];",funcao,isdn == 2)){
            if(strcmp(funcao,"SEARCH")== 0){
                printf("Funcao aind nao construida");
            }
            if(strcmp(funcao,"CHECK_IN")== 0){
                printf("Funcao aind nao construida");
            }
            if(strcmp(funcao,"CHECK_OUT")== 0){
                printf("Funcao aind nao construida");
            }
        }
        else {
            printf("Formato invalido na linha: %s\n", linha);
        }
    }

    // Fechando o arquivo
    fclose(file);
}

void imprimir_livros_biblioteca(t_biblioteca* biblioteca){
    imprimir_lse(biblioteca->livros);
}


int main(){
    t_biblioteca* sumsung = criar_biblioteca(10);
    ligar_biblioteca(sumsung);
    
    // PLAY nome_da_musica 
    // HEART nome_da_musica
    // PLAY nome_da_musica
    // PAUSE
    // RESUME
    // STOP
    // FINISH --> gravar o status da nossa livros

    imprimir_livros_biblioteca(sumsung);
}