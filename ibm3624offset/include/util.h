#ifndef UTIL_H
#define UTIL_H

#ifndef __BOOLEAN
#define __BOOLEAN
	typedef enum {FALSE  = 0, TRUE = 1 } boolean;
#endif /* __BOOLEAN */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
 * pack  : a char ascii array (only hexadecimal digits) to half size (Binary value)
 *
 * Example : '12'ascii a.k.a  X'3132' (2 bytes) --> X'12' binary (1 byte)
 *
 * RETURN:
 * 		void
 * INPUT
 * 		blkIN 		pointer to input array block to be packed
 * 		size		size of input array
 * OUTPUT
 * 		blkOUT		pointer to output block array (packed)
 *
 */
void pack 		( unsigned const char *blkIN , int size , unsigned char *blkOUT );

/*
 * unpack  : a char binary array (only hexadecimal digits) to ascii format (Binary value)
 *
 * Example : X'12' binary (1 byte) --> X'3132' ascii (2 bytes)
 *
 * RETURN:
 * 		void
 * INPUT
 * 		blkIN 		pointer to input array block
 * 		size		size of input array
 * OUTPUT
 * 		blkOUT		pointer to output block array (packed)
 *
 */
void unpack 	( unsigned const char *blkIN , int size,  unsigned char *blkOUT );

/*
 * getUchar  : Convert an hexadecimal char (0x00 to 0xF) (1 byte) to is corresponding ascii format
 *
 * Example : 0x00 (1 byte) --> X'30' ascii (1 byte)
 *
 * RETURN:
 * 		ascii value
 * INPUT
 * 		hexChar		hexadecimal char (0x00 to 0xF)
 *
 */
unsigned char getUChar	( unsigned const char  hexChar);

/*
 * getHexValue  : Convert an ascii char (1 byte) (only hexadecimal characters) to is corresponding
 * 				  hexadecimal format (1 byte)
 *
 * Example : X'30' ascii (1 byte) --> 0x00 (1 byte)
 *
 * RETURN:
 * 		hexadecimal value
 * INPUT
 * 		hexChar		hexadecimal char (0x00 to 0xF)
 *
 */
unsigned char getHexValue	( unsigned const char  hexChar);

/*
 * Validate is hexadecimal  ( 0 to 9 , A to F,  a to f )
 */
boolean isHex ( unsigned const char  *hexChar, int size ) ;

/*
 * Validate is Decimal  ( 0 to 9 )
 */
boolean isDec ( unsigned const char  *hexChar, int size ) ;
//
/*
 * replace one character by another
 */
void replacechar(char *buff, int num, char oldc, char newc) ;

#ifdef __cplusplus
}
#endif

#endif  /* ! UTIL_H */
