#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct elem_sll t_elem_sll;
struct elem_sll{
    char titulo[100];
    char autor[100];
    char ISDN[50];
    char ano[6];
    int disp;
    t_elem_sll* child;
};

typedef struct {
    t_elem_sll *first;
    int size;
    t_elem_sll *last;
}t_sll;

void destroy_sll(t_sll* list){
    assert(list->first==NULL);
    free(list);
}


t_elem_sll* create_elem_sl(char titulo[100], char autor[100], char ISDN[50], char ano[6]){
    t_elem_sll* new = malloc(sizeof(t_elem_sll));
    new->titulo = titulo; 
    new->autor = autor;
    new->ISDN = ISDN;
    new->ano = ano;
    new->child=NULL;
    new->disp = 1;
    return new;
}

t_sll* create_list(){
    t_sll* new = malloc(sizeof(t_sll));
    new->first = NULL;
    new->size = 0;
    new->last = NULL;
    return new;
}

void insert_end_elem_list(t_sll* list, char titulo[100], char autor[100], char ISDN[50], char ano[6]){
    t_elem_sll* new = create_elem_sll(titulo,autor,ISDN,ano);
    if(list->first == NULL){
        list->first = new;
        list->last = new;
    }
    else {
        list->last->child = new;
        list->last = new;
    }
    list->size++;
}


int access_by_author_sll(t_sll* list, char autor[100]) {
    t_elem_sll* path = list->first;
    int count = 1;
    while(count < list->size) {
        if(path->autor==autor){
            printf("%s,%s,%s,%s,%d\n",path->ISDN,path->titulo,path->autor,path->ano,path->disp);
        }
        path = path->child;
        count++;
    }
    return count;
}

int access_by_ISDN_sll(t_sll* list, char titulo[100], char autor[100], char ISDN[50], char ano[6]) {
    t_elem_sll* path = list->first;
    int count = 1;
    while((path!=NULL)&& count != list->size) {
        if(path->ISDN==ISDN){
            printf("%s,%s,%s,%s,%d\n",path->ISDN,path->titulo,path->autor,path->ano,path->disp);
        }
        path = path->child;
        count++;
    }
    return count;
}


void insert_content_list(t_sll *list, char titulo[100], char autor[100], char ISDN[50], char ano[6]) {
    t_elem_sll* new = create_elem_sll(titulo,autor,ISDN,ano);
    t_elem_sll* path = list->first;
    t_elem_sll*ant = NULL;
    while((path!= NULL) && (path->autor < autor)){
        ant = path;
        path= path->child;
    }
    if(path == list->first){
        new->child = list->first;
        list->first = new;
    }
    else if (path == NULL){
        list->last->child = new;
        list->last - new;
    }
    else {
        ant->child = new;
        new->child = path;

    }
    list->size++;
}


int main(){
    t_sll* list = create_list();
    insert_content_list(list,10);
    insert_content_list(list,9);
    insert_content_list(list,8);
    printf("9 Esta na posicao %d\n",access_by_content_sll(list,9));
    printf("%d\n", access_sll(list,2));
    remove_content_sll(list, 9);
    printf("%d\n",access_sll(list,2));
    printf("%d\n", list->size);
}