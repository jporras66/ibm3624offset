#ifndef VALIDATION_H
#define VALIDATION_H

#ifndef __BOOLEAN
#define __BOOLEAN
	typedef enum {FALSE  = 0, TRUE = 1 } boolean;
#endif /* __BOOLEAN */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
//
int validateKey ( unsigned const char *ipvk , char *errstatus );
int validatePan ( unsigned const char *pan , char *errstatus );
int validatePinValidationData ( unsigned const char *ipinvalidationdata , char *errstatus );
int validatePin ( unsigned const char *ipin , char *errstatus );
boolean isValidPinLength ( const int ipinlength , char *errstatus );
int validateDecTable ( unsigned const char *idectable , char *errstatus );

#ifdef __cplusplus
}
#endif

#endif  /* ! VALIDATION_H */
