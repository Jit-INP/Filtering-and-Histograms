#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include <stdlib.h>

void chkMatrixValidity(pix *mat, size_t row, size_t col);
void printMatrix(unsigned char *buf, size_t eleSiz, size_t row, size_t col);
pix *allocMatMem(size_t r, size_t c, size_t eleSiz);
void cpyMatrix(pix *dst, pix *src, size_t r, size_t c);
void reverseMatrix(pix *revH, pix *h, size_t r, size_t c);
void prodMatrix(pix *x, pix *h, size_t r, size_t c, pixprod *y);
void matrixMul(pix *matA, size_t rowA, size_t colA, pix *matB, size_t rowB, size_t colB, mfiltersum **matC, size_t *rowC, size_t *colC);

#endif // MATRIX_H
