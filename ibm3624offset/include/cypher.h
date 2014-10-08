#ifndef CYPHER_H
#define CYPHER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
 * DES encrypt with a SINGLE Length KEY
 *
 */
void Des_encrypt ( unsigned const char *key , unsigned const char *blkIN,  unsigned char *blkOUT );
/*
 * TDES encrypt with a DOUBLE or TRIPLE Length KEY
 *
 */
void Tdes_encrypt ( unsigned const char *key , unsigned const char *blkIN,  unsigned char *blkOUT );

#ifdef __cplusplus
}
#endif

#endif  /* ! CYPHER_H */
