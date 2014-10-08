#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "ibm3624.h"

int main(int argc, char *argv[]) {

	unsigned char pvk[] 		= "815F814E8AAC998E7DD12ADDA0FAF179";
	unsigned char dectable[] 	= "0123456789012345";
	//							   0123456789ABCDEF
	unsigned char pin[]			= "108800";
	char errstatus[ ERRSTABLK + 1 ];
//
	int k=0;
/*
int naturalpin 	(unsigned const char *ipvk,
				 const int 			 ipinlength,
		 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvalidationdata,
				 unsigned char 		 *onaturalpin,
				 char 				 *errstatus);
*/
	unsigned char pinvaldat[ ] ="1850002769676960";
	unsigned char natPin[sizeof(pin)];
	unsigned char result[] = "180216";
	memset( natPin,'\0', sizeof(natPin) );
	k = naturalpin ( pvk, sizeof(natPin), dectable , pinvaldat , natPin, errstatus);
	if ( k==0 ){
		if ( strcmp( (const char *) natPin, (const char *)  result) == 0 ){
			printf ("main.naturalpin.1 OK %s %s \n", natPin, result );
		}else{
			printf ("main.naturalpin.1 KO %s %s \n",  natPin, result );
		}
	}
	else{
		printf ("main.naturalpin.1 KO %2d %s \n" , k , errstatus );
	}
//
	int length = sizeof(pin) + 1 ;
	unsigned char natPin2[ length ]; //invalid length
	k = naturalpin ( pvk, length , dectable , pinvaldat , natPin2, errstatus);
	if ( k==0 ){
		printf ("main.naturalpin.2 KO length %2d %s %s \n", length , natPin2, result );
	}
	else{
		printf ("main.naturalpin.2 OK length %2d %s \n" , length , errstatus );
	}
	return 0 ;
}
