#ifndef IMGOPER_H
#define IMGOPER_H

#include <stdlib.h>

void doBinConv(const char* ipFilNam, size_t n);
void doMedianFilter(const char* ipFilNam, size_t n);
void doHistStch(const char* ipFilNam);
void doHistEq(const char* ipFilNam);
void doAll(const char *ipFilNam, size_t n);

#endif // IMGOPER_H
