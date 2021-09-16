#include "median.h"
#include "filter.h"
#include "matrix.h"

int medComp(const void *ele1, const void *ele2){
    pix f = *((pix*)ele1);
    pix s = *((pix*)ele2);
    if (f > s){
        return  1;
    }
    if (f < s){
        return -1;
    }
    return 0;
}

void sortMedianMatrix(pix *y){
    qsort(y, FILTER_SIZ * FILTER_SIZ, sizeof (pix), medComp);
}

pix getMedPix(pix *x){
    pix *y = (void *)allocFilterMem(sizeof (pix));
    cpyMatrix(y, x, FILTER_SIZ, FILTER_SIZ);
    sortMedianMatrix(y);
    pix medPix = y[(FILTER_SIZ * FILTER_SIZ) / 2];
    free(y);
    return medPix;
}

pix medianXY(pix *buf, size_t x, size_t y, size_t row, size_t col){
    pix *tmp = allocFilterMem(sizeof (pix));
    buildFilterSizMatrix(tmp, buf, x, y, row, col);
    pix med = getMedPix(tmp);
    free(tmp);
    return med;
}

void median(pix *dstBuff, pix *srcBuff, size_t row, size_t col){
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            *(dstBuff + ( (i * col) + j) ) = medianXY(srcBuff, i, j, row, col);
        }
    }
    return;
}

void medianN(pix *dstBuff, pix *srcBuff, size_t row, size_t col, size_t n){
    chkMatrixValidity(srcBuff, row, col);
    NULL_PTR_CHK(dstBuff);
    ABOVE_ZERO_CHK(n);

    pix *tmpBuff = allocMatMem(row, col, sizeof (pix));
    cpyMatrix(tmpBuff, srcBuff, row, col);
    for (size_t i = 0; i < n; ++i) {
        median(dstBuff, tmpBuff, row, col);
        cpyMatrix(tmpBuff, dstBuff, row, col);
    }
    free(tmpBuff);
    return;
}
