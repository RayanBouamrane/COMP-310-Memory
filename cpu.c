//Name: Rayan Bouamrane
//ID: 260788250

#include <stdlib.h>
#include <string.h>
#include "ram.h"
#include "shell.h"

typedef struct {
    int IP;
    char IR[1000];
    int quanta;
} CPU;

CPU *CPU_CORE;

void setIP(int i) { CPU_CORE->IP = i; }

void initializeCPU() {
    CPU_CORE = malloc(sizeof(CPU));
    CPU_CORE->IP = 0;
    CPU_CORE->quanta = 2;
}

void runCPU(int quanta) {
    for (int i = 0; i < quanta; i++) {
        strcpy(CPU_CORE->IR, getFromRAM(CPU_CORE->IP));

        if (strcmp("quit", CPU_CORE->IR) == 0) {
            CPU_CORE->IP = 1001;            //if command is quit, IP == 1001 (larger than any PCB->PC will ever be)
            return;                         //any instructions below quit won't run, but other programs may still run
        }
        else {
            parse(CPU_CORE->IR);
        }
        CPU_CORE->IP++;
    }
}