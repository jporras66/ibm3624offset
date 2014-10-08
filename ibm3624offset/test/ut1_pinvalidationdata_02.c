#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "ibm3624.h"

int main(int argc, char *argv[]) {

 	unsigned char pan[] 		= "4041850002769603" ;
	char errstatus[ ERRSTABLK + 1 ];
//
/*
int pinValidationData	(unsigned const char *ipan,
						 const int			 iposition,
						 unsigned char       *opinvaldat,
						 char 				 *errstatus);
 */
	int k=0;
	unsigned char pinvaldat[ MAXDATVAL + 1 ];
	unsigned char result[] = "1769605000276960";
	int pos = 2 ;
	k = pinValidationData ( pan, pos, pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp( (const char *) pinvaldat, (const char *) result) == 0 ){
			printf ("main.pinValidationData.1 OK position %2d - %s %s \n", pos, pinvaldat, result );
		}else{
			printf ("main.pinValidationData.1 KO position %2d - %s %s \n", pos, pinvaldat, result );
		}
	}
	else{
		printf ("main.pinValidationData.1 KO %2d %s \n", k , errstatus );
	}
//
	unsigned char result2[] = "1850002769676960";
	pos = 12 ;
	k = pinValidationData ( pan, pos, pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp((const char *) pinvaldat, (const char *) result2) == 0 ){
			printf ("main.pinValidationData.2 OK position %2d - %s %s \n", pos, pinvaldat, result2 );
		}else{
			printf ("main.pinValidationData.2 KO position %2d - %s %s \n", pos, pinvaldat, result2 );
		}
	}
	else{
		printf ("main.pinValidationData.2 KO %2d %s \n", k , errstatus );
	}

	//
	unsigned char result3[] = "7696085000276960";
	pos = 1 ;
	k = pinValidationData ( pan, pos, pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp((const char *) pinvaldat, (const char *) result3) == 0 ){
			printf ("main.pinValidationData.3 OK position %2d - %s %s \n", pos, pinvaldat, result3 );
		}else{
			printf ("main.pinValidationData.3 KO position %2d - %s %s \n", pos, pinvaldat, result3 );
		}
	}
	else{
		printf ("main.pinValidationData.3 KO %2d %s \n", k , errstatus );
	}
//
	pos = 13 ;
	k = pinValidationData ( pan, pos, pinvaldat, errstatus);
	if ( k==0 ){
		if ( strcmp((const char *) pinvaldat, (const char *) result3) == 0 ){
			printf ("main.pinValidationData.4 KO position %2d - %s %s \n", pos, pinvaldat, result3 );
		}else{
			printf ("main.pinValidationData.4 KO position %2d - %s %s \n", pos, pinvaldat, result3 );
		}
	}
	else{
		printf ("main.pinValidationData.4 OK position %2d - %s \n", pos , errstatus );
	}
	return 0 ;
}
