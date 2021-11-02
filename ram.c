//Name: Rayan Bouamrane
//ID: 260788250

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

#define RAM_SIZE 1000

char *ram[RAM_SIZE];

void initializeRAM() { for (int i = 0; i < RAM_SIZE; i++) { ram[i] = NULL; }}

int findSpace() {
    for (int i = 0; i < RAM_SIZE; i++) {
        if (ram[i] == NULL)
            return i;
    }
    return RAM_SIZE;
}

void printRAM() {
    for (int i = 0; i < RAM_SIZE; i++) {
        if (ram[i] != NULL) {
            printf("%s\n", ram[i]);
        }
    }
}

int addToRam(FILE *p, int *start, int *end) {

    char line[STRING_LENGTH];
    char c;

    *start = findSpace();

    while (1) {
        c = '\0';
        memset(line, 0, STRING_LENGTH);

        for (int i = 0; i < STRING_LENGTH; i++) {
            c = (char) fgetc(p);
            if (c == '\n' || c == '\r' || c == EOF) {
                break;
            }
            line[i] = c;
        }


        if (strlen(line) > 1) {
            int slot = findSpace();
            if (slot == RAM_SIZE) {
                return 10;
            } else {
                ram[slot] = strdup(line);
            }

        }
        if (c == EOF) break;
    }

    *end = findSpace() - 1;

    return 0;

}

char *getFromRAM(int i) {
    if (ram[i] != NULL)
        return ram[i];
    else return NULL;
}