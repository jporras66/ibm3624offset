#include <stdio.h>
#include <string.h>
#include "util.h"

/*
 * Return the corresponding ASCII character to his hex value.
 */
unsigned char getUChar( unsigned const char  hexChar){
	if ( hexChar >= 0x00 && hexChar <= 0x09 ) return hexChar + 0x30 ;
	if ( hexChar >= 0x0A && hexChar <= 0x0F ) return hexChar + 0x37 ;
	return 0x00 ;
}

/*
 * Return the corresponding hex value from an Alphanumerical ASCII character  ( 0 to 9 , A to F,  a to f )
 */
unsigned char getHexValue( unsigned const char  hexChar){
	if ( hexChar >= 0x30 && hexChar <= 0x39 ) {
		return hexChar - 0x30 ;
	}
	if ( hexChar >= 0x41 && hexChar <= 0x46 ) {
		return hexChar - 0x37 ;
	}
	if ( hexChar >= 0x61 && hexChar <= 0x66 ) {
		return hexChar - 0x57 ;
	}
	return 0x00 ;
}
/*
 * Validate is hexadecimal  ( 0 to 9 , A to F,  a to f )
 */
boolean isHex( unsigned const char  *hexChar, int size ){
	int k=0;
	for(k=0;k<size;k++){
		unsigned const char c = *(hexChar+k) ;
		//printf("isHex %d %#x  \n" , k , c ) ;
		if ( ! (
					( c >= 0x30 && c <= 0x39 ) ||
					( c >= 0x41 && c <= 0x46 ) ||
					( c >= 0x61 && c <= 0x66 )
			   )   )  {
			return FALSE;
		}
	}
	return TRUE;
}
/*
 * Validate is Decimal  ( 0 to 9 )
 */
boolean isDec( unsigned const char  *hexChar, int size ){
	int k=0;
	for(k=0;k<size;k++){
		unsigned const char c = *(hexChar+k) ;
		//printf("isDec %d %#x  \n" , k , c ) ;
		if ( !  ( c >= 0x30 && c <= 0x39 )  )  {
			return FALSE;
		}
	}
	return TRUE;
}

