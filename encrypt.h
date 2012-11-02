#include "tablecheck.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encryptDES(FILE *f, FILE *tf, char* key, char mode);
void hex(unsigned int *val,int size);
unsigned int Xor(unsigned int a, unsigned int b);
unsigned int** subkeys(char* key, unsigned int* PC1, unsigned int* PC2, unsigned int* V, bool output);


