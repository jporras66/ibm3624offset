==========================================
ibm 3624 offset library  - Build & Install
==========================================

1.Requirements

	1.1 Openssl header files installed 
	1.2 Openssl libcrypto.a or libcrypto.so

2. Review makefile ( ifeq ($(ARCH),SunOS) )

	2.1 Verify BASEDIR points to the rigth directory.
		BASEDIR=<PATH_TO_SOURCE_DIR>
		
	2.2 Save makefile
		
3. How build.
		
	$ cd <PATH_TO_SOURCE_DIR>
	$ export LD_LIBRARY_PATH=/usr/sfw/lib:$LD_LIBARRY_PATH
	$ make clean 
	$ make all  
	$ ls -ali ./lib/libibm3624.a
	$ ar -t ./lib/libibm3624.a
	$ ls -ali ./bin
		
3. Test.

	$ cd <PATH_TO_SOURCE_DIR>
	$ export LD_LIBRARY_PATH=/usr/sfw/lib:$LD_LIBARRY_PATH
	$ export DATA=<PATH_TO_SOURCE_DIR>/data
	$ edit ./data/datainput.txt, and add records:
 	  Format is:	card_pan_number#clear_pin_number#
	$ Execute ./bin/find_offset and enter required data
	  Please type DOUBLE KEY data (32 hex digits), then <enter> :
	  Please type DECIMALIZATION TABLE data (16 decimal digits), then <enter> :
	$ edit and review ./data/out.txt and ./data/log.txt

=======================================
ibm 3624 offset library - How use 
=======================================	

Available Services:

 	customerPin: 		Get a customer PIN from an OFFSET
 	ibm3624Offset:		Get an OFFSET from customer PIN
 	verifyPin :		Verify a PIN/OFFSET pair match
 	pinValidationData : 	Build a pinvalidationdata block, inserting 5 last digits of Account Number in a gived position	
 	naturalPin:		Get a natural pin from a giving pin validation data block

How find offset :

	Calling function compute_offset inside main/find_offset.c:
	Review /data/test_data.xlsx for key and decimalization table used.

/*
 * compute_offset  : compute OFFSET for a PAN
 *
 * RETURN:
 * 		0	OK
 * 	   	-1	KO
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

