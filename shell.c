//Name: Rayan Bouamrane
//ID: 260788250

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shell.h"

#define PROMPT "$ "

char rawString[STRING_LENGTH];
char *parsedString[4];

void printError(int e);

int parse(char rawStr[]) {

    for (int i = 0; i < 4; i++) { parsedString[i] = "\0"; }

    if (rawStr[STRING_LENGTH - 1] != '\0' && rawStr[STRING_LENGTH - 1] != '\r' && rawStr[STRING_LENGTH - 1] != '\377') {
        return 6;
    }

    if (rawStr[0] == '\377') return 0;

    if (parsedString[0] != NULL && parsedString[0][0] == EOF) { return 0; }

    parsedString[0] = strtok(rawStr, " " "\r" "\n" "\377");
    parsedString[1] = strtok(NULL, " " "\r" "\n" "\377");

    if (strcmp(parsedString[0], "set") == 0) {
        parsedString[2] = strtok(NULL, "\n" "\r" "\0" "\377");
    } else {
        parsedString[2] = strtok(NULL, " " "\r" "\n" "\377");
        parsedString[3] = strtok(NULL, "\n" "\r" "\0" "\377");
    }
    int errCode = (interpreter(parsedString));
    printError(errCode);
    return errCode;
}

void printError(int e) {
    if (e == 1)
        printf("Unknown command\n");
    else if (e == 2)
        printf("Too few arguments\n");
    else if (e == 3)
        printf("Too many arguments\n");
    else if (e == 4)
        printf("Variable does not exist\n");
    else if (e == 5)
        printf("Low Disk Space\n");
    else if (e == 6)
        printf("Max String length exceeded\n");
    else if (e == 7)
        printf("Script not found\n");
    else if (e == 8) {
        printf("Too many open files, shell terminated\n");
        exit(24);
    } else if (e == 9)
        printf("Script Terminated\n");
    else if (e == 10)
        printf("Your computer is low on memory\n");
}

int isRedir = 0;
int checkedRedir = 0;

int shellUI() {

    printf("Kernel 2.0 loaded!\n");
    printf("Welcome to Rayan's Shell\n");
    printf("Shell version 2.0 Created April 2020\n");

    int r = 0;

    while (1) {

        if (isScript == 0 && isRedir == 0) { printf(PROMPT); }

        isScript = 0;
        memset(rawString, 0, STRING_LENGTH);

        char ch = '\0';
        for (int i = 0; i < STRING_LENGTH; i++) {
            ch = getchar();

            if (ch == '\n')
                break;

            rawString[i] = ch;
        }

        for (int i = 0; i < STRING_LENGTH && checkedRedir == 0; i++) {
            if (r > 1) {
                isRedir = 1;
                break;
            }
            if (stdin->_IO_read_base[i] == '\n')
                r++;
        }
        checkedRedir = 1;

        if (ch == '\377') {
            freopen("/dev/tty", "rw", stdin);
            isRedir = 0;
            continue;
        }

        if (rawString[0] == '\0') {
            continue;
        }

        if (strcmp(rawString, "quit") == 0) {
            printf("Bye!\n");
            exit(EXIT_SUCCESS);
        }

        parse(rawString);

    }
}
