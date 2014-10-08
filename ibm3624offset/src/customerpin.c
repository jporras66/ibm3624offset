#include <stdio.h>
#include <string.h>
#include "block.h"
#include "ibm3624.h"
#include "validation.h"
#include "util.h"
#include "cypher.h"
//


int customerPin	(unsigned const char *ipvk,
	 	 	 	 const int 			 ipinlength,
	 	 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvaldat,
				 unsigned char 		 *ioffset,
				 unsigned char 		 *opin,
				 char 				 *errstatus)
{
    unsigned char natPin [ ipinlength ] ;
    memset( natPin, '\0' , ipinlength );
    memset( opin  , '\0' , ipinlength );
   	memset( errstatus ,'\0', ERRSTABLK + 1 );
//
    int k = naturalpin ( ipvk, ipinlength, idectable , ipinvaldat, natPin, errstatus);
    if ( k == -1) return -1 ;
//
// calculate CUSTOMER PIN = (NATURAL PIN + OFFSET) mod 10
//
// be careful : pinLength counts full length (\0 final character included), then loops until (ipinlength -1)
//
    for (k=0; k<ipinlength-1; k++){
    	int i1nat = getHexValue ( *(natPin+k) );
    	int i2off = getHexValue ( *(ioffset+k) );
    	*(opin+k) = getUChar ( (i1nat + i2off) % 10 ) ;
    }
#ifdef TRACE
    printf ("customerPin.naturalpin %s \n",  natPin );
    printf ("customerPin.offset     %s \n",  ioffset );
    printf ("customerPin.pin        %s \n",  opin );
#endif
//
	return 0 ;
}
