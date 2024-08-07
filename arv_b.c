// Deleting a key from a B-tree in C

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct tipoNo{
  int item[MAX], contador;
  struct tipoNo*ponteiros[MAX + 1];
};

struct tipoNo*raiz;

// Node creation
struct tipoNo*criaNo(int item, struct tipoNo*filho) {
  struct tipoNo*novoNo;
  novoNo = (struct tipoNo*)malloc(sizeof(struct tipoNo));
  novoNo->item[1] = item;
  novoNo->contador = 1;
  novoNo->ponteiros[0] = raiz;
  novoNo->ponteiros[1] = filho;
  return novoNo;
}

// Add value to the node
void adcValorNo(int item, int pos, struct tipoNo*no,
          struct tipoNo*filho) {
  int j = no->contador;
  while (j > pos) {
    no->item[j + 1] = no->item[j];
    no->ponteiros[j + 1] = no->ponteiros[j];
    j--;
  }
  no->item[j + 1] = item;
  no->ponteiros[j + 1] = filho;
  no->contador++;
}

// Split the node
void divideNo(int item, int *pval, int pos, struct tipoNo*node,
         struct tipoNo*filho, struct tipoNo**novoNo) {
  int mediano, j;

  if (pos > MIN)
    mediano = MIN + 1;
  else
    mediano = MIN;

  *novoNo = (struct tipoNo*)malloc(sizeof(struct tipoNo));
  j = mediano + 1;
  while (j <= MAX) {
    (*novoNo)->item[j - mediano] = node->item[j];
    (*novoNo)->ponteiros[j - mediano] = node->ponteiros[j];
    j++;
  }
  node->contador = mediano;
  (*novoNo)->contador = MAX - mediano;

  if (pos <= MIN) {
    adcValorNo(item, pos, node, filho);
  } else {
    adcValorNo(item, pos - mediano, *novoNo, filho);
  }
  *pval = node->item[node->contador];
  (*novoNo)->ponteiros[0] = node->ponteiros[node->contador];
  node->contador--;
}

// Set the value in the node
int colocaValorNo(int item, int *pval,
           struct tipoNo*node, struct tipoNo**filho) {
  int pos;
  if (!node) {
    *pval = item;
    *filho = NULL;
    return 1;
  }

  if (item < node->item[1]) {
    pos = 0;
  } else {
    for (pos = node->contador;
       (item < node->item[pos] && pos > 1); pos--)
      ;
    if (item == node->item[pos]) {
      printf("Duplicates not allowed\n");
      return 0;
    }
  }
  if (colocaValorNo(item, pval, node->ponteiros[pos], filho)) {
    if (node->contador < MAX) {
      adcValorNo(*pval, pos, node, *filho);
    } else {
      divideNo(*pval, pval, pos, node, *filho, filho);
      return 1;
    }
  }
  return 0;
}

// Insertion operation
void insercao(int item) {
  int flag, i;
  struct tipoNo*filho;

  flag = colocaValorNo(item, &i, raiz, &filho);
  if (flag)
    raiz = criaNo(i, filho);
}

// Copy the successor
void copiaSucessor(struct tipoNo*meuNo, int pos) {
  struct tipoNo*dummy;
  dummy = meuNo->ponteiros[pos];

  for (; dummy->ponteiros[0] != NULL;)
    dummy = dummy->ponteiros[0];
  meuNo->item[pos] = dummy->item[1];
}

// Remove the value
void removeVal(struct tipoNo*meuNo, int pos) {
  int i = pos + 1;
  while (i <= meuNo->contador) {
    meuNo->item[i - 1] = meuNo->item[i];
    meuNo->ponteiros[i - 1] = meuNo->ponteiros[i];
    i++;
  }
  meuNo->contador--;
}

// Do right shift
void rotDireita(struct tipoNo*meuNo, int pos) {
  struct tipoNo*x = meuNo->ponteiros[pos];
  int j = x->contador;

  while (j > 0) {
    x->item[j + 1] = x->item[j];
    x->ponteiros[j + 1] = x->ponteiros[j];
  }
  x->item[1] = meuNo->item[pos];
  x->ponteiros[1] = x->ponteiros[0];
  x->contador++;

  x = meuNo->ponteiros[pos - 1];
  meuNo->item[pos] = x->item[x->contador];
  meuNo->ponteiros[pos] = x->ponteiros[x->contador];
  x->contador--;
  return;
}

