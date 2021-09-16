#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imgoper.h"
#include "utils.h"

typedef enum{
    eBinConv = 0,
    eMedFilter,
    eHistStch,
    eHistEq,
    eNbImgOper
}ImgOper;

void printHelpNExit(const char *fileNam){
    printf("\nUsage: %s filename operation option\n\n", fileNam);
    printf("Operations:\n");
    printf("0 n( > 0): n times Convolution With Binomial Filter\n");
    printf("1 n( > 0): n times Median Filtering\n");
    printf("2 : Histogram Stretching\n");
    printf("3 : Histogram Equalization\n");
    printf("4 n( > 0): All of the above(n time Convolution and Median filter)\n");
    exit(0);
}

#ifdef IDE
int main(){
    // doHistEq("Unequalized.pgm");
    doHistEq("tmp648.pgm");
//    doHistEq("boat.pgm");
    return 0;
}
#else
int main(int argc, char **argv){
    if((argc > 4) || (argc < 3)){
        printHelpNExit(argv[0]);
    }
    char ipFilNam[MAX_FIL_NAM_SIZ];
    strncpy(ipFilNam, argv[1], MAX_FIL_NAM_SIZ);
    int oper = atoi(argv[2]);
    int subOper = 1;
    if(argc == 4){
        if( ( subOper = atoi(argv[3]) ) < 1 ){
            printHelpNExit(argv[0]);
        }
    }
    switch (oper) {
    case eBinConv:
        doBinConv(ipFilNam, subOper);
        break;
    case eMedFilter:
        doMedianFilter(ipFilNam, subOper);
        break;
    case eHistStch:
        doHistStch(ipFilNam);
        break;
    case eHistEq:
        doHistEq(ipFilNam);
        break;
    case eNbImgOper:
        doAll(ipFilNam, subOper);
        break;
    default:
        printHelpNExit(argv[0]);
        break;
    }
    return 0;
}
#endif
