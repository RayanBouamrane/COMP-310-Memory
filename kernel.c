//Name: Rayan Bouamrane
//ID: 260788250

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"

struct pcbNode {
    PCB *p;
    struct pcbNode *next;
};

struct pcbNode *head;
struct pcbNode *tail;

void initializePCBs() {
    head = NULL;
    tail = NULL;
}

void addToReady(PCB *pcb) {

    struct pcbNode *newNode = malloc(sizeof(struct pcbNode));
    newNode->p = pcb;
    newNode->next = NULL;

    if (head == NULL && tail == NULL) {
        head = newNode;
        tail = newNode;
    } else if (head == NULL) {
        head = newNode;
    } else if (head->next == NULL) {
        head->next = newNode;
        tail->next = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

struct pcbNode dequeue() {
    if (head != NULL) {
        struct pcbNode temp = *head;
        if (head->next == NULL) {
            head = NULL;
        } else
            *head = *head->next;
        return temp;
    }
}

int min(int a, int b) {
    if (a < b) return a; else return b;
}

void scheduler() {
    int x = 5;
    while (1) {
        struct pcbNode temp = dequeue();
        PCB *p = malloc(sizeof(PCB));

        p->PC = temp.p->PC;
        p->start = temp.p->start;
        p->end = temp.p->end;

        setIP(p->PC);

        int quanta = min(1 + p->end - p->PC, 2);

        if (quanta < 1) {
            if (temp.next == NULL) {
                free(p);
                return;
            }

            free(p);

            continue;
        }

        runCPU(quanta);
        p->PC += quanta;
        addToReady(p);
    }
}

void boot() {
    initializeRAM();
    system("rm -rf BackingStore && mkdir BackingStore");
}

void kernel() {

//    freopen("/home/rayan/Projects/CLion/COMP_310_A2/testfile.txt", "r", stdin);

    isScript = 0;

    initializeCPU();
    initializePCBs();

    shellUI();

}

int main(int argc, const char **argv) {

    boot();
    kernel();

}