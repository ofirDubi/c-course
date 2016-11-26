#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100 /* the max length of the string that the program recieves as input */

void contract(char s1[], char s2[]); /* declaring the function contract so it can be used in main */

/*main function */
int main(){
	char s1[MAXLENGTH]; /* the first String */
	char s2[MAXLENGTH]; /* the second String */
	printf("enter the string to s1\n");
	gets(s1); /* puts the users string input into s1 */
	
	contract(s1, s2);
	printf("s2 = %s\n", s2); /* print s2, to see if the contract worked */
	return 0;
}
/* the function contract recives 2 strinngs, s1 and s2. It copy's the string from s1
	to s2 in a shorted format - each 3 or more following characters (determened by their ASCII value) 
	will be represented like this: firstChar-lastChar.
	for example: abcd => a-d.

*/
void contract(char s1[], char s2[]){
	char firstChar, lastChar; /*define the first char in a possible ASCII sequence and the last char in 
								that sequence*/
	
	int i, location = 0; /*the location to put the current char from s1 in s2 */

	
	for(i=0; i<strlen(s1); ++i){ 
		firstChar = s1[i];
		/* checks for 3 following ASCII notes */
 		if((s1[i]+1) == s1[i+1] && s1[i+1] != '\0' && (s1[i+1]+1) == s1[i+2] && s1[i+2] != '\0' ){
				while((s1[i]+1) == s1[i+1] && s1[i+1] != '\0'){ /* stops when the next char is not a following
																	ASCII value or if its the end of the array */
					lastChar = s1[i+1];
					i++;
				}
				s2[location] = firstChar;
				++location;
				s2[location] = '-';
				++location;
				s2[location] = lastChar;
				++location;
		}else{
		
			s2[location] = firstChar;
			++location;
		}
	}
	s2[location] = '\0'; /* to clear any trash values in s2 after the end of the wanted array */
}


