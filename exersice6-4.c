#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void isInWords(char * string);
struct word {
	int num;
	char *content , *token;
} words[30];

int main(){
	
	char input[100];
	int i;
	gets(input);
	
	token = strtok(input, " ");
	
	while(token != NULL){
		isInWords(token);
	}	
	for(i=0; i<words.length; i++){
		printf("word is: %s appered : %d \n", words[i].num, words[i].content);
	}
	return 0;
}

void isInWords(char * string){
	int i=0;
	while(words[i].num==0){
		if(strcmp(words[i].content, string)){
			words[i].num++;
			return;
		}
	}
	/*if came this far, then string is not in words*/
	words[i].content = string;
	words[i].num = 1;
	
}