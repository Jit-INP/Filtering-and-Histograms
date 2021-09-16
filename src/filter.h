#ifndef FILTER_H
#define FILTER_H


#include "utils.h"
#include <stdlib.h>

void revFilter(pix *dst, pix *src);
void prodWFilter(pix *x, pix *h, pixprod *y);
pix *allocFilterMem(size_t eleSiz);
mfiltersum sumBuff(pix *buff, size_t limit);
mfiltersum summateFilter(pixprod *m);
void buildFilterSizMatrix(pix *op, pix *buf, size_t x, size_t y, size_t row, size_t col);
void genGausianKernel(pix *gKernel, pixprod *divFactor);

#endif // FILTER_H
