#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct elem_sll t_elem_sll;
struct elem_sll{
    int content;
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


t_elem_sll* create_elem_sll(int content){
    t_elem_sll* new = malloc(sizeof(t_elem_sll));
    new->content = content;
    new->child=NULL;
    return new;
}

t_sll* create_list(){
    t_sll* new = malloc(sizeof(t_sll));
    new->first = NULL;
    new->size = 0;
    new->last = NULL;
    return new;
}

void insert_start_elem_list(t_sll* list, int content){
    t_elem_sll* new = create_elem_sll(content);
    new->child = list->first;
    list->first = new;
    if(list->last == NULL){
        list->last = new;
    }
    list->size++;
}


void insert_end_elem_list(t_sll* list, int content){
    t_elem_sll*new = create_elem_sll(content);
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

int remove_start_list(t_sll* list) {
    int content;
    assert(list->first!=NULL);
    if(list->first == list->last) {
        content = list->first->content;
        free(list->first);
        destroy_sll(list);
    }else {
        t_elem_sll* second = list->first->child;
        free(list->first);
        list->first = second;
        list->first->content = second->content;
    }
    list->size--;
}

void remove_end_list(t_sll* list){
    int content;
    assert(list->first!=NULL);
    if(list->first == list->last) {
        content = list->first->content;
        free(list->first);
        destroy_sll(list);
    }else {
        t_elem_sll* path = list->first;
        while(path->child != list->last){
        path = path->child;
        }
        free(list->last);
        list->last = path;
    }
    list->size--;
}

int access_sll(t_sll* list, int pos){
    assert(pos >= 1 &&pos <= list->size);
    t_elem_sll* path = list->first;
    for(int i=1; i<pos;i++){
        path = path->child;
    }
    return path->content;
}

void insert_content_list(t_sll *list, int content) {
    t_elem_sll* new = create_elem_sll(content);
    t_elem_sll* path = list->first;
    t_elem_sll*ant = NULL;
    while((path!= NULL) && (path->content < content)){
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


void remove_start_elem_list(t_sll* list){
    assert(list->last!=NULL);
    t_elem_sll* second = list->first->child;
    free(list->first);
    list->first = second;
    list->size--;
    if (second == NULL){
        list->last = NULL;
    }
    list->size--;
}

int main(){
    t_sll* list = create_list();
    insert_content_list(list,10);
    insert_content_list(list,9);
    printf("%d\n", access_sll(list,2));
    printf("%d\n", list->size);
}