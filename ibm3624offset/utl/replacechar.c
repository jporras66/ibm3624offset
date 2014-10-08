#include <string.h>
#include "util.h"

void replacechar(char *buff, int num, char oldc, char newc){
    int k=0;
    for(k=0; k<num;k++){
       if( *(buff+k) == oldc) *(buff+k) = newc;
    }
}
