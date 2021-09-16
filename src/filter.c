#include "filter.h"
#include <string.h>
#include "matrix.h"

void revFilter(pix *dst, pix *src){
    reverseMatrix(dst, src, FILTER_SIZ, FILTER_SIZ);
}

void prodWFilter(pix *x, pix *h, pixprod *y){
    prodMatrix(x, h, FILTER_SIZ, FILTER_SIZ, y);
}

pix *allocFilterMem(size_t eleSiz){
    return allocMatMem(FILTER_SIZ, FILTER_SIZ, eleSiz);
}

mfiltersum summateFilter(pixprod *m){
    NULL_PTR_CHK(m);

    mfiltersum sum = 0;
    for (size_t i = 0; i < FILTER_SIZ; ++i) {
        for (size_t j = 0; j < FILTER_SIZ; ++j) {
            sum += m[ (i * FILTER_SIZ) + j];
        }
    }
    return sum;
}

mfiltersum sumBuff(pix *buff, size_t limit){
    NULL_PTR_CHK(buff);

    mfiltersum sum = 0;
    for (size_t i = 0; i <= limit; ++i) {
        sum += buff[i];
    }
    return sum;
}

void buildFilterSizMatrix(pix *op, pix *buf, size_t x, size_t y, size_t row, size_t col){
    chkMatrixValidity(buf, row, col);
    NULL_PTR_CHK(op);
    SAME_PTR_CHK(buf, op);

    int mid = FILTER_SIZ / 2;
    for (int i = -mid; i <= mid; ++i) {
        for (int j = -mid; j <= mid; ++j) {
            if( ( ((signed)x + i) < 0 ) || ( ((signed)y + j) < 0 ) || ( ((signed)x + i) > (signed)(row - 1) ) || ( ((signed)y + j) > (signed)(col - 1) ) ){
                op[( (i + mid) * FILTER_SIZ) + (j + mid)] = 0;
            } else {
                op[( (i + mid) * FILTER_SIZ) + (j + mid)] = buf [ ( ((signed)x + i) * (signed)col ) + ((signed)y + j)];
            }
        }
    }
}

void genPascalNbs( pix *pascBuf){
    pix *pascMat = allocFilterMem(sizeof (pix));
    memset(pascMat, 1, FILTER_SIZ);
    for (size_t i = 1; i < FILTER_SIZ; ++i) {
        for (size_t j = 0; j < FILTER_SIZ; ++j) {
            pascMat[(i * FILTER_SIZ) + j] = (pix) sumBuff(pascMat + ( (i - 1) * FILTER_SIZ), j);
        }
    }
    for (size_t k = 0; k < FILTER_SIZ; ++k){
        size_t i = FILTER_SIZ - 1 - k;
        size_t j = k;
        pascBuf[k] = pascMat[(i * FILTER_SIZ) + j];
    }
    free(pascMat);
}

void genGausianKernel(pix *gKernel, pixprod *divFactor){
    NULL_PTR_CHK(gKernel);
    NULL_PTR_CHK(divFactor);

    pix *pascNb = malloc(FILTER_SIZ * sizeof (pix));
    genPascalNbs(pascNb);
    mfiltersum *buf;
    size_t tmp;
    matrixMul(pascNb, FILTER_SIZ, 1, pascNb, 1, FILTER_SIZ, &buf, &tmp, &tmp);
    for (size_t i = 0; i < FILTER_SIZ; ++i) {
        for (size_t j = 0; j < FILTER_SIZ; ++j) {
            gKernel[ (i * FILTER_SIZ) + j] = *((pix*)buf + ( (i * FILTER_SIZ) + j) * sizeof (mfiltersum));
        }
    }
    free(buf);
    pixprod sum = (pixprod) sumBuff(pascNb, FILTER_SIZ - 1);
    *divFactor = sum * sum;
    free(pascNb);
}
