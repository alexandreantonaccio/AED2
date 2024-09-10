#include "stdio.h"

typedef int(*t_maior_especialista)(void*,void*);

int maior(void* a, void* b, t_maior_especialista maior_especialista){
    return maior_especialista(a,b);
}

int maior_double(double* aa,double* bb){
    double* a = aa;
    double* b = bb;
    if(*a>*b){
        return 1;
    } else if (*a < *b){
        return -1;
    } else {
        return 0;
    }
    
}

void main(){
    double aa, bb;
    scanf("%lf",&aa);
    scanf("%lf",&bb);
    int c = maior(&aa,&bb, maior_double);
    if(c > 0){
        printf("maior valor eh %d\n", aa);
    }
    else if (c<0){
        printf("maior valor eh %d\n", bb);
    }
    else {
        printf("ambos iguais");
    }
}