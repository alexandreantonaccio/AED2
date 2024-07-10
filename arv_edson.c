void preorder(TipoArv *Pai) {
    if(Pai != NULL) {
        printf("%d ", Pai->chave);
        preorder(Pai->esq);
        preorder(Pai->dir);
    }
}

TipoArv* Inserir(TipoArv *Pai, TipoArv *Novo) {
    if(Pai == NULL) {
        Pai = Novo;
        return Pai;
    }else if(Pai->chave > Novo->chave){
        Pai->esq = Inserir(Pai->esq, Novo);
    }else if(Pai->chave < Novo->chave){
        Pai->dir = Inserir(Pai->dir, Novo);
    } return Pai;
}

int busca(TipoArv *Pai, int chave) {
    if(Pai == NULL) {
        return 0;
    } else {
        if(Pai->chave == chave) {
            return chave;
        } else if(Pai->chave > chave) {
            return busca(Pai->esq, chave);
        }else {
            return busca(Pai->dir, chave);
        }
    }
}

int main() {
    TipoArv *Inicio  = (TipoArv*) malloc(sizeof(TipoArv));
    TipoArv *criado;
    int dado = 0, chave_busca, result = 0;
    Inicio = NULL;
    do {
        printf("Informe -1 para sair: ");
        scanf("%d", &dado);
        if(dado != -1) {
        criado = criaNo(dado);
        Inicio = Inserir(Inicio, criado);
        }
    } while(dado != -1);
    printf("\nÁrvore: \n");
    preorder(Inicio);
    printf("Informe o valor a ser buscado: ");
    do {
        scanf("%d", &chave_busca);
        result = busca(Inicio, chave_busca);
        if (result == 0){
            printf("Valor não encontrado! :(\n");
        }else {
            printf("Valor encontrado: %d :)\n", result);
        }
    } while(chave_busca >= 0);

    return 0;
}
