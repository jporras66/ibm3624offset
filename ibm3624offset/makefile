#
ARCH:= $(shell uname -s | cut -c 1-6)
#
AR=ar r
RANLIB=ranlib
#
# TRACE=-D TRACE, enables displaying tracing information from *.c
#
#TRACE=-D TRACE
#
ifeq ($(ARCH),Linux)
#/lib/libcrypto.a
#/usr/lib/x86_64-linux-gnu/libcrypto.so.1.0.0
	CC=gcc 
	BASEDIR=/v02/workspace/ibm3624offset
	OPENSSL_INCLUDE=-I /usr/include/openssl
#	OPENSSL_LIB=-L /lib -l crypto		
	OPENSSL_LIB=-L /usr/lib/x86_64-linux-gnu -l crypto
	CCFLAGS=-O0 -g3 -Wall
endif
#
ifeq ($(ARCH),CYGWIN)
	CC=gcc
	BASEDIR=/cygdrive/C/DATOS/E/workspace/ibm3624offset
	OPENSSL_BASE=/cygdrive/C/DATOS/E/openssl
	OPENSSL_INCLUDE=-I $(OPENSSL_BASE)/include -I $(OPENSSL_BASE)/include/openssl
	OPENSSL_LIB=-L $(OPENSSL_BASE)/lib -l crypto	
	CCFLAGS=-O0 -g3 -Wall
endif 
#
ifeq ($(ARCH),SunOS)
	CC=gcc
	BASEDIR=<PATH_TO_SOURCE_DIR>
	OPENSSL_BASE=/usr/sfw
	OPENSSL_INCLUDE=-I $(OPENSSL_BASE)/include -I $(OPENSSL_BASE)/include/openssl
	OPENSSL_LIB=-L $(OPENSSL_BASE)/lib -l crypto
	CCFLAGS=-O0 -g3 -Wall
endif
#
SOURCE=$(BASEDIR)/src
SRCUTL=$(BASEDIR)/utl
SRCMAIN=$(BASEDIR)/main
SRCTEST=$(BASEDIR)/test
OBJ=$(BASEDIR)/obj
LIB=$(BASEDIR)/lib
BIN=$(BASEDIR)/bin
#
INCLUDE=-I"." -I usr/include -I $(BASEDIR)/include $(OPENSSL_INCLUDE)
#
LIBOBJ= $(OBJ)/util.o $(OBJ)/pack.o  $(OBJ)/unpack.o $(OBJ)/cypher.o $(OBJ)/replacechar.o \
		$(OBJ)/validation.o $(OBJ)/naturalpin.o $(OBJ)/customerpin.o $(OBJ)/verifypin.o $(OBJ)/pinvalidationdata.o  $(OBJ)/ibm3624offset.o
LIBS=-L $(LIB) -l ibm3624 $(OPENSSL_LIB)
#
all: lib main
#
test: $(BIN)/ut1_pinvalidationdata_01  $(BIN)/ut1_pinvalidationdata_02 $(BIN)/uat1_ibm3624offset $(BIN)/ut2_naturalpin
main: $(BIN)/find_offset
#
clean:
	rm -f $(OBJ)/*.o
	rm -f $(LIB)/libibm3624.a
	rm -f $(BIN)/*
#
lib: $(LIBOBJ)
	$(AR) $(LIB)/libibm3624.a $(LIBOBJ)
	$(RANLIB) $(LIB)/libibm3624.a
#	
#	Source in utl 
$(OBJ)/util.o: $(SRCUTL)/util.c
	$(CC) $(CCFLAGS) -c $(SRCUTL)/util.c $(INCLUDE) -o $(OBJ)/util.o 
$(OBJ)/pack.o: $(SRCUTL)/pack.c
	$(CC) $(CCFLAGS) -c $(SRCUTL)/pack.c $(INCLUDE) -o $(OBJ)/pack.o 
$(OBJ)/unpack.o: $(SRCUTL)/unpack.c
	$(CC) $(CCFLAGS) -c $(SRCUTL)/unpack.c $(INCLUDE) -o $(OBJ)/unpack.o 
$(OBJ)/cypher.o: $(SRCUTL)/cypher.c 
	$(CC) $(CCFLAGS) -c $(SRCUTL)/cypher.c $(INCLUDE) -o $(OBJ)/cypher.o
$(OBJ)/replacechar.o: $(SRCUTL)/replacechar.c 
	$(CC) $(CCFLAGS) -c $(SRCUTL)/replacechar.c $(INCLUDE) -o $(OBJ)/replacechar.o
#	
#	Source in src
$(OBJ)/naturalpin.o: $(SOURCE)/naturalpin.c
	$(CC) $(CCFLAGS) -c $(SOURCE)/naturalpin.c $(INCLUDE) -o $(OBJ)/naturalpin.o	
$(OBJ)/customerpin.o: $(SOURCE)/customerpin.c
	$(CC) $(CCFLAGS) -c $(SOURCE)/customerpin.c $(INCLUDE) -o $(OBJ)/customerpin.o	
$(OBJ)/verifypin.o: $(SOURCE)/verifypin.c
	$(CC) $(CCFLAGS) -c $(SOURCE)/verifypin.c $(INCLUDE) -o $(OBJ)/verifypin.o		
$(OBJ)/pinvalidationdata.o: $(SOURCE)/pinvalidationdata.c
	$(CC) $(CCFLAGS) -c $(SOURCE)/pinvalidationdata.c $(INCLUDE) -o $(OBJ)/pinvalidationdata.o		
$(OBJ)/validation.o: $(SOURCE)/validation.c 
	$(CC) $(CCFLAGS) -c $(SOURCE)/validation.c $(INCLUDE) -o $(OBJ)/validation.o	
$(OBJ)/ibm3624offset.o: $(SOURCE)/ibm3624offset.c
	$(CC) $(CCFLAGS) -c $(SOURCE)/ibm3624offset.c $(INCLUDE) -o $(OBJ)/ibm3624offset.o	
# 
#	Source in test
$(BIN)/uat1_ibm3624offset: $(SRCTEST)/uat1_ibm3624offset.c lib
	$(CC) $(CCFLAGS) $(SRCTEST)/uat1_ibm3624offset.c $(INCLUDE) -o $(BIN)/uat1_ibm3624offset	$(LIBS)
$(BIN)/ut1_pinvalidationdata_01: $(SRCTEST)/ut1_pinvalidationdata_01.c lib
	$(CC) $(CCFLAGS) $(SRCTEST)/ut1_pinvalidationdata_01.c $(INCLUDE) -o $(BIN)/ut1_pinvalidationdata_01	$(LIBS)
$(BIN)/ut1_pinvalidationdata_02: $(SRCTEST)/ut1_pinvalidationdata_02.c lib
	$(CC) $(CCFLAGS) $(SRCTEST)/ut1_pinvalidationdata_02.c $(INCLUDE) -o $(BIN)/ut1_pinvalidationdata_02	$(LIBS)
$(BIN)/ut2_naturalpin: $(SRCTEST)/ut2_naturalpin.c lib
	$(CC) $(CCFLAGS) $(SRCTEST)/ut2_naturalpin.c $(INCLUDE) -o $(BIN)/ut2_naturalpin	$(LIBS)	
#	Source in ibm3624
$(BIN)/find_offset: $(SRCMAIN)/find_offset.c lib
	$(CC) $(CCFLAGS) $(SRCMAIN)/find_offset.c $(INCLUDE) -o $(BIN)/find_offset $(LIBS)
		
