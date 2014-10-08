#include <stdio.h>
#include <string.h>
#include "block.h"
#include "ibm3624.h"
#include "validation.h"

boolean verifyPin	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvaldat,
	 	 	 	 	 unsigned const char *ioffset,
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
	unsigned char cusOffset[ pinLength];
	memset( cusOffset,'\0', pinLength  );
	k = ibm3624Offset ( ipvk, ipin , idectable , ipinvaldat, cusOffset, errstatus);
	if ( pinLength == -1 ) return -1 ;

	for (k=0; k<pinLength-1;k++){
		if ( *(ioffset+k) != cusOffset[k] ){
			return FALSE ;
		}
	}
	return TRUE;
}
