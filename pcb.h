//Name: Rayan Bouamrane
//ID: 260788250

#ifndef PCB_H
#define PCB_H

typedef struct
{
    int PC;
    int start;
    int end;
    int pageTable[10];
    int PC_page;
    int PC_offset;
    int pages_max;

}PCB;

PCB *makePCB(int start, int end);

#endif //PCB_H
