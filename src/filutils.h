#ifndef FILUTILS_H
#define FILUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int fileGetC(FILE *fileH);
char pm_getc(FILE* file);
bit pm_getbit(FILE* file);
unsigned char pm_getrawbyte(FILE* file);
int pm_getint( FILE* file);

#endif // FILUTILS_H