// Do left shift
void rotEsquerda(struct tipoNo*meuNo, int pos) {
  int j = 1;
  struct tipoNo*x = meuNo->ponteiros[pos - 1];

  x->contador++;
  x->item[x->contador] = meuNo->item[pos];
  x->ponteiros[x->contador] = meuNo->ponteiros[pos]->ponteiros[0];

  x = meuNo->ponteiros[pos];
  meuNo->item[pos] = x->item[1];
  x->ponteiros[0] = x->ponteiros[1];
  x->contador--;

  while (j <= x->contador) {
    x->item[j] = x->item[j + 1];
    x->ponteiros[j] = x->ponteiros[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void juntaNos(struct tipoNo*meuNo, int pos) {
  int j = 1;
  struct tipoNo*x1 = meuNo->ponteiros[pos], *x2 = meuNo->ponteiros[pos - 1];

  x2->contador++;
  x2->item[x2->contador] = meuNo->item[pos];
  x2->ponteiros[x2->contador] = meuNo->ponteiros[0];

  while (j <= x1->contador) {
    x2->contador++;
    x2->item[x2->contador] = x1->item[j];
    x2->ponteiros[x2->contador] = x1->ponteiros[j];
    j++;
  }

  j = pos;
  while (j < meuNo->contador) {
    meuNo->item[j] = meuNo->item[j + 1];
    meuNo->ponteiros[j] = meuNo->ponteiros[j + 1];
    j++;
  }
  meuNo->contador--;
  free(x1);
}

// Adjust the node
void ajustaNo(struct tipoNo*meuNo, int pos) {
  if (!pos) {
    if (meuNo->ponteiros[1]->contador > MIN) {
      rotEsquerda(meuNo, 1);
    } else {
      juntaNos(meuNo, 1);
    }
  } else {
    if (meuNo->contador != pos) {
      if (meuNo->ponteiros[pos - 1]->contador > MIN) {
        rotDireita(meuNo, pos);
      } else {
        if (meuNo->ponteiros[pos + 1]->contador > MIN) {
          rotEsquerda(meuNo, pos + 1);
        } else {
          juntaNos(meuNo, pos);
        }
      }
    } else {
      if (meuNo->ponteiros[pos - 1]->contador > MIN)
        rotDireita(meuNo, pos);
      else
        juntaNos(meuNo, pos);
    }
  }
}

// Delete a value from the node
int apagaValNo(int item, struct tipoNo*meuNo) {
  int pos, flag = 0;
  if (meuNo) {
    if (item < meuNo->item[1]) {
      pos = 0;
      flag = 0;
    } else {
      for (pos = meuNo->contador; (item < meuNo->item[pos] && pos > 1); pos--)
        ;
      if (item == meuNo->item[pos]) {
        flag = 1;
      } else {
        flag = 0;
      }
    }
    if (flag) {
      if (meuNo->ponteiros[pos - 1]) {
        copiaSucessor(meuNo, pos);
        flag = apagaValNo(meuNo->item[pos], meuNo->ponteiros[pos]);
        if (flag == 0) {
          printf("Não esta presente na arvore\n");
        }
      } else {
        removeVal(meuNo, pos);
      }
    } else {
      flag = apagaValNo(item, meuNo->ponteiros[pos]);
    }
    if (meuNo->ponteiros[pos]) {
      if (meuNo->ponteiros[pos]->contador < MIN)
        ajustaNo(meuNo, pos);
    }
  }
  return flag;
}

// Delete operaiton
void apaga (int item, struct tipoNo*meuNo) {
  struct tipoNo*tmp;
  if (!apagaValNo(item, meuNo)) {
    printf("Nao Tem\n");
    return;
  } else {
    if (meuNo->contador == 0) {
      tmp = meuNo;
      meuNo = meuNo->ponteiros[0];
      free(tmp);
    }
  }
  raiz = meuNo;
  return;
}

void pesquisa(int item, int *pos, struct tipoNo*meuNo) {
  if (!meuNo) {
    printf("Nao esta presente na arvore");
    return;
  }

  if (item < meuNo->item[1]) {
    *pos = 0;
  } else {
    for (*pos = meuNo->contador;
       (item < meuNo->item[*pos] && *pos > 1); (*pos)--)
      ;
    if (item == meuNo->item[*pos]) {
      printf("%d presente na árvore", item);
      return;
    }
  }
  pesquisa(item, pos, meuNo->ponteiros[*pos]);
  return;
}

void pesquisaVetor(int item, int*pos, struct tipoNo*meuNo) {
  
}

void imprime(struct tipoNo*meuNo) {
  int i;
  if (meuNo) {
    for (i = 0; i < meuNo->contador; i++) {
      imprime(meuNo->ponteiros[i]);
      printf("%d ", meuNo->item[i + 1]);
    }
    imprime(meuNo->ponteiros[i]);
  }
}

int main() {
  int item, ch;

  insercao(8);
  insercao(9);
  insercao(10);
  insercao(11);
  insercao(9);
  insercao(15);
  insercao(16);
  insercao(17);
  insercao(18);
  insercao(20);
  insercao(23);

  imprime(raiz);

  apaga (20, raiz);
  printf("\n");
  imprime(raiz);
  printf("\n");
  pesquisa(20,&ch,raiz);
  printf("\n");
  apaga(15,raiz);
  imprime(raiz);
}