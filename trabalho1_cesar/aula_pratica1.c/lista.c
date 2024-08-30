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

void print_list(t_sll* list){

}

void destroy_sll(t_sll* list){
    assert(list->first==NULL);
    free(list);
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
}

int main(){
    t_sll* list = create_list();
    insert_start_elem_list(list,10);
    insert_end_elem_list(list,12);
    printf("%d\n", list->size);
    print_list(list);
}