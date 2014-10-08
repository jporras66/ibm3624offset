#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "ibm3624.h"

int main(int argc, char *argv[]) {


 	unsigned char pan[] 		= "4041850002769603" ;
	unsigned char pvk[] 		= "815F814E8AAC998E7DD12ADDA0FAF179";
	unsigned char dectable[] 	= "0123456789012345";
	//							   0123456789ABCDEF
	unsigned char pin[]			= "108800";
	unsigned char offset[] 		= "881655";
	char errstatus[ ERRSTABLK ];
//
/*
int pinValidationData	(unsigned const char *ipan,
						 const int			 iposition,
						 unsigned char       *opinvaldat,
						 char 				 *errstatus)
 */
	unsigned char pinvaldat[ MAXDATVAL + 1 ];
	unsigned char result[] = "1850002769676960";
	int k = pinValidationData ( pan, 12, pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp( (const char *) pinvaldat, (const char *) result) == 0 ){
			printf ("main.pinValidationData.1 OK %s %s \n", pinvaldat, result );
		}else{
			printf ("main.pinValidationData.1 KO %s %s \n", pinvaldat, result );
		}
	}
	else{
		printf ("main.pinValidationData.1 KO %d %s \n" , k , errstatus );
		return k;
	}

//
/*
int naturalpin 	(unsigned const char *ipvk,
				 const int 			 ipinlength,
		 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvalidationdata,
				 unsigned char 		 *onaturalpin,
				 char 				 *errstatus);
*/
	unsigned char natPin[sizeof(pin)];
	memset( natPin,'\0', sizeof(natPin) );
	k = naturalpin ( pvk, sizeof(natPin), dectable , pinvaldat , natPin, errstatus);
	if ( k==0 ){
		printf ("main.naturalpin          OK %s \n" , natPin );
	}
	else{
		printf ("main.naturalpin          KO %d %s %s \n" , k , natPin, errstatus);
		return k;
	}
//
/*
int customerPin	(unsigned const char *ipvk,
	 	 	 	 const int 			 ipinlength,
	 	 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvalidationdata,
				 unsigned char 		 *ioffset,
				 unsigned char 		 *opin,
				 char 				 *errstatus)
 */
	unsigned char cusPin[sizeof(pin)];
	memset( cusPin,'\0', sizeof(natPin) );
	k = customerPin ( pvk, sizeof(cusPin), dectable , pinvaldat, offset, cusPin, errstatus);
	if ( k==0 ){
		printf ("main.customerPin         OK %s \n" , cusPin);
	}
	else{
		printf ("main.customerPin         KO %d %s %s \n" , k , cusPin, errstatus );
		return k;
	}
//
/*
int ibm3624Offset	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvalidationdata,
	 	 	 	 	 unsigned char 		 *offset,
	 	 	 	 	 char 				 *errstatus)
{
 */
	unsigned char cusOffset[sizeof(pin)];
	memset( cusOffset,'\0', sizeof(cusOffset) );
	k = ibm3624Offset ( pvk, cusPin , dectable , pinvaldat, cusOffset, errstatus);
	if ( k==0 ){
		printf ("main.ibm3624Offset       OK %s \n" ,  cusOffset );
	}
	else{
		printf ("main.ibm3624Offset       KO %d %s %s \n" , k , cusOffset, errstatus );
		return k;
	}
//
/*
boolean verifyPin	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvaldat,
	 	 	 	 	 unsigned const char *ioffset,
	 	 	 	 	 char 				 *errstatus)
 */
	boolean b = verifyPin ( pvk, cusPin , dectable , pinvaldat, cusOffset, errstatus);
	if (b == TRUE ){
		printf ("main.verifyPin           OK pin %s offset %s \n" , cusPin, cusOffset );
	}
	else{
		printf ("main.verifyPin           KO %d pin %s \n" , k , errstatus );
		return k;
	}
//
/*
 * int pinValidationData (unsigned const char *ipan,
						 const int			 iposition,
						 unsigned char       *opinvaldat,
						 char 				 *errstatus)
 */
	k = pinValidationData ( pan, 12, pinvaldat, errstatus );
	if ( k==0 ){
		printf ("main.pinValidationData   OK %s \n" ,  pinvaldat );
	}
	else{
		printf ("main.pinValidationData   KO %d %s %s \n" , k , pinvaldat, errstatus );
		return k;
	}
	return 0 ;
}
