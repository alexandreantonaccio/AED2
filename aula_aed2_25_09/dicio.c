#include "stdio.h"
#include "thash.h"
#include "dicio.h"

struct dicio{
    t_hash* entradas;
};

t_dicio* criar_dicio(){
    t_dicio* novo = malloc(sizeof(t_dicio));
    
    novo->entradas = criar_hash(0.9);
    return novo;
}

void inserir_dicio(t_dicio* d,int chave,void* valor){
    assert(chave > 0); 
    inserir_hash(d->entradas,chave,valor);
}

void* consulta_dicio(t_dicio* d , int chave){
    return buscar_hash(d->entradas, chave);
}

void* remover_dicio(t_dicio* d, int chave) {
    return remover_hash(d->entradas,chave);
}

void destroi_dicio(t_dicio* d){
    //destroi_hash(d->entradas);
}