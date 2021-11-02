//Name: Rayan Bouamrane
//ID: 260788250

#ifndef KERNEL_H
#define KERNEL_H

#include "pcb.h"

void addToReady(PCB *pcb);
void scheduler();
PCB dequeue();
void initializePCBs();

#endif //KERNEL_H