#include <stdio.h>
#include <string.h>
#include "block.h"
#include "ibm3624.h"
#include "validation.h"
#include "util.h"
#include "cypher.h"

//
int naturalpin	(unsigned const char *ipvk,
				 const int 			 ipinlength,
		 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvaldat,
				 unsigned char 		 *onaturalpin,
				 char 				 *errstatus)
{
    int k=0;
   	memset( onaturalpin,'\0', ipinlength );
   	memset( errstatus ,'\0', ERRSTABLK + 1 );
/*
 * PVK, PIN LENGTH, DECIMALIZATION TABLE, PIN DATA VALIDATION block
 *
 */
	int keylength  = validateKey ( ipvk , errstatus ) ;
	if ( keylength == -1 ) return -1 ;

	int declength = validateDecTable ( idectable, errstatus );
	if ( declength == -1 ) return -1 ;
//
	int pinvaldatlength = validatePinValidationData ( ipinvaldat , errstatus );
	if ( pinvaldatlength == -1 ) return -1 ;

	int pinLength = ipinlength - 1;
	boolean isValid = isValidPinLength ( pinLength , errstatus );
	if ( isValid == FALSE ) return -1 ;


//
/*
 * pack input key (ASCII), to half the size of the input (Binary value)
 *
 * Example : '12' a.k.a '3132' ascii (2 bytes) --> '12' binary (1 byte)
 */
	unsigned char pvk[TRIPLEKEY];
	memset( pvk,'\0', TRIPLEKEY );
//
	int pvklength = keylength / 2 ;
	pack ( ipvk, keylength  , pvk );
/*
 * Always store PVK as TRIPLE
 *
 * Example :   	Input Single : 	815F814E8AAC998E
 *  			Saved PVK:		815F814E8AAC998E-815F814E8AAC998E-815F814E8AAC998E
 *
 * Example :   	Input Double : 	815F814E8AAC998E-7DD12ADDA0FAF179
 *  			Saved PVK:		815F814E8AAC998E-7DD12ADDA0FAF179-815F814E8AAC998E
 */
	if ( pvklength != TRIPLEKEY ) fillPvk( pvk, pvklength );
//
//
//  ( 12 last pan's digits padded with 0's on the left )
// 	dataValidation : 	contains Pan data for DES or TDES
//
//	Example :   4041850002769603 --> 0000185000276960
//
    unsigned char pinvalidationdata[BLOCKLEN] ;
    memset( pinvalidationdata, '\0' , BLOCKLEN );
    pack ( ipinvaldat, pinvaldatlength , pinvalidationdata );
//
    unsigned char cypherblk[BLOCKLEN] ;
    memset( cypherblk, '\0' , BLOCKLEN );
//
// TDES with DOUBLE or TRIPLE key length. Other case DES
//
    if ( pvklength != SINGLEKEY ) {
    	Tdes_encrypt ( pvk , pinvalidationdata, cypherblk ) ;
    }else{
    	Des_encrypt ( pvk , pinvalidationdata, cypherblk ) ;
    }
//
// decimalize result
//
    unsigned char decimalized[ BLOCKLEN*2 ] ;
    memset( decimalized, '\0' , BLOCKLEN*2 );
    int index=0;
    for(k = 0; k <BLOCKLEN; k++) {
    	unsigned char upper = (cypherblk[k] & 0xF0) >> 4;
    	unsigned char lower = (cypherblk[k] & 0x0F);
    	int iu = (int) upper ;
    	int il = (int) lower ;
    	decimalized[index] = idectable[ iu ];
    	index++;
    	decimalized[index] = idectable[ il ];
    	index++;
    }
//
    memcpy( onaturalpin, decimalized , pinLength );
//
#ifdef TRACE
    printf ("=============== PACKED DATA ==================== \n");
    for(k = 0; k<TRIPLEKEY; k++) {
    	if ( k==SINGLEKEY || k==DOUBLEKEY ) printf ( "pvk ==== \n");
    		printf ("pvk %#x \n", *(pvk+k) );
    }
    for(k = 0; k <sizeof(pinvalidationdata); k++) {
    	printf ("pinvalidationdata %2d  %#x \n", k , pinvalidationdata[ k ] );
    }
    for(k = 0; k <sizeof(cypherblk); k++) {
    	printf ("cypherblk %2d  %#x \n", k , cypherblk[ k ] );
    }
    printf ("=============== END OF PACKED DATA ============= \n");
    printf ("============= DECIMALIZATION TABLE ============= \n");
    for(k = 0; k <sizeof(decimalized); k++) {
    	printf ("decimalized %2d  %c \n", k , decimalized[ k ] );
    }
    printf ("========= END OF DECIMALIZATION TABLE ========== \n");
    printf ("idectable   %s  \n", idectable );
    printf ("onaturalpin %s  \n", onaturalpin );
#endif
//
	return 0 ;
}

void fillPvk ( unsigned char *p, int length ){
	int k=0;
	if (length == SINGLEKEY){
		for(k=0;k<SINGLEKEY;k++){
			*(p+k+SINGLEKEY) = *(p+k);
			*(p+k+DOUBLEKEY) = *(p+k);
		}
	}
	if (length == DOUBLEKEY){
		for(k=0;k<SINGLEKEY;k++){
			*(p+k+DOUBLEKEY) = *(p+k);
		}
	}
}
