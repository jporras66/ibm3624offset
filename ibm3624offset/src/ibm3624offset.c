#include <stdio.h>
#include <string.h>
#include "block.h"
#include "ibm3624.h"
#include "validation.h"
#include "util.h"
//
int ibm3624Offset	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvaldat,
	 	 	 	 	 unsigned char 		 *offset,
	 	 	 	 	 char 				 *errstatus)
{
	int k=0;
   	memset( errstatus ,'\0', ERRSTABLK + 1 );
/*
 * PIN Validation
 *
 * be careful : pinLength returned by ValidatePin Function,  DOES NOT count (\0 final character)
 *
 */
	int	pinLength = validatePin ( ipin , errstatus );
	if ( pinLength == -1 ) return -1 ;
//
// Update pinLength, as needed for naturalpin Function
//
	pinLength++;
//
	unsigned char natPin [ pinLength ] ;
    memset( natPin, '\0' , pinLength );
    memset( offset, '\0' , pinLength );
//
    k = naturalpin ( ipvk, pinLength, idectable , ipinvaldat, natPin, errstatus);
    if ( k == -1) return -1 ;
//
//
// calculate  OFFSET = (NATURAL PIN - CUSTOMER PIN) mod 10
//
// be careful : pinLength counts full length (\0 final character included), then loops until (ipinlength -1)
//
    for (k=0; k<pinLength-1; k++){
       	int i1nat  = getHexValue ( *(natPin+k) );
       	int i2pin  = getHexValue ( *(ipin+k) );
       	*(offset+k)= getUChar ( (10 - i1nat + i2pin) % 10 ) ;
    }
#ifdef TRACE
    printf ("ibm3624Offset.naturalpin %s \n",  natPin );
    printf ("ibm3624Offset.pin        %s \n",  ipin );
    printf ("ibm3624Offset.offset     %s \n",  offset );
#endif
//
	return 0 ;
}
