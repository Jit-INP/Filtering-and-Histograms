#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <assert.h>

//#define FILTER_SIZ 5
#define MAX_FIL_NAM_SIZ 64

typedef unsigned char pix;
typedef unsigned short pixprod;
typedef unsigned int mfiltersum;

typedef pix bit;
typedef pix gray;
typedef pix color;


#define NULL_PTR_CHK(x) assert(x != NULL)
#define SAME_PTR_CHK(x, y) assert(x != y)
#define ABOVE_ZERO_CHK(x) assert(x > 0)

#define MAX_PIX_VAL ( (pixprod) ( pow( 2, 8 * sizeof(pix) ) - 1 ) )

#endif // UTILS_H
