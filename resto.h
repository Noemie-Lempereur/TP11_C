#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef TP11_LISTRESTO_H
#define TP11_LISTRESTO_H
struct Resto{
    char* name;
    int quality;
    int distance;
    int time;
};

struct Resto* createResto(char* name, int quality, int distance);
char* getName(struct Resto* r);
int getQuality(struct Resto* r);
int getDistance(struct Resto* r);
int getTime(struct Resto* r);
void updateTime(struct Resto* r, int newTime);
void deleteResto(struct Resto* r);
void printResto(struct Resto* r);

#endif //TP11_LISTRESTO_H
