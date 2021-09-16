#include <string.h>
#include "convol.h"
#include "filter.h"
#include "matrix.h"

pix getConvPix(pix *x, pix *revH, pixprod divFactor){
    pixprod *y = (void *)allocFilterMem(sizeof (pixprod));
    prodWFilter( x, revH, y);
    mfiltersum sum = summateFilter(y);
    pix convPix = (pix) ( (double) sum / divFactor );
    free(y);
    return convPix;
}

pix convXY(pix *buf, size_t x, size_t y, size_t row, size_t col, pix *revH, pixprod divFactor){
    pix *tmp = allocFilterMem(sizeof (pix));
    buildFilterSizMatrix(tmp, buf, x, y, row, col);
    pix conv = getConvPix(tmp, revH, divFactor);
    free(tmp);
    return conv;
}

void convol(pix *dstBuff, pix *srcBuff, size_t row, size_t col, pix *h, pixprod divFactor){
    pix *revH = allocFilterMem(sizeof (pix));
    revFilter(revH, h);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            *(dstBuff + ( (i * col) + j) ) = convXY(srcBuff, i, j, row, col, revH, divFactor);
        }
    }
    free(revH);
    return;
}

void convolN(pix *dstBuff, pix *srcBuff, size_t row, size_t col, pix *h, pixprod divFactor, size_t n){
    chkMatrixValidity(srcBuff, row, col);
    NULL_PTR_CHK(dstBuff);
    ABOVE_ZERO_CHK(divFactor);
    ABOVE_ZERO_CHK(n);
    SAME_PTR_CHK(dstBuff, srcBuff);

    pix *tmpBuff = allocMatMem(row, col, sizeof (pix));
    cpyMatrix(tmpBuff, srcBuff, row, col);
    for (size_t i = 0; i < n; ++i) {
        convol(dstBuff, tmpBuff, row, col, h, divFactor);
        cpyMatrix(tmpBuff, dstBuff, row, col);
    }
    free(tmpBuff);
    return;
}

void binomFilConvolN(pix *dstBuff, pix *srcBuff, size_t row, size_t col, size_t n){
    pix *h = allocFilterMem(sizeof (pix));
    pixprod divFactor;
    genGausianKernel( h, &divFactor);
    convolN(dstBuff, srcBuff, row, col, h, divFactor, n);
}
