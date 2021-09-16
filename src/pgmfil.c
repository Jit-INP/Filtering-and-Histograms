#include "pgmfil.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "filutils.h"
#include "matrix.h"

void pgmToGraymap(const char *filNam, gray **graymap, size_t *row, size_t *col, size_t *maxVal, PGMType *type){
    NULL_PTR_CHK(filNam);
    NULL_PTR_CHK(graymap);
    NULL_PTR_CHK(row);
    NULL_PTR_CHK(col);
    NULL_PTR_CHK(type);

    FILE* ifp = fopen(filNam, "r");
    NULL_PTR_CHK(ifp);

    fileGetC( ifp );
    int ich2 = fileGetC( ifp );

    switch (ich2) {
    case '2':
        *type = eP2;
        break;
    case '5':
        *type = eP5;
        break;
    default:
        assert(0);
        break;
    }

    *col = (unsigned)pm_getint( ifp );
    *row = (unsigned)pm_getint( ifp );
    *maxVal = (unsigned)pm_getint( ifp );

    gray *ptr = *graymap = allocMatMem(*row, *col, sizeof (gray));

    for(size_t i=0; i < *row; ++i){
        for(size_t j=0; j < *col; ++j){
            gray val;
            if(*type == eP5){
                val = pm_getrawbyte(ifp);
            } else {
                val = (gray)pm_getint(ifp);
            }
            ptr[(i * (*col)) + j] = val;
        }
    }

    fclose(ifp);
}

void graymapToPgm(const char *filNam, gray *graymap, size_t row, size_t col, size_t maxVal, PGMType type){
    FILE* ifp = fopen(filNam, "w");
    NULL_PTR_CHK(ifp);

    if(type == eP5){
        fprintf(ifp, "P5\n");
    } else {
        fprintf(ifp, "P2\n");
    }
    fprintf(ifp, "%d %d\n", (signed)col, (signed)row);
    fprintf(ifp, "%d\n", (signed)maxVal);

    for(size_t i=0; i < row; ++i){
        for(size_t j=0; j < col; ++j){
            gray val = graymap[(i * col) + j];
            if(type == eP5){
                fprintf(ifp, "%c", val);
            } else {
                fprintf(ifp, "%d ", val);
            }
        }
    }

    fclose(ifp);
}
