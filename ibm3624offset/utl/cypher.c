#include "cypher.h"
#include <des.h>		// DES Openssl implementation

/*
 * DES encrypt with a SINGLE Length KEY
 *
 */
void Des_encrypt ( unsigned const char *key , unsigned const char *blkIN,  unsigned char *blkOUT ){

    DES_cblock k1;
	int i=0;
	for (i=0;i<8;i++){
		k1[i]=*(key + i);
	}
    DES_key_schedule s1;
    DES_set_key((C_Block *)k1, &s1);
    DES_ecb_encrypt((C_Block *)blkIN,(C_Block *)blkOUT, &s1, DES_ENCRYPT);
}

/*
 * TDES encrypt with a DOUBLE or TRIPLE Length KEY
 *
 */
void Tdes_encrypt ( unsigned const char *key , unsigned const char *blkIN,  unsigned char *blkOUT ){
//
// Example : http://www.opensource.apple.com/source/Heimdal/Heimdal-247.6/lib/hcrypto/destest.c
//
	DES_cblock k1, k2, k3 ;
    DES_key_schedule s1, s2, s3;
	int i=0;
	for (i=0;i<8;i++){
		k1[i]=*(key + i);
		k2[i]=*(key + i + 8);
		k3[i]=*(key + i + 16);
	}
//
    DES_set_key((C_Block *)k1, &s1);
    DES_set_key((C_Block *)k2, &s2);
    DES_set_key((C_Block *)k3, &s3);
    DES_ecb3_encrypt((C_Block *)blkIN, (C_Block *)blkOUT , &s1, &s2, &s3, DES_ENCRYPT);
}

