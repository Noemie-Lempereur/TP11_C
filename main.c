#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listResto.h"
#include "resto.h"


int main() {
    struct ListResto* list =createEmptyList();
    list= readRestos("restos.txt");
    bool val;
    struct Resto* resto;
    for(int j=0;j<20;j++){
        resto=bestResto(list);
        printf("%d) %s\n",j+1,getName(resto));
        resto->time=-1;
        for(int a=0;a<listSize(list);a++){
            getItemPos(list,a,&val)->r->time++;
        }
    }
    return 0;
}

