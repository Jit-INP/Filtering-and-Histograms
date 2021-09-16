#ifndef MATRIXMUL_H
#define MATRIXMUL_H

#include "utils.h"
#include <stdlib.h>

void convolN(pix *dstBuff, pix *srcBuff, size_t row, size_t col, pix *h, pixprod divFactor, size_t n);
void binomFilConvolN(pix *dstBuff, pix *srcBuff, size_t row, size_t col, size_t n);

#endif // MATRIXMUL_H
