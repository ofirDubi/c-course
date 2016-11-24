#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100
void contract(char s1[], char s2[]);

int main(){
	char s1[MAXLENGTH];
	char s2[MAXLENGTH];
	printf("enter the string to s1\n");
	gets(s1);
	printf("s2 = %s\n", s2);
	printf("s1 = %s\n", s1);
	contract(s1, s2);
	printf("s2 = %s\n", s2);
	return 0;
}
/* i want to check if 'char+1 = next_char, if so put them together, and keep on going
	until its not true */
void contract(char s1[], char s2[]){
	char firstChar;
	char lastChar;
	
	int location = 0;
	int i;
	
	for(i=0; i<strlen(s1); ++i){
		firstChar = s1[i];
		if((s1[i]+1) == s1[i+1] && s1[i+1] != '\0'){
			if((s1[i+1]+1) == s1[i+2] && s1[i+2] != '\0'){
				while((s1[i]+1) == s1[i+1] && s1[i+1] != '\0'){
					lastChar = s1[i+1];
					i++;
				}
				s2[location] = firstChar;
				++location;
				s2[location] = '-';
				++location;
				s2[location] = lastChar;
				++location;
			}
				
			
		}else{
			if(firstChar)
			s2[location] = firstChar;
			++location;
		}
	}
	s2[location] = '\0'; /* to clear any garbage values in s2 after the end of the wanted array */
}


/* תרגיל לבית - יש משתנה int x בעל סיביות a,b,c,d,e,f אנחנו רוצים להחליף בין סיבית לסיבית
*/