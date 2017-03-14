#include <stdio.h>
#include <string.h>
char FindFirstVowel(char *s);

int main(){
	char string[50], c;
	scanf("%s", string);
	c = FindFirstVowel(string);
	printf("%c", c);
	return 0;
}

char FindFirstVowel(char *s){
	char *c;
	if((c=strpbrk(s,"AaEeIiOoUu"))!=NULL){
		return *c;
	}
	
	return 0;
}