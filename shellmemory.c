//Name: Rayan Bouamrane
//ID: 260788250

#include <stdlib.h>
#include <string.h>

typedef struct {
	char *var;
	char *value;
} MEM;

#define MEM_SIZE 100
MEM memory[MEM_SIZE];

int getVarLocation(char *pVar) {
	for (int i = 0; i < MEM_SIZE; i++) {
		if (memory[i].var != NULL && strcmp(pVar, memory[i].var) == 0) {
			return i;
		}
	}
	return -1;
}

int getFreeSpace() {
	for (int i = 0; i < MEM_SIZE; i++) {
		if (memory[i].var == NULL) {
			return i;
		}
	}
	return -1;
}

char* getValue(char *pVar) {
	for (int i = 0; i < MEM_SIZE; i++) {
		if (memory[i].var != NULL)
			if (strcmp(pVar, memory[i].var) == 0) {
			return memory[i].value;
		}
	}
	return NULL;
}

int copyToMemory(char *pVar, char *pValue) {

	int m;

	if (getValue(pVar) == NULL) {
		m = getFreeSpace();
	} else
		m = getVarLocation(pVar);
	if (m != -1) {
		MEM temp = memory[m];
		temp.var = calloc(strlen(pVar), 1);
		temp.value = calloc(strlen(pValue), 1);
		strcpy(temp.var, pVar);
		strcpy(temp.value, pValue);
		memory[m] = temp;
		return 0;
	}
	return 5;
}

