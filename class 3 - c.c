#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	char str1[] = "abcdsssass";
	char str2[] = "1smantuabf";
	char str3[100];
	int i;
	int cntdigits = 0, cntletters=0, cntlower=0, cntupper=0;
	
	printf("\n str1= %s\n", str1);
	printf("\n str2 = %s\n", str2);
	printf("\n strlen(str1)= %d\n" ,strlen(str1));
	printf("\n strlen(str2)= %d\n" ,strlen(str2));
	printf("\n strlen(str3)= %d\n" ,strlen(str3));
	printf("\n strcmp(str1,str2) = %d\n", strcmp(str1,str2)); /* does the action of str1-str2*/
	printf("\n strcmp(str1+4,str2+1, 3) = %d\n", strcmp(str1+4,str2+1, 3)); 
	/* does the action of str1+4(starting from item number 5)-str2+1
	(starting from the second item) 
	*/
	
	printf("\n strcpy(str3,str1+4) = %d\n", strcpy(str3,str1+4)); // copy str 1 to str 3
	
	printf("\n strcpy(str3,str1+4) = %d\n", strcpy(str3,str1+4,3)); // copy thirst 3 chars of str 1 to str 3
	
	printf("\n is strchr(str1,8) != NULL? %s\n", strchr(str1,8)?"True":"Fales");
	printf("\n strrchar is a reverse strchar search, searching from %s %d\n",
			"the end to the start", strrchr(str1,y)-str);
	
	printf("\n is strstr(str1,'cx') != NULL? %s\n", strchr(str1,"cx")?"True":"Fales");

	
	/*strcpy is for copying strings
	 
	 *strchar(str1, '8') searches for a char in an array returns 
	 a pointer with the location of the char, or null.
	 
	gets() => gets a string from input
	getchar => gets a char from input
	*/
	return 0;
}