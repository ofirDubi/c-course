#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main( int argc, char *argv[]){
	int i,j;
	for(i=1; i<argc; i++){
		for(j=0;j<strlen(argv[i]);j++){
			putchar(toupper(argv[i][j]));
		}
		
	}
	return 0;
}