#ifndef IBM3624_H
#define IBM3624_H


#ifndef __BOOLEAN
#define __BOOLEAN
	typedef enum {FALSE  = 0, TRUE = 1 } boolean;
#endif /* __BOOLEAN */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
//
/*
 * pinValidationData  : Build a pinvalidationdata block (8 bytes length)
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipan 		pointer to PAN number
 * 		iposition	where las 5 digit of account number going to be inserted
 * OUTPUT
 * 		opinvaldat	pointer to pinvalidationdata block returned
 * 		errstatus	error message (if any)
 *
 */
int pinValidationData	(unsigned const char *ipan,
						 const int			 iposition,
						 unsigned char       *opinvaldat,
						 char 				 *errstatus);
//
/*
 * naturalpin  : compute natural PIN from pinvalidationdata block
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipvk 		pointer to PVK key
 * 		ipinlength	pin length
 * 		idectable	decimalization table
 * 		ipinvaldat	pointer to pinvalidationdata block
 * OUTPUT
 * 		onaturalpin	natural PIN ( ipinlength characters
 * 		errstatus	error message (if any)
 *
 */
int naturalpin 	(unsigned const char *ipvk,
				 const int 			 ipinlength,
		 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvaldat,
				 unsigned char 		 *onaturalpin,
				 char 				 *errstatus);
//
/*
 * customerPin  : compute PIN (customer PIN) for a giving offset
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipvk 		pointer to PVK key
 * 		ipinlength	pin length
 * 		idectable	pointer decimalization table
 * 		ipinvaldat	pointer to pinvalidationdata block
 * 		ioffset		pointer to offset
 * OUTPUT
 * 		opin		PIN ( ipinlength characters )
 * 		errstatus	error message (if any)
 *
 */
int customerPin	(unsigned const char *ipvk,
	 	 	 	 const int 			 ipinlength,
	 	 	 	 unsigned const char *idectable,
				 unsigned const char *ipinvaldat,
				 unsigned char 		 *ioffset,
				 unsigned char 		 *opin,
				 char 				 *errstatus);
//
/*
 * ibm3624Offset  : compute offset for a giving pin (customer PIN)
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipvk 		pointer to PVK key
 * 		ipin		pointer to pin (customer PIN)
 * 		idectable	pointer decimalization table
 * 		ipinvaldat	pointer to pinvalidationdata block
 * OUTPUT
 * 		offset		pointer to offset
 * 		errstatus	error message (if any)
 *
 */
int ibm3624Offset	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvaldat,
	 	 	 	 	 unsigned char 		 *offset,
	 	 	 	 	 char 				 *errstatus);
//
/*
 * verifyPin  :  Verify a PIN against a OFFSET
 *
 * RETURN:
 * 		TRUE
 * 	   	FALSE
 * INPUT
 * 		ipvk 		pointer to PVK key
 * 		ipin		pointer to pin (customer PIN)
 * 		idectable	pointer decimalization table
 * 		ipinvaldat	pointer to pinvalidationdata block
 * 		ioffset		pointer to offset*
 * OUTPUT
 * 		errstatus	error message (if any)
 *
 */
boolean verifyPin	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *ipin,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned const char *ipinvaldat,
	 	 	 	 	 unsigned const char *ioffset,
	 	 	 	 	 char 				 *errstatus);
//
/*
 * getPinValidationData  : Build a pinvalidationdata block (8 bytes length)
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipan 		pointer to PAN number
 * 		inumdigits	number of digits to be taken from PAN ( inumdigits <12 ||inumdigits > 15 )
 * 		ipaddigit	padding digit ('0' or 'F')
 * 		ipad2rigth	TRUE  pad characters to rigth
 * 					FALSE pad characters to left
 * OUTPUT
 * 		opinvaldat	pointer to pinvalidationdata block returned
 * 		errstatus	error message (if any)
 *
 */
int getPinValidationData	(unsigned const char *ipan,
						 	 unsigned const int	 inumdigits,
						 	 unsigned const char ipaddigit,
						 	 boolean			 ipad2rigth,
						 	 unsigned char       *opinvaldat,
						 	 char 				 *errstatus);
//
void fillPvk ( unsigned char *p, int length );

#ifdef __cplusplus
}
#endif

#endif  /* ! IBM3624_H */
