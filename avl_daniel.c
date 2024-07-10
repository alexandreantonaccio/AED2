#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *esquerda, *direita;
    int Altura;
} TipoArv;

void preord(TipoArv *Pai){
    if (Pai != NULL) {
        printf("%d ", Pai->dado);
        preord(Pai->esquerda);
        preord(Pai->direita);
    }
}

int maior(int a, int b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}
int Altura(TipoArv *Pai){
    if (Pai == NULL){
        return 0;
    } else {
        return 1 + maior(Altura(Pai->esquerda), Altura(Pai->direita));
    }
}

int fb(TipoArv *Pai){
    if (Pai == NULL){
        return 0;
    } else {
        return Altura(Pai->direita) - Altura(Pai->esquerda);
    }
}

void AttAltura(TipoArv *Pai){
    if (Pai == NULL){
        return;
    } else {
        Pai->Altura =Altura(Pai);
    }
}

TipoArv *CriaNo(int novodado){
    TipoArv *NovoNo;
    NovoNo = malloc(sizeof(TipoArv));
    NovoNo->dado = novodado;
    NovoNo->esquerda = NULL;
    NovoNo->direita = NULL;
    return NovoNo;
}
TipoArv* rsd(TipoArv* Pai) {
    if (Pai == NULL || Pai->esquerda == NULL) {
        return Pai;
    }
    TipoArv* Aux = Pai->esquerda;
    Pai->esquerda = Aux->direita;
    Aux->direita = Pai;
    return Aux;  // Retorne o novo nó raiz após a rotação.
}

TipoArv* rse(TipoArv* Pai) {
    if (Pai == NULL || Pai->direita == NULL) {
        return Pai;
    }
    TipoArv* Aux = Pai->direita;
    Pai->direita = Aux->esquerda;
    Aux->esquerda = Pai;
    return Aux;  // Retorne o novo nó raiz após a rotação.
}

TipoArv* rdd(TipoArv *Pai) {
    if (Pai == NULL) {
        return NULL;
    }
    
    Pai->esquerda = rse(Pai->esquerda);
    TipoArv* novaRaiz = rsd(Pai);
    return novaRaiz;
}



TipoArv* rde(TipoArv *Pai) {
    if (Pai == NULL) {
        return NULL;
    }
    
    Pai->direita = rsd(Pai->direita);
    TipoArv* novaRaiz = rse(Pai);
    return novaRaiz;
}
// Função para inserir um valor em uma árvore AVL
TipoArv *Insere(TipoArv *Pai, int novodado) {
    if (Pai == NULL) {
        return CriaNo(novodado);
    }   
    if (novodado < Pai->dado) {
        Pai->esquerda = Insere(Pai->esquerda, novodado);
    } else if (novodado > Pai->dado) {
        Pai->direita = Insere(Pai->direita, novodado);
    }
    
    AttAltura(Pai);

    int resultado = fb(Pai);
    
    // Casos de desequilíbrio
    if (resultado > 1) {
        if (novodado < Pai->esquerda->dado) {
            return rsd(Pai);
        } else {
            return rdd(Pai);
        }
    }
    if (resultado < -1) {
        if (novodado > Pai->direita->dado) {
            return rse(Pai);
        } else {
            return rde(Pai);
        }
    }

    return Pai;
}

int main(){
    int vetor[] = {50, 60, 70, 80, 40, 90, 1000};
    TipoArv *Pai = NULL;  // Inicialize a raiz como NULL

    // Insira elementos do vetor na árvore
    for (int i = 0; i < sizeof(vetor) / sizeof(vetor[0]); i++) {
        Pai = Insere(Pai, vetor[i]);
    }
    
    // Imprima os elementos em pré-ordem
    printf("Árvore em pré-ordem: ");
    preord(Pai);
    
    // Imprima a altura da árvore
    printf("\nAltura da Árvore: %d\n", Altura(Pai));
    return 0;
}
