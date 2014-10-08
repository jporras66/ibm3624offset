#include <stdio.h>
#include <string.h>
#include "block.h"
#include "validation.h"
#include "util.h"
//
int validateKey ( unsigned const char *ipvk , char *errstatus ){

	unsigned const char *p = ipvk ;
	int length=0;
	while ( *(p+length) != '\0' ){
		length++;
	}
	if ( length != SINGLEKEY*2 && length != DOUBLEKEY*2 && length != TRIPLEKEY*2 )  {  //simple,double or triple length key
		strcpy(errstatus, "Invalid PVK data - must containt 16, 32 or 48 hexadecimal characters !!");
		return -1 ;
	}

	boolean isValid = isHex ( ipvk, length ) ;
	if ( isValid == FALSE) {
		strcpy(errstatus, "Invalid PVK data - must containt 16, 32 or 48 hexadecimal characters !!");
		return -1 ;
	}

	return length  ;
}

int validateDecTable ( unsigned const char *idectable , char *errstatus ){

	unsigned const char *p = idectable ;
	int length=0;
	while ( *(p+length) != '\0' ){
		length++;
	}
	if ( length != MAXDECTAB ){
		strcpy(errstatus, "Invalid Decimalization Table - must containt 16 decimal characters !!");
		return -1 ;
	}

	boolean isValid = isDec ( idectable, length ) ;
	if (  isValid == FALSE ) {
		strcpy(errstatus, "Invalid Decimalization Table - must containt 16 decimal characters !!");
		return -1 ;
	}

	return length  ;
}

int validatePin ( unsigned const char *ipin , char *errstatus ){

	unsigned const char *p = ipin ;
	int length=0;
	while ( *(p+length) != '\0' ){
		length++;
	}

	boolean isValid = isValidPinLength ( length, errstatus );
	if (  isValid == FALSE ) {
		return -1;
	}
//
	isValid = isDec ( ipin, length ) ;
	if (  isValid == FALSE ) {
		strcpy(errstatus, "Invalid pin - must containt between 4 to 6 decimal digits !!");
		return -1 ;
	}
	return length  ;
}

boolean isValidPinLength ( const int ipinlength , char *errstatus ){

	if ( ipinlength < MINPINLENGTH || ipinlength > MAXPINLENGTH )  {
		strcpy(errstatus, "Invalid pin - must containt between 4 to 6 decimal digits !!");
		return FALSE ;
	}
	return TRUE  ;
}

int validatePan ( unsigned const char *pan , char *errstatus ){

	unsigned const char *p = pan ;
	int length=0;
	while ( *(p+length) != '\0' ){
		length++;
	}

	if ( length < 13 || length > 19  )  {
		strcpy(errstatus, "Invalid pan - must containt between 13 to 19 decimal digits !!");
		return -1 ;
	}
	boolean isValid = isDec ( pan, length ) ;
	if (  isValid == FALSE ) {
		strcpy(errstatus, "Invalid data validation - must containt between 13 to 19 decimal digits !!");
		return -1 ;
	}
	return length  ;
}

int validatePinValidationData ( unsigned const char *ipinvalidationdata , char *errstatus ){

	unsigned const char *p = ipinvalidationdata ;
	int length=0;
	while ( *(p+length) != '\0' ){
		length++;
	}

	if ( length != MAXDATVAL  )  {
		strcpy(errstatus, "Invalid pinValidationData - must containt 16 hexadecmial digits !!");
		return -1 ;
	}
	boolean isValid = isHex ( ipinvalidationdata, length ) ;
	if (  isValid == FALSE ) {
		strcpy(errstatus, "Invalid pinValidationData - must containt 16 hexadecmial digits !!");
		return -1 ;
	}
	return length  ;
}
