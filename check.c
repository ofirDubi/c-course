#include <stdio.h>
#include <string.h>

int main(){
	char s[100];
	char * token;
	gets(s);
	token = strtok(s, " ");
	while(token!=NULL){
		printf("%s\n", token);
		
		
		
		token = strtok(NULL, " ");
	}
	return 1;
}

