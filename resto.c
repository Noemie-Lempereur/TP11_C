#include "resto.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Resto* createResto(char* name, int quality, int distance){
    struct Resto* r=malloc(sizeof(struct Resto));
    if(r!=NULL) {
        char* n = malloc(strlen(name)*sizeof(char));
        strcpy(n, name);
        r->name=n;
        r->distance=distance;
        r->quality=quality;
        r->time=999;
    }
    return r;
}
char* getName(struct Resto* r){
    if(r!=NULL){
        return r->name;
    }
    return NULL;
}
int getQuality(struct Resto* r){
    if(r!=NULL){
        return r->quality;
    }
}
int getDistance(struct Resto* r){
    if(r!=NULL){
        return r->distance;
    }
    return -1;
}
int getTime(struct Resto* r){
    if(r!=NULL){
        return r->time;
    }
    return -1;
}
void updateTime(struct Resto* r, int newTime){
    r->time=newTime;
}
void deleteResto(struct Resto* r){
    free(r->name);
    free(r);
}
void printResto(struct Resto* r){
    printf("Name:%s\nDistance:%d\nQuality:%d\nTime:%d\n",getName(r),getDistance(r),getQuality(r),getTime(r));
}