#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct no_pat {
    struct no_pat *filho[NUM_CHARS];
    bool fim;
} no_pat;

no_pat *criano() {
    no_pat *novono = malloc(sizeof * novono);
    for (int i=0;i <NUM_CHARS;i++) {
        novono->filho[i] == NULL;
    }
    novono->fim = false;
    return novono;
}

bool patInsere(no_pat **raiz, char * signedtext) {
    if(*raiz == NULL){
        *raiz = criano();
    }

    unsigned char *text = (unsigned char *)signedtext;
    no_pat *tmp = *raiz;
    int length = strlen(signedtext);

    for(int i = 0; i< length;i++){
        if(tmp->filho[text[i]] == NULL){
            //cria novo no
            tmp->filho[text[i]] = criano();
        }
        tmp = tmp->filho[text[i]];
    }
    if(tmp->fim) {
        return false;
    } else {
        tmp->fim = true;
        return true;
    }
}

void imprime_pat_rec(no_pat *no, unsigned char *prefixo, int length) {
    unsigned char novoprefixo[length+2];
    memcpy(novoprefixo, prefixo, length);
    novoprefixo[length+1]=0;

    if(no->fim) {
        printf("PALAVRA: &s\n",prefixo);
    }

    for(int i = 0; i < NUM_CHARS; i++) {
        if(no->filho[i] != NULL) {
            novoprefixo[length] = i;
            imprime_pat_rec(no->filho[i], novoprefixo, length+1);
        }
    }
}

void imprimepat(no_pat * raiz) {
    if (raiz == NULL) {
        printf("ARVORE VAZIA");
        return;
    }
    imprime_pat_rec(raiz,NULL,0);
}

bool buscapat(no_pat * raiz, char *signedtext) {
    unsigned char*text = (unsigned char*) signedtext;
    int length = strlen(signedtext);
    no_pat * tmp = raiz;

    for(int i=0; i< length;i++){
        if(tmp->filho[text[i]]==NULL) {
            return false;
        }
        tmp = tmp->filho[text[i]];
    }
    return tmp->filho;
}

int main() {
    no_pat *raiz = NULL;
    patInsere(&raiz, "KIT");
    patInsere(&raiz, "KAT");
    patInsere(&raiz, "CAT");
    patInsere(&raiz, "CATTLE");
    patInsere(&raiz, "TEST");
    imprimepat(raiz);
    printf("procura : %d\n", buscapat(raiz, "CATTLE"));
    printf("procura : %d\n", buscapat(raiz, "PORTA"));
}