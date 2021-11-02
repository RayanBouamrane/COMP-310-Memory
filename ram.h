//Name: Rayan Bouamrane
//ID: 260788250

#ifndef RAM_H
#define RAM_H

#include <stdio.h>

int addToRam(FILE *p, int *start, int *end);

void initializeRAM();

void printRAM();

int findSpace();

char *getFromRAM(int i);

#endif //RAM_H
