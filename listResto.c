#include "listResto.h"
#include "resto.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct CellResto* createCell(struct Resto* r){
    struct CellResto* Resto=malloc(sizeof(struct CellResto));
    if(Resto!=NULL) {
        Resto->r=r;
        Resto->next=NULL;
    }
    return Resto;
}
struct ListResto* createEmptyList(){
    struct ListResto* liste=malloc(sizeof(struct CellResto));
    if(liste!=NULL) {
        liste->size=0;
        liste->head=NULL;
    }
    return liste;
}
void addFirst(struct ListResto* l, struct Resto* r){
    if(l != NULL) {
        struct CellResto *newHead = createCell(r);
        newHead->next = l->head;
        l->head = newHead;
        l->size = l->size + 1;
    }
}
bool isEmptyList(struct ListResto* l){
    if (listSize(l)==0){
        return true;
    }
    return false;
}

struct CellResto* getItemPos(struct ListResto* l, int position, bool* valid){
    int Size=l->size;
    if((position<0)||(position>=Size)||(l->head==NULL)){
        *valid=false;
        return NULL;
    }
    int i=0;
    struct CellResto* iter=l->head;
    while (i < position) {
        iter = iter->next;
        i++;
    }
    *valid=true;
    return iter;
}
void deleteFirst(struct ListResto* l){
    if(l->head==NULL){
        return;
    }
    struct CellResto* Head=l->head;
    struct CellResto* newHead=Head->next;
    free(Head);
    l->head=newHead;
    l->size=l->size-1;
}
void printList(struct ListResto* l){
    if (isEmptyList(l)==true) {
        printf("NULL\n");
    }
    else {
        struct CellResto *itr = l->head;
        while (itr->next != NULL) {
            printResto(itr->r);
            itr = itr->next;
        }
        printResto(itr->r);
    }
}
int listSize(struct ListResto* l){
    return l->size;
}
void addItemPos(struct ListResto* l, struct Resto* r, int position, bool* valid){
    struct CellResto *previous = l->head;
    int i = 0;
    if (position == 0) {
        addFirst(l,r);
        *valid = true;
        return;
    }
    if ((position < 0) || (position >= listSize(l)+1) || (l->head==NULL)) {
        *valid = false;
        return;
    }
    struct CellResto *new = createCell(r);
    while (i < position -1) {
        previous = previous->next;
        i++;
    }
    new->next = previous->next;
    previous->next = new;
    *valid = true;
    l->size=l->size+1;
}
void deleteItemPos(struct ListResto* l, int position, bool* valid){
    int i = 0;
    struct CellResto *itr=l->head;
    struct CellResto *nextcell=l->head;
    if((position<0)||(position>=l->size)||(l->head==NULL)){
        *valid=false;
        return;
    }
    if (position==0){
        deleteFirst(l);
        *valid=true;
        return;
    }
    while (i < position-1) {
        itr = itr->next;
        i++;
    }
    nextcell=itr->next;
    itr->next=nextcell->next;
    free(nextcell);
    *valid=true;
    l->size=l->size-1;
}

void deleteList(struct ListResto* l){
    if(l!=NULL) {
        struct CellResto *current = l->head;
        struct CellResto *next;
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        l->head = NULL;
    }
    free(l);
}

struct ListResto* readRestos(char* nameFile) {
    FILE* file = fopen("restos.txt", "r");
    if(file == NULL) {
        return NULL;
    }
    char name[500];
    int quality=0;
    int distance=0;
    struct ListResto* list = createEmptyList();
    while(! feof(file)){
        fgets(name,500,file);
        name[strlen(name)-1]='\0';
        fscanf(file, "%d %d\n", &quality, &distance);
        //printf("Name : %s\nDistance : %d \nQuality : %d\n", name, distance, quality);
        struct Resto *rest = createResto(name, quality, distance);
        addFirst(list, rest);
    }
    fclose(file);
    return list;
}
/*
struct Resto* bestResto(struct ListResto* l){
    struct ListResto* list = readRestos("restos.txt");
    int i=0;
    bool valid=true;
    int a;
    int amax;
    amax=max{0,(getItemPos(list,0,&valid)->r->quality)-((getItemPos(list,0,&valid)->r->distance)*(getItemPos(list,0,&valid)->r->distance))+pow(2,(min{(getItemPos(list,0,&valid)->r->time),10}))};
    for (int k=1;k<list->size;k++){
        a=max{0,(getItemPos(list,k,&valid)->r->quality)-((getItemPos(list,k,&valid)->r->distance)*(getItemPos(list,k,&valid)->r->distance))+pow(2,(min{(getItemPos(list,k,&valid)->r->time),10}))};
        if(a>amax){
            i=k;
            amax=a;
        }
    }
    return getItemPos(list,i,&valid)->r;
}*/
struct Resto* bestResto(struct ListResto* l){
    int i=0;
    bool valid=true;
    int a;
    int amax;
    int b;
    b=getItemPos(l,0,&valid)->r->time;
    if(b>10){
        b=10;
    }
    amax=getItemPos(l,0,&valid)->r->quality-((getItemPos(l,0,&valid)->r->distance)*(getItemPos(l,0,&valid)->r->distance))+b*b;
    if(amax<0){
        amax=0;
    }
    for (int k=1;k<l->size;k++){
        b=getItemPos(l,k,&valid)->r->time;
        if(b>10){
            b=10;
        }
        a=getItemPos(l,k,&valid)->r->quality-((getItemPos(l,k,&valid)->r->distance)*(getItemPos(l,k,&valid)->r->distance))+b*b;
        if(a<0){
            a=0;
        }
        if(a>=amax){
            i=k;
            amax=a;
        }
    }
    struct Resto* resto=getItemPos(l,i,&valid)->r;
    return resto;
}