#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "offset.h"

#define LINE 80
struct INDATA {
	char pan [19+1];
	char se1 ;
	char pin [6+1];
	char se2 ;
	char offset [6+1];
	char se3 ;
	char cr  ;
	char eor ;
} ;
//
int  read_key ( unsigned char *ipvk, unsigned char* idectable, char *errstatus );
int  remove_invalid_record( char *pi, char c, char *po );
void parse_data ( char *p, char c  , struct INDATA *inrec );
//
/*
 * compute_offset  : compute OFFSET for a PAN
 *
 * RETURN:
 * 		0	OK
 * 	   -1	KO
 * INPUT
 * 		ipvk 		PVK key
 * 		idectable	decimalization table
 * 		ipan		PAN Number
 * 		ipin		Customer PIN
 * OUTPUT
 * 		offset		offset for the gived (pvk, dec_table, pan & pin)
 * 		errstatus	error message (if any)
 *
 */
int  compute_offset	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned char       *ipan,
	 	 	 	 	 unsigned char       *ipin,
	 	 	 	 	 unsigned char 		 *offset,
	 	 	 	 	 char 				 *errstatus);
//
int main(int argc, char *argv[]) {

	unsigned char dectable[] 	= 	"0123456789012345";
//							   	 	 0123456789ABCDEF
	unsigned char pvk[] 		=   "00000000000000000000000000000000";
//							   	 	 123456789-123456789-123456789-12
	char errstatus[ ERRSTABLK + 1 ];
//
	char * datapath ;
	char fnamein  [ 255];
	char fnameout [ 255];
	char fnamelog [ 255];
	char sep = '#';
	char irecord [ LINE ] ;
	char orecord[ LINE ] ;
	int k=0;
//
	memset(irecord,'\0', LINE );
	memset(orecord,'\0', LINE );
	memset(fnamein,'\0', 255 );
	memset(fnameout,'\0', 255);

//
	k = read_key ( pvk, dectable , errstatus);
	if ( k!=0) return k ;
//
	datapath = getenv("DATA");
	if ( datapath == NULL){
		fprintf( stderr, "Can not find path to input datapath :-) !!\n");
		return -1 ;
	}
//
	FILE *ifile, *ofile, *logfile;
	strcpy( fnamein, datapath);
	strcat( fnamein, "/datainput.txt");
	strcpy( fnameout, datapath);
	strcat( fnameout, "/out.txt");
	strcpy( fnamelog, datapath);
	strcat( fnamelog, "/log.txt");
//
	ifile = fopen( fnamein, "r");
	ofile = fopen( fnameout, "w");
	logfile = fopen( fnamelog, "w");
	if ( ifile == NULL ){
		fprintf( stderr, "Can not open input file :-)  %s !!\n", fnamein);
		return -1 ;
	}
	if ( ofile == NULL ){
		fprintf( stderr, "Can not open output file  :-) %s !!\n", fnameout);
		return -1 ;
	}
	if ( logfile == NULL ){
		fprintf( stderr, "Can not open logfile file  :-) %s !!\n", fnamelog);
		return -1 ;
	}
//
	fprintf(ofile,"%s", "   PAN NUMBER         PIN    OFFSET  \n");
	fprintf(ofile,"%s", "=====================================\n");
//
	struct INDATA inrec ;
	unsigned char offset [sizeof(inrec.pin)];
//
	while ( fgets ( irecord , LINE, ifile ) != NULL ){
		//printf("record is : %s \n", irecord );
		k = remove_invalid_record ( irecord, sep, orecord);
		if ( k != 0 ) {
			fprintf(logfile,"%s", orecord);
		}else{
			parse_data ( orecord, sep, &inrec );
			memset(orecord ,' ', LINE ); // fill with spaces
			memset( offset,'\0', sizeof(offset) );
//
			k = compute_offset ( pvk, dectable, (unsigned char*) inrec.pan, (unsigned char*) inrec.pin, offset, errstatus );
			if ( k==0){
				memcpy( inrec.offset, offset, sizeof(offset) );
				replacechar( inrec.pan, sizeof(inrec.pan),'\0',' ');
				replacechar( inrec.pin, sizeof(inrec.pin),'\0',' ');
				replacechar( inrec.offset, sizeof(inrec.offset), '\0',' ');
				memcpy(orecord, &inrec, sizeof(inrec) );
				fprintf(ofile,"%s", orecord);
			}else{
				strcpy( orecord, (const char * ) inrec.pan );
				strcat( orecord, (const char * ) errstatus );
				replacechar( orecord, sizeof(orecord), '\0',' ');
				orecord[LINE-1] = '\n';
				fprintf(logfile,"%s", orecord);
			}
		}
	}

	fclose (ifile);
	fclose (ofile);
	fclose (logfile);
//
	return 0 ;
}
/*
 * Allowed values ( only decimal digits and sep='#' character )
 */
int remove_invalid_record( char *pi, char c, char *po ){

	memset(po ,'\0', LINE );
	int i=0;
	strcpy( po, pi );
	while ( *(pi+i) != '\n'){
		char* pc = (pi+i) ;
		boolean b = isDec( (const unsigned char*) pc, 1 );
		if  ( b == FALSE && *pc != c )  return -1;
		i++;
	}
	if ( i < 5 ){
		return -1 ;
	}
	return 0 ;
}

void parse_data ( char *p , char c, struct INDATA *inrec ){

	inrec->se1 = c ;
	inrec->se2 = c ;
	inrec->se3 = c ;
	inrec->cr  = '\n' ;
	inrec->eor  = '\0';
	memset( inrec->offset,'\0', sizeof(inrec->offset) );
//
	memset( inrec->pan,'\0', sizeof(inrec->pan) );
	char * pch=strchr( p , c ); 	//position for ocurrence of 'char c'
	int i = pch-p ;
	memcpy( inrec->pan, p, i );
//
	memset( inrec->pin,'\0', sizeof(inrec->pin) );
	pch=strchr( p+i+1 , c );
	int k = pch - (p+i+1);
	memcpy( inrec->pin, (p+i+1) , k );
//
}

int read_key ( unsigned char *ipvk, unsigned char* idectable, char *errstatus ) {
	printf("Please type DOUBLE KEY data (32 hex digits), then <enter> : \n");
	scanf("%s", ipvk );
	int k =  validateKey ( ipvk , errstatus ) ;
	if ( k == -1 ){
		printf("find_offset.read_key %2d %s \n", k, errstatus);
		return k;
	}
	printf("Please type DECIMALIZATION TABLE data (16 decimal digits), then <enter> : \n");
	scanf("%s", idectable );
	k =  validateDecTable ( idectable , errstatus ) ;
	if ( k == -1 ){
		printf("find_offset.read_DEC_TABLE %2d %s \n", k, errstatus);
		return k;
	}
	return 0 ;
}

int  compute_offset	(unsigned const char *ipvk,
	 	 	 	 	 unsigned const char *idectable,
	 	 	 	 	 unsigned char       *ipan,
	 	 	 	 	 unsigned char       *ipin,
	 	 	 	 	 unsigned char 		 *offset,
	 	 	 	 	 char 				 *errstatus)
{
	int k=0;
//
	unsigned char pinvaldat[ MAXDATVAL + 1 ];
	k = pinValidationData ( ipan, 12, pinvaldat, errstatus);
	if ( k!=0) return k;
//
	k = ibm3624Offset ( ipvk, ipin , idectable , pinvaldat, offset, errstatus);
	if ( k!=0) return k;
//
	return 0 ;
}
