#include "imgoper.h"

#include <stdio.h>
#include <string.h>

#include "convol.h"
#include "median.h"
#include "pgmfil.h"
#include "matrix.h"
#include "filter.h"
#include "hist.h"

void mkOpName(char *opNam, const char *opStr, const char *ipNam, size_t strSiz){
    const char *iPtr = ipNam;
    char *oPtr = opNam;
    size_t cnt = 0;
    while( ((*iPtr != '\0') && (*iPtr != '.')) && (cnt < strSiz - 5)){
        *oPtr = *iPtr;
        ++iPtr;
        ++oPtr;
        ++cnt;
    }
    const char *kPtr = opStr;
    while( (*kPtr != '\0') && (cnt < strSiz - 5)){
        *oPtr = *kPtr;
        ++kPtr;
        ++oPtr;
        ++cnt;
    }
    *oPtr = FILTER_SIZ + '0';
    ++oPtr;
    *oPtr = '.';
    ++oPtr;
    *oPtr = 'p';
    ++oPtr;
    *oPtr = 'g';
    ++oPtr;
    *oPtr = 'm';
    ++oPtr;
    *oPtr = 0;
}

void doBinConv(const char* ipFilNam, size_t n){
    gray *graymap;
    size_t row, col, maxVal;
    PGMType type;

    pgmToGraymap(ipFilNam, &graymap, &row, &col, &maxVal, &type);

    gray *biConv = allocMatMem(row, col, sizeof (gray));
    binomFilConvolN(biConv, graymap, row, col, n);

    char convOpFilNam[MAX_FIL_NAM_SIZ];
    mkOpName(convOpFilNam, "BiConv", ipFilNam, sizeof (convOpFilNam));
    graymapToPgm(convOpFilNam, biConv, row, col, maxVal, type);
    free(graymap);
    free(biConv);
}

void doMedianFilter(const char* ipFilNam, size_t n){
    gray *graymap;
    size_t row, col, maxVal;
    PGMType type;

    pgmToGraymap(ipFilNam, &graymap, &row, &col, &maxVal, &type);

    gray *med = allocMatMem(row, col, sizeof (gray));
    medianN(med, graymap, row, col, n);

    char medOpFilNam[MAX_FIL_NAM_SIZ];
    mkOpName(medOpFilNam, "Med", ipFilNam, sizeof (medOpFilNam));
    graymapToPgm(medOpFilNam, med, row, col, maxVal, type);
    free(graymap);
    free(med);
}

void doHistStch(const char* ipFilNam){
    gray *graymap;
    size_t row, col, maxVal;
    PGMType type;

    pgmToGraymap(ipFilNam, &graymap, &row, &col, &maxVal, &type);

    gray *histStch = allocMatMem(row, col, sizeof (gray));
    stretchHist(histStch, graymap, row, col);

    char histStchOpFilNam[MAX_FIL_NAM_SIZ];
    mkOpName(histStchOpFilNam, "HistStch", ipFilNam, sizeof (histStchOpFilNam));
    graymapToPgm(histStchOpFilNam, histStch, row, col, maxVal, type);
    free(graymap);
    free(histStch);
}

void doHistEq(const char* ipFilNam){
    gray *graymap;
    size_t row, col, maxVal;
    PGMType type;

    pgmToGraymap(ipFilNam, &graymap, &row, &col, &maxVal, &type);

    gray *histEq = allocMatMem(row, col, sizeof (gray));
    eqHist(histEq, graymap, row, col);

    char histEqOpFilNam[MAX_FIL_NAM_SIZ];
    mkOpName(histEqOpFilNam, "HistEq", ipFilNam, sizeof (histEqOpFilNam));
    graymapToPgm(histEqOpFilNam, histEq, row, col, maxVal, type);
    free(graymap);
    free(histEq);
}

void doAll(const char *ipFilNam, size_t n){
    doBinConv(ipFilNam, n);
    doMedianFilter(ipFilNam, n);
    doHistStch(ipFilNam);
    doHistEq(ipFilNam);
}
