#include "stdio.h"

int main(){
    const char* filename = "trabalho/ent01.in";

    // Abrindo o arquivo para leitura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return 1;
    }
    
    
    char CMD[30];
    char titulo[100];
    char autor[100];
    char ISDN[50];
    char ano[6];
    char separador[4];

    scanf("%s ", CMD);
    //printf("%s\n", CMD);
    scanf("%[^;]s", ISDN);
    //printf("%s\n", ISDN);
    scanf("%s ",separador);
    scanf("%[^;]s", titulo);
    //printf("%s\n", titulo);
    scanf("%s ",separador);
    scanf("%[^;]s", autor);
    //printf("%s\n", autor);
    scanf("%s ",separador);
    scanf("%s", ano);
    //printf("%s\n", ano);
    printf("%s|%s|%s|%s|%s\n", CMD, ISDN, titulo, autor, ano);

}