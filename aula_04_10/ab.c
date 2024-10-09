#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "musica.h"

typedef int(*t_comparar_ab)(void*, void*);
typedef void(*t_imprimir_ab)(void*);

typedef struct no t_no;
struct no{
    void* info;
    t_no* sae;
    t_no* sad;
    t_no* ancestral;
};

t_no* criar_no(t_no* ancestral, void* info){
    t_no* novo = malloc(sizeof(t_no));
    novo->info = info;
    novo->sad = NULL;
    novo->sae = NULL;
    novo->ancestral = ancestral;
    return novo;
}

typedef struct ab t_ab;
struct ab{
    t_no* raiz;
    int tamanho;
    t_imprimir_ab impressora;
    t_comparar_ab comparar;
};

t_ab* criar_ab(t_imprimir_ab impressora, t_comparar_ab comparar){
    t_ab* nova = malloc(sizeof(t_ab));

    nova->raiz = NULL;
    nova->tamanho = 0;

    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;

}

static void* __buscar_ab(t_no* no, void* chave, t_comparar_ab comparar){
    if (no == NULL)
        return NULL;
    
    if (comparar(no->info, chave) == 0){
            return no->info;
    }else{
        void* retorno = __buscar_ab(no->sae, chave, comparar);
        if (retorno == NULL){
            retorno = __buscar_ab(no->sad, chave, comparar);
        }
        return retorno;
    }
}

void* buscar_ab(t_ab* ab, void* chave){
    return __buscar_ab(ab->raiz, chave, ab->comparar);
}

static int __sorteio(){
    static int primeira_vez=1;

    if (primeira_vez){
        srand48(time(NULL));
        primeira_vez = 0;
    } 
    int num = ((10*drand48()) % 2);
    printf("%d\n", num);
    return num;
}

void* __inserir_ab(t_no* no, t_no* ancestral, void* carga){
    if (no==NULL){
        return criar_no(ancestral, carga);
    }
    if (__sorteio() == 1){
        no->sae = __inserir_ab(no->sae, no, carga);
    }else{
        no->sad = __inserir_ab(no->sad, no, carga);
    }
    return no;
}

void inserir_ab(t_ab *a, void* carga){
    a->tamanho++;
    a->raiz = __inserir_ab(a->raiz, NULL, carga);
}


int main(int argc, char const *argv[])
{
    t_ab* ab = criar_ab(imprimir_musica, comparar_musica);
    for(int i=0;i<3;i++){
        t_musica* m = ler_musica();
        inserir_ab(ab,m);
    }    
    return 0;
}
