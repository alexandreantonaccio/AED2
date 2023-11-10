#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
  int coef;
  char palavra[46];
  struct no *esquerda, *direita;
}No;

int ehfolha(No* raiz){
  if(raiz->esquerda==NULL && raiz->direita==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

No* criafolha(char chave[]){
  No* novo=malloc(sizeof(No));
  strcpy(novo->palavra, chave);
  novo->esquerda=NULL;
  novo->direita=NULL;
  return novo;
}

int achadiferenca(char palavra[], char chave[], int i){
  if(palavra[i]!=chave[i] || palavra[i]=='\0' || chave[i]=='\0'){
    return i;
  }
  else{
    return achadiferenca(palavra, chave, i+1);
  }
}

No* inserefilhos(No inter, No raiz, char chave[], int diferenca){
  if(chave[diferenca]->raiz->palavra[diferenca]){
    inter->palavra[0]=chave[diferenca];
    inter->direita=criafolha(chave);
    inter->esquerda=raiz;
  }
  else{
    inter->palavra[0]=raiz->palavra[diferenca];
    inter->direita=raiz;
    inter->esquerda=criafolha(chave);
  }
  return inter;
}

No* criapai(No* raiz, char chave[]){
  No* novo=malloc(sizeof(No));
  int diferenca=achadiferenca(raiz->palavra, chave,0);
  novo->coef=diferenca+1;
  return inserefilhos(novo, raiz, chave, diferenca);
}

No* MDM(No* raiz){
  if(ehfolha(raiz)==1){
    return raiz;
  }
  else{
    return MDM(raiz->esquerda);
  }
}

No* insereinter(No* raiz, char chave[], int acumulado){
  No* novo=malloc(sizeof(No));
  int diferenca=achadiferenca(raiz->palavra, chave, acumulado-1);
  novo->coef=diferenca+1-acumulado;
  return inserefilhos(novo, raiz, chave, diferenca);
}

No* inserepai(No* raiz, char chave[], char busca[], int diferenca, int acumulado){
  No* novo=malloc(sizeof(No));
  novo->coef=(diferenca+1)-(acumulado-raiz->coef);
  raiz->coef=raiz->coef-novo->coef;
  if(chave[diferenca]>busca[diferenca]){
    novo->palavra[0]=chave[diferenca];
    novo->direita=criafolha(chave);
    novo->esquerda=raiz;
  }
  else{
    novo->palavra[0]=busca[diferenca];
    novo->direita=raiz;
    novo->esquerda=criafolha(chave);
  }
  return novo;
}

No* inserirPrincipal(No *raiz, char chave[], int acumulado){
  if(ehfolha(raiz)==1){
    return insereinter(raiz, chave, acumulado);
  }
  else{
    acumulado=acumulado+raiz->coef;
    No* busca=MDM(raiz->direita);
    int diferenca=achadiferenca(busca->palavra, chave, 0);
    if(diferenca+1<acumulado){
      return inserepai(raiz, chave, busca->palavra, diferenca, acumulado);
    }
    if(chave[acumulado-1]<raiz->palavra[0]){
      raiz->esquerda=inserirPrincipal(raiz->esquerda, chave, acumulado);
    }
    else{
      raiz->direita=inserirPrincipal(raiz->direita, chave, acumulado);
    }
    return raiz;
  }
}

No* verificainserir(No *raiz, char chave[]){
  if(raiz==NULL){
    return criafolha(chave);
  }
  else if(ehfolha(raiz)==1){
    return criapai(raiz, chave);
  }
  else{
    return inserirPrincipal(raiz, chave, 0);
  }
}

void imprimir(No* raiz){
  if(raiz!=NULL){
    imprimir(raiz->esquerda);
    if(ehfolha(raiz)==1){
      printf("\n%s\n", raiz->palavra);
    }
    imprimir(raiz->direita);
  }
}

No* remover(No* raiz, No* pai){
  if(pai->esquerda==raiz){
    if(ehfolha(pai->direita)==1){
      No* aux=pai->direita;
      free(raiz);
      free(pai);
      return aux;
    }
    else{
      No* aux=pai->direita;
      aux->coef=aux->coef+pai->coef;
      free(pai);
      free(raiz);
      return aux;
    }
  }
  else{
    if(ehfolha(pai->esquerda)==1){
      No* aux=pai->esquerda;
      free(raiz);
      free(pai);
      return aux;
    }
    else{
      No* aux=pai->esquerda;
      aux->coef=aux->coef+pai->coef;
      free(raiz);
      free(pai);
      return aux;
    }
  }
}

No* verificaremocao(No raiz, No pai, char chave[]){
  if(strcmp(raiz->palavra, chave)==0){
    return remover(raiz, pai);
  }
  else{
    printf("chave nao encontrada");
    return pai;
  }
}

No* removerPrincipal(No *raiz, char chave[], int acumulado){
  acumulado=acumulado+raiz->coef;
  if(chave[acumulado-1]<raiz->palavra[0]){
    if(ehfolha(raiz->esquerda)==1){
      return verificaremocao(raiz->esquerda, raiz, chave);
    }
    else{
      raiz->esquerda=removerPrincipal(raiz->esquerda, chave, acumulado);
    }
  }
  else{
    if(ehfolha(raiz->direita)==1){
      return verificaremocao(raiz->direita, raiz, chave);
    }
    else{
      raiz->direita=removerPrincipal(raiz->direita, chave, acumulado);
    }
  }
  return raiz;
}

No* verificaremoverraiz(No* raiz, char chave[]){
  if(raiz==NULL){
    printf("\narvore vazia");
    return NULL;
  }
  else if(ehfolha(raiz)==1){
    if(strcmp(chave, raiz->palavra)==0){
      free(raiz);
      return NULL;
    }
    else{
      printf("chave nao encontrada");
      return raiz;
    }
  }
  else{
    return removerPrincipal(raiz, chave, 0);
  }
}

int main(void){
  No* raiz=NULL;
  int opcao;
  char chave[46];

  do{
    printf("Digite 1 para inserir, 2 para imprimir, 3 para remover ");
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
        printf("Digite a chave ");
        scanf("%s", chave);
        raiz=verificainserir(raiz, chave);
        break;
      case 2:
        imprimir(raiz);
        break;
      case 3:
        printf("Digite a chave ");
        scanf("%s", chave);
        raiz=verificaremoverraiz(raiz, chave);
        break;
    }
  }while(opcao!=0);

  return 0;
}