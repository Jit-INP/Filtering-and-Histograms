#ifndef HIST_H
#define HIST_H

#include "utils.h"
#include <stdlib.h>

pixprod *buildHist(pix *buf, size_t row, size_t col);
void stretchHist(pix *dstBuf, pix *srcBuf, size_t row, size_t col);
void eqHist(pix *dstBuf, pix *srcBuf, size_t row, size_t col);

#endif // HIST_H
