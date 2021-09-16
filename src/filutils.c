#include <stdio.h>
#include <stdlib.h>
#include "filutils.h"

int fileGetC(FILE *fileH){
    int ich = getc( fileH );
    assert(ich != EOF );
    return ich;
}

// get char skipping comments
char pm_getc(FILE* file){
    int ich;
    char ch;

    ich = fileGetC(file);
    ch = (char) ich;

    if ( ch == '#' ){
        do{
            ich = fileGetC(file);
            ch = (char) ich;
        } while ( ch != '\n' && ch != '\r' ); // skip the comment and yield newline char
    }
    return ch;
}

// p1 -> p4
bit pm_getbit(FILE* file){
    char ch;

    do {
        ch = pm_getc( file );
    } while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ); // trying to find 1st non-whitespace char

    switch (ch) {
    case '0':
        return 0;
    case '1':
        return 1;
    default:
        assert(0);
    }
}


unsigned char pm_getrawbyte(FILE* file){
    return  (unsigned char) fileGetC(file);
}

int pm_getint( FILE* file){
    char ch;
    do {
        ch = pm_getc( file );
    } while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' );// get 1st non-whitespace char

    if ( ch < '0' || ch > '9' ){ // check if it's valid ascii dec
        assert(0);
    }

    int i = 0;
    do {
        i = i * 10 + ch - '0';
        ch = pm_getc( file );
    } while ( ch >= '0' && ch <= '9' ); // until next whitespace convert chars in ascii decimal to numbers

    return i;
}
