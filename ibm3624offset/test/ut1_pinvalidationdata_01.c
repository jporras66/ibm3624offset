#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "ibm3624.h"

int main(int argc, char *argv[]) {

 	unsigned char pan[] 		= "4041850002769603" ;
//	unsigned char pvk[] 		= "815F814E8AAC998E7DD12ADDA0FAF179";
//	unsigned char dectable[] 	= "0123456789012345";
	//							   0123456789ABCDEF
//	unsigned char pin[]			= "108800";
//	unsigned char offset[] 		= "881655";
	unsigned const char padchar	= 'F';
	char errstatus[ ERRSTABLK + 1 ];
//
/*
int getPinValidationData	(unsigned const char *ipan,
						 	 unsigned const int	 inumdigits,
						 	 unsigned const char ipaddigit,
						 	 boolean			 pad2rigth,
						 	 unsigned char 		 *opinvaldat,
						 	 char 				 *errstatus)
 */
	unsigned char pinvaldat[ MAXDATVAL + 1 ];
	boolean pad2rigth = TRUE;
	unsigned char result[] = "185000276960FFFF";
	int numdigits = 12 ;
	int k = getPinValidationData ( pan, numdigits, padchar, pad2rigth , pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp( (const char *) pinvaldat, (const char *) result) == 0 ){
			printf ("main.getPinValidationData.1 OK numdigits %2d - %s %s \n",numdigits,  pinvaldat, result );
		}else{
			printf ("main.getPinValidationData.1 KO numdigits %2d - %s %s \n",numdigits,  pinvaldat, result );
		}
	}
	else{
		printf ("main.getPinValidationData.1 KO %2d %s \n" , k , errstatus );
	}
//
	unsigned char result2[] = "404185000276960F";
	numdigits = 15 ;
	k = getPinValidationData ( pan, numdigits, padchar, pad2rigth , pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp( (const char *) pinvaldat , (const char *) result2) == 0 ){
			printf ("main.getPinValidationData.2 OK numdigits %2d - %s %s \n",numdigits,  pinvaldat, result2 );
		}else{
			printf ("main.getPinValidationData.2 KO numdigits %2d - %s %s \n",numdigits,  pinvaldat, result2 );
		}
	}
	else{
		printf ("main.getPinValidationData.2 KO %2d %s \n" , k , errstatus );
	}
//
	unsigned char result3[] = "FFFF185000276960";
	pad2rigth = FALSE;
	numdigits = 12;
	k = getPinValidationData ( pan, numdigits, padchar, pad2rigth , pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp((const char *) pinvaldat, (const char *) result3) == 0 ){
			printf ("main.getPinValidationData.3 OK numdigits %2d - %s %s \n",numdigits,  pinvaldat, result3 );
		}else{
			printf ("main.getPinValidationData.3 KO numdigits %2d - %s %s \n",numdigits,  pinvaldat, result3 );
		}
	}
	else{
		printf ("main.getPinValidationData.3 KO %2d %s \n" , k , errstatus );
	}
//
	unsigned char result4[] = "F404185000276960";
	pad2rigth = FALSE;
	numdigits = 15;
	k = getPinValidationData ( pan, numdigits, padchar, pad2rigth , pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp((const char *) pinvaldat, (const char *) result4) == 0 ){
			printf ("main.getPinValidationData.4 OK numdigits %2d - %s %s \n",numdigits,  pinvaldat, result4 );
		}else{
			printf ("main.getPinValidationData.4 KO numdigits %2d - %s %s \n",numdigits,  pinvaldat, result4 );
		}
	}
	else{
		printf ("main.getPinValidationData.4 KO %2d %s \n" , k , errstatus );
	}
//
	numdigits = 10;
	k = getPinValidationData ( pan, numdigits, padchar, pad2rigth , pinvaldat, errstatus);
	if ( k==0 ){
		printf ("main.getPinValidationData.5 KO numdigits %2d - %s \n" ,numdigits,  pinvaldat );
	}
	else{
		printf ("main.getPinValidationData.5 OK numdigits %2d - %s \n" , numdigits , errstatus );
	}
//
	return 0 ;
}
