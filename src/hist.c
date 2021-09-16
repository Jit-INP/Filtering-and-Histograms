#include "hist.h"
#include <string.h>
#include "matrix.h"
#include "filter.h"

pixprod *buildHist(pix *buf, size_t row, size_t col){
    chkMatrixValidity(buf, row, col);
    pixprod *hist = malloc(sizeof (pixprod) * (MAX_PIX_VAL + 1));
    memset(hist, 0, sizeof (pixprod) * (MAX_PIX_VAL + 1));
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            hist[buf[(i * col) + j]]++;
        }
    }
    return hist;
}

pix findMinIndex(pixprod *buf, size_t nbEle){
    pix minI = (pix)nbEle;
    for (size_t i = 0; i < nbEle; ++i) {
        if(buf[i] != 0){
            minI = (pix)i;
            break;
        }
    }
    assert(minI != nbEle);
    return minI;
}

pix findMaxIndex(pixprod *buf, size_t nbEle){
    pix maxI = (pix)nbEle;
    for (size_t i = nbEle - 1; i != 0; --i) {
        if(buf[i] != 0){
            maxI = (pix)i;
            break;
        }
    }
    assert(maxI != nbEle);
    return maxI;
}

pix keepInRange(int val){
    if( val < 0){
        val = 0;
    }
    if( val > MAX_PIX_VAL){
        val = MAX_PIX_VAL;
    }
    return (pix) val;
}

void stretchHist(pix *dstBuf, pix *srcBuf, size_t row, size_t col){
    chkMatrixValidity(srcBuf, row, col);
    NULL_PTR_CHK(dstBuf);
    SAME_PTR_CHK(dstBuf, srcBuf);

    pixprod *hist = buildHist(srcBuf, row, col);
    pix iMin = findMinIndex(hist, sizeof (pix) * MAX_PIX_VAL);
    pix iMax = findMaxIndex(hist, sizeof (pix) * MAX_PIX_VAL);
    pix iDel = iMax - iMin;
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            pix iCur = srcBuf[ (i * col) + j ];
            signed int val = (int)( ( (iCur - iMin) * MAX_PIX_VAL ) / (double) iDel );
            dstBuf[ (i * col) + j ] = keepInRange(val);
        }
    }
    free(hist);
}

#include<stdio.h>
mfiltersum cdfBuff(pixprod *buff, size_t limit){
    NULL_PTR_CHK(buff);

    mfiltersum sum = 0;
    for (size_t i = 0; i <= limit; ++i) {
        sum += buff[i];
    }
    return sum;
}

pix histEqXY(pixprod *histBuf, pix *imgBuf, size_t x, size_t y, size_t row, size_t col ){
    mfiltersum sum = cdfBuff(histBuf, imgBuf[(x * col) + y]);
    mfiltersum eqXY = (mfiltersum) ( ( (double)(sum * MAX_PIX_VAL) ) / (row * col) );
    return keepInRange((int)eqXY);
}

void eqHist(pix *dstBuf, pix *srcBuf, size_t row, size_t col){
    chkMatrixValidity(srcBuf, row, col);
    NULL_PTR_CHK(dstBuf);
    SAME_PTR_CHK(dstBuf, srcBuf);

    pixprod *hist = buildHist(srcBuf, row, col);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            *(dstBuf + ( (i * col) + j) ) = histEqXY(hist, srcBuf, i, j, row, col);
        }
    }

    free(hist);
    return;
}
