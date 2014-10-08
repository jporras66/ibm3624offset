#include <stdio.h>
#include <string.h>
#include "block.h"
#include "ibm3624.h"
#include "validation.h"

int pinValidationData	(unsigned const char *ipan,
						 const int			 iposition,
						 unsigned char       *opinvaldat,
						 char 				 *errstatus){
//    int k=0;
	memset( opinvaldat,'\0', MAXDATVAL + 1 );
   	memset( errstatus ,'\0', ERRSTABLK + 1 );
/*
 * accountnumber	The 12 right-most digits of the account number, excluding check digit
 *
 */
	unsigned char accountnumber[13] ;
	memset(accountnumber, '\0', 13 );
	unsigned char last5digits[6] ;
	memset(last5digits, '\0', 6 );
//
/*
  PAN validation & numdigits
*/
	int panlength  = validatePan ( ipan , errstatus );
	if ( panlength == -1 ) return -1 ;

	if ( iposition - 1 < 0 || iposition -1  > 11 ){
		strcpy(errstatus, "Invalid position to insert last 5 digits of account number - must be between 1 to 12 !!");
		return -1 ;
	}
//
	strncpy( (char *) accountnumber, (const char *) (ipan + panlength - 12 - 1), 12 ); 			// copy to accountnumber from PAN 12 last digits without check digit
	accountnumber[12]='\0';
//
//	int index =  panlength - 5 - 1 ;
	strncpy( (char *) last5digits, (const char *) (ipan + panlength - 5 - 1), 5 );				// copy to last5digits from  PAN 5  last digits without check digit
	last5digits[5]='\0';
//
	strncpy( (char *) opinvaldat, (const char *) accountnumber, iposition - 1 );				// copy from accountnumber first iposition characters
	strcat ( (char *) opinvaldat, (const char *) last5digits);									// add 5 last digits
	strncat( (char *) opinvaldat, (const char *) (accountnumber+iposition), 12 - iposition );	// add PAN last position (to complete 16 charactes)
	opinvaldat[ MAXDATVAL + 1 ] = '\0';

#ifdef TRACE
	printf("pinValidationData.pan           %s  \n", ipan );
	printf("pinValidationData.accountnumber %s  \n", accountnumber );
	printf("pinValidationData.last5         %s  \n", last5digits );
	printf("pinValidationData.iposition     %d  \n", iposition );
	printf("pinValidationData.opinvaldat    %s  \n", opinvaldat );
#endif
	return 0 ;
}

int getPinValidationData	(unsigned const char *ipan,
						 	 unsigned const int	 inumdigits,
						 	 unsigned const char ipaddigit,
						 	 boolean			 ipad2rigth,
						 	 unsigned char       *opinvaldat,
						 	 char 				 *errstatus)
{
    int k=0;
   	memset( opinvaldat,'\0', MAXDATVAL + 1 );
   	memset( errstatus ,'\0', ERRSTABLK + 1 );
/*
 * PAN validation & numdigits
 */
	int panlength  = validatePan ( ipan , errstatus );
	if ( panlength == -1 ) return -1 ;

	if ( inumdigits <12 || inumdigits > 15 ){
		strcpy(errstatus, "Invalid number of digits to be taked from PAN - must be between 12 to 15 !!");
		return -1 ;
	}

	if ( ipaddigit != '0' &&  ipaddigit != 'F' ){
		strcpy(errstatus, "Invalid PAD diggit - must be 0 or F !!");
		return -1 ;
	}

/*
 * Copy to pandigits from PAN inumdigits last digits without check digit
 *
 */
	unsigned char pandigits[ inumdigits + 1 ];
	memset(pandigits, '\0', inumdigits + 1);
	strncpy( (char *) pandigits, (const char *) (ipan + panlength - inumdigits - 1), inumdigits );
	pandigits[inumdigits] = '\0';
/*
 * Build pinvalidationdata block
 *
 */
	if ( ipad2rigth == TRUE ){
		for (k=0; k<inumdigits;k++){
			*(opinvaldat+k) = pandigits[k];			// move pan digits
		}
		for (k=inumdigits; k<BLOCKLEN*2;k++){
			*(opinvaldat+k) = ipaddigit;			// move PAD character
		}
	}else{
		for (k=0; k<BLOCKLEN*2-inumdigits;k++){
			*(opinvaldat+k) = ipaddigit;			// move PAD character
		}
		int index = k ;
		for (k=0; k<inumdigits ;k++){
			*(opinvaldat+index) = pandigits[k];		// move pan digits
			index++;
		}
		opinvaldat[ MAXDATVAL + 1 ] = '\0';
	}
#ifdef TRACE
	printf("getpinValidationData.pan        %s  \n", ipan );
	printf("getpinValidationData.pandigits  %s  \n", pandigits );
	printf("getpinValidationData.inumdigits %2d \n", inumdigits );
	printf("getpinValidationData.ipaddigit  %c  \n", ipaddigit );
	printf("getpinValidationData.ipad2rigth %d  \n", ipad2rigth );
	printf("getpinValidationData.opinvaldat %s  \n", opinvaldat );
#endif

	return 0 ;
}


