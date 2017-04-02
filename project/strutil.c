/*this file contains string functions*/

#include <ctype.h>
#include <string.h> 


int subsequentChar(char * str, char mark){
	int i;
	int prev=0;
	for(i=0;i<strlen(str); i++){
		if(str[i] == mark){
			if(prev){
				return 1 ;
			}else{
				prev =1; 
			} 
		}else{
			prev = 0;
		}
	}
	return 0;
}

void clearSpaces(char *str) {
	char* i = str;
	char* j = str;
	while (*j != 0)
	{
		*i = *j++;
		if (*i != ' ' && *i != '\n')
			i++;
	}
	*i = 0;
}

char * trimSpaces(char * str){
		
	char *end;

	  /* Trim leading space*/
	while(*str == ' ' || *str == '\n'){
		str = str+1; 
	} 

	if(*str == 0){
		
		return str;
	}
    

  /* Trim trailing space*/
  end = str + strlen(str) - 1;
	while(end > str && (*end == ' '|| *end == '\n' )) end--;

  /* Write new null terminator*/
	*(end+1) = 0;

	
	return str;
}
void strToLower(char * str){
	
	int i;
	for(i = 0; i<strlen(str); i++){
		str[i] = tolower(str[i]);
	}
	
}

void strToUpper(char * str){
			
	int i;
	for(i = 0; i<strlen(str); i++){
		str[i] = toupper(str[i]);
	}
	
}

void tabsToSpaces(char * str){
	int i;
	for(i=0; str[i]; i++){
		if(str[i] == '\t'){
			str[i] = ' ';
		}
	}
	
}
