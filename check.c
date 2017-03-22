#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	static char *k;
	k = realloc(k, 10);
	strcpy(k, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaak");
	

	
	printf(k);
	return 1;
}

