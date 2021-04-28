#ifndef COMMON_H
#define COMMON_H


#include <stdint.h> //Int types
#include <limits.h> //Int constants
#include <stdbool.h> //Duh
#include <stdlib.h> //NULL etc
#include <string.h> //memcpy etc


#define IDIV(n, d) ((n) + (d)/2) / (d) /*Minimises overflow, handles signed values*/
//#define IDIV(n, d) ((n) + (d)/2 + 1) / (d)
#define	UDIV(n, d) ((n)<<1 + (d)) / ((d)<<1) /*Minimises error, only suitable for positives*/

typedef unsigned int uint; //Native databus size

static inline int16_t wrap180(int angle) {
	int shifted = angle + 180;
	shifted += 360*(abs(angle)/360 + 1);
	shifted %= 360;
	int wrapped = shifted - 180;
	return (int16_t)wrapped;
}



#endif //COMMON_H


