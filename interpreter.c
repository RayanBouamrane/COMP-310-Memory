//Name: Rayan Bouamrane
//ID: 260788250

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shellmemory.h"
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "kernel.h"
#include "cpu.h"

int help();

int print(char *pVar);

int set(char *pVar, char *pValue);

int run(char *filename);

int exec(char *p1, char *p2, char *p3);

int quit();

int interpreter(char *parsedString[]) {

    if (parsedString[0] == NULL) {
        return 0;

    } else if (strcmp(parsedString[0], "help") == 0) {
        if (parsedString[1] != NULL || parsedString[2] != NULL)
            return 3;
        return help();

    } else if (strcmp(parsedString[0], "quit") == 0) {
        if (parsedString[1] != NULL || parsedString[2] != NULL)
            return 3;
        quit();
        return 0;
    } else if (strcmp(parsedString[0], "print") == 0) {
        if (parsedString[1] == NULL) {
            return 2;
        }
        if (parsedString[2] != NULL)
            return 3;
        return print(parsedString[1]);

    } else if (strcmp(parsedString[0], "set") == 0) {
        if (parsedString[1] == NULL || parsedString[2] == NULL) {
            return 2;
        }
        return set(parsedString[1], parsedString[2]);

    } else if (strcmp(parsedString[0], "run") == 0) {
        if (parsedString[1] == NULL) {
            return 2;
        }
        if (parsedString[2] != NULL)
            return 3;

        return run(parsedString[1]);

    } else if (strcmp(parsedString[0], "exec") == 0) {
        if (parsedString[1] == NULL) {
            return 2;
        }
        return exec(parsedString[1], parsedString[2], parsedString[3]);
    }
    return 1;
}

int help() {
    printf("COMMAND\t\t\tDESCRIPTION\n"
           "help\t\t\t\tDisplays all the commands\n"
           "quit\t\t\t\tExits / terminates the shell with “Bye!”\n"
           "set VAR STRING\t\t\tAssigns a value to shell memory\n"
           "print VAR\t\t\tDisplays the STRING assigned to VAR\n"
           "run SCRIPT.TXT\t\t\tExecutes the file SCRIPT.TXT\n"
           "exec p1 p2 p3\t\t\tExecutes concurrent programs\n");
    return 0;
}

int quit() {
    if (isScript == 0) {
        printf("Bye!\n");
        exit(EXIT_SUCCESS);
    } else {
        return 999;
    }
}

int print(char *pVar) {
    char *temp = getValue(pVar);
    if (temp != NULL) {
        printf("%s\n", temp);
        return 0;
    }
    return 4;
}

int set(char *pVar, char *pValue) {
    return copyToMemory(pVar, pValue);
}

int run(char *filename) {
    isScript = 1;
    FILE *pFile = fopen(filename, "r");
    if (pFile == NULL) {
        isScript = 0;
        if (errno == 24)
            return 8;
        return 7;
    }
    char line[STRING_LENGTH];
    memset(line, 0, STRING_LENGTH);

    char c = '\0';

    while (1) {
        memset(line, 0, STRING_LENGTH);

        for (int i = 0; i < STRING_LENGTH; i++) {
            c = fgetc(pFile);
            if (c == '\n') {
                break;
            }
            line[i] = c;
        }

        if (line[0] == EOF) {
            isScript = 0;
            fclose(pFile);
            return 0;
        }
        int x = parse(line);

        if (x == 999) {
            isScript = 0;
            break;
        } else if (x != 0) {
            isScript = 0;
            return 9;
        }
    }
}

int myinit(char *filename) {

    FILE *pFile = fopen(filename, "r");
    if (pFile == NULL) {
        isScript = 0;
        if (errno == 24)
            return 8;
        return 7;
    }

    PCB *pcb = makePCB(0, 0);
    int *start = &pcb->start;
    int *end = &pcb->end;

    addToReady(pcb);
    addToRam(pFile, start, end);

    pcb->PC = *start;

    return 0;
}

int exec(char *p1, char *p2, char *p3) {

    isScript = 1;

    int e = myinit(p1);
    if (e != 0) {
        isScript = 0;
        return e;
    }

    if (p2 != NULL) {
        if (strcmp(p1, p2) == 0) {
            isScript = 0;
            printf("Error: Script %s already loaded\n", p1);
        } else {
            e = myinit(p2);
            if (e != 0) {
                isScript = 0;
                return e;
            }
        }
    }

    if (p3 != NULL) {
        if (strcmp(p1, p3) == 0) {
            isScript = 0;
            printf("Error: Script %s already loaded\n", p1);
        } else if (strcmp(p2, p3) == 0) {
            isScript = 0;
            printf("Error: Script %s already loaded\n", p2);
        } else {
            e = myinit(p3);
            if (e != 0) {
                isScript = 0;
                return e;
            }
        }
    }

    scheduler();

    initializeRAM();
    initializeCPU();
    initializePCBs();

    isScript = 0;

    return 0;
}