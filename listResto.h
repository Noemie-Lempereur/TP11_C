#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef TP11_RESTO_H
#define TP11_RESTO_H

struct CellResto{
    struct Resto* r;
    struct CellResto* next;
};
struct ListResto{
    int size;
    struct CellResto* head;
};

struct CellResto* createCell(struct Resto* r);
struct ListResto* createEmptyList();
void addFirst(struct ListResto* l, struct Resto* r);
bool isEmptyList(struct ListResto* l);
struct CellResto* getItemPos(struct ListResto* l, int position, bool* valid);
void deleteFirst(struct ListResto* l);
void printList(struct ListResto* l);
int listSize(struct ListResto* l);
void addItemPos(struct ListResto* l, struct Resto* r, int position, bool* valid);
void deleteItemPos(struct ListResto* l, int position, bool* valid);
void deleteList(struct ListResto* l);
struct ListResto* readRestos(char* nameFile);
struct Resto* bestResto(struct ListResto* l);

#endif