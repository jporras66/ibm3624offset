#include <stdio.h>
#include <string.h>
#include "util.h"

void unpack ( unsigned const char *blkIN , int length, unsigned char *blkOUT ){

	int index = 0 , i = 0;
	unsigned char upper = 0x00 , lower = 0x00;

    for(i = 0; i < length; i++) {

		upper = ( blkIN[i] & 0xF0  ) >> 4 ;
		lower = ( blkIN[i] & 0x0F );

		blkOUT[index] = getUChar (upper) ;
		index++;

		blkOUT[index] = getUChar (lower) ;
		index++;
    }
#ifdef TRACE
	int size=0;
	for(i = 0; i < size; i++) {
		printf ("blkOUT %x \n", blkOUT[i] );
	}
#endif
}
