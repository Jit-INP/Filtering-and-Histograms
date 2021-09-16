#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void chkMatrixValidity(pix *mat, size_t row, size_t col){
    NULL_PTR_CHK(mat);
    ABOVE_ZERO_CHK(row);
    ABOVE_ZERO_CHK(col);
}

void printMatrix(unsigned char *buf, size_t eleSiz, size_t row, size_t col){
    chkMatrixValidity(buf, row, col);
    assert(eleSiz > 0);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            printf("%d ", buf[((i * col) + j) * eleSiz]);
        }
        printf("\n");
    }
    printf("\n");
}

pix *allocMatMem(size_t r, size_t c, size_t eleSiz){
    ABOVE_ZERO_CHK(r);
    ABOVE_ZERO_CHK(c);
    ABOVE_ZERO_CHK(eleSiz);

    return malloc(r * c * eleSiz);
}

void cpyMatrix(pix *dst, pix *src, size_t r, size_t c){
    chkMatrixValidity(src, r, c);
    NULL_PTR_CHK(dst);
    SAME_PTR_CHK(dst, src);

    memcpy(dst, src, r * c);
}

void reverseMatrix(pix *revH, pix *h, size_t r, size_t c){
    chkMatrixValidity(h, r, c);
    NULL_PTR_CHK(revH);
    SAME_PTR_CHK(revH, h);

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            revH[(i * c) + j] = h[( ( (r - 1) - i ) * c ) + ( ( c - 1 ) - j )];
        }
    }
}

void prodMatrix(pix *x, pix *h, size_t r, size_t c, pixprod *y){
    chkMatrixValidity(x, r, c);
    NULL_PTR_CHK(h);
    NULL_PTR_CHK(y);
    SAME_PTR_CHK(x, (void *)y);
    SAME_PTR_CHK(h, (void *)y);

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            y[((i * c) + j)] = (pixprod) (x[(i * c) + j] * h[(i * c) + j]);
        }
    }
}


void getMatAEle(pix *mat, size_t col, size_t rowNo, pix *arr){
    for (size_t j = 0; j < col; ++j) {
        arr[j] = mat[ (rowNo * col) + j];
    }
}

void getMatBEle(pix *mat, size_t nbRow, size_t nbCol, size_t colNo, pix *arr){
    for (size_t i = 0; i < nbRow; ++i) {
        arr[i] = mat[ (i * nbCol) + colNo];
    }
}

mfiltersum multEle(pix *matA, pix *matB, size_t nbEle){
    mfiltersum sum = 0;
    for (size_t i = 0; i < nbEle; ++i) {
        sum += (matA[i] * matB[i]);
    }
    return sum;
}

void matrixMul(pix *matA, size_t rowA, size_t colA, pix *matB, size_t rowB, size_t colB, mfiltersum **matC, size_t *rowC, size_t *colC){
    chkMatrixValidity(matA, rowA, colA);
    chkMatrixValidity(matB, rowB, colB);
    NULL_PTR_CHK(matC);
    NULL_PTR_CHK(rowC);
    NULL_PTR_CHK(colC);
    SAME_PTR_CHK(*matC,(void*)matA);
    SAME_PTR_CHK(*matC,(void*)matB);
    assert(colA == rowB);

    *rowC = rowA;
    *colC = colB;
    *matC = (void *)allocMatMem(rowA, colB, sizeof(mfiltersum));

    mfiltersum *p = *matC;

    for (size_t i = 0; i < rowA; ++i) {
        for (size_t j = 0; j < colB; ++j) {
            pix *arrA = allocMatMem(1, colA, sizeof (pix));
            getMatAEle(matA, colA, i, arrA);

            pix *arrB = allocMatMem(rowB, 1, sizeof (pix));
            getMatBEle(matB, rowB, colB, j, arrB);

            p[(i * colB) + j] = multEle(arrA, arrB, colA);

            free(arrA);
            free(arrB);
        }
    }
}
