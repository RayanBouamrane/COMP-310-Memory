//Name: Rayan Bouamrane
//ID: 260788250

#include <stdlib.h>
#include "pcb.h"

PCB *makePCB(int start, int end) {
    PCB *p = malloc(sizeof(PCB));
    (*p).PC = start;
    (*p).start = start;
    (*p).end = end;

    (*p).pages_max = 10;
    (*p).PC_offset = 0;
    (*p).PC_page = 0;

    for (int i = 0; i < 10; i++) {
        (*p).pageTable[i] = 0;
    }
    return p;
}