#include <stdio.h>
#include <string.h>
#include "util.h"

void pack ( unsigned const char *blkIN , int length, unsigned char *blkOUT ){

	int index = 0 , i = 0;
	unsigned char nibble = 0x00, dummy = 0x00 ;

    for(i = 0; i < length; i++) {
    	dummy =  getHexValue( *(blkIN+i) ) ;
    	index = ( i / 2) ;
		if ( (i % 2)  == 0) { 		// i is even
			nibble = ( dummy << 4 ) & 0xF0 ;
			blkOUT[index] = nibble ;
		}else{ 						// i is odd
			nibble = (  ( dummy ) & 0x0F );
			blkOUT[index] = ( blkOUT[index] | nibble ) ;
		}
    }
#ifdef TRACE
	int size=0;
   	for(i = 0; i < size; i++) {
   		printf ("blkOUT %x \n", *(blkOUT+i) );
   	}
#endif
}
