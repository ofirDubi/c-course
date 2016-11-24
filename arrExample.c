#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(){
	int len; /*current line length*/
	int max; /*max line length so far*/
	char line[MAXLINE]; /*our current line */
	char longest[MAXLINE]; /*our longest line so far*/
	max = 0;
	while((len = getline(line, MAXLINE)) >0 && len !=3){
		if(len > max){
			max = len;
			copy(longest, line);
		}
	}
	if(max > 0){
		/*there is a new line */
		printf("%s, %c\n", longest, longest[1]+1);
		printf("this is the test %c", 'c'+1);
	}
	return 0;
}

int getline(char s[], int lim){
	int c,i;
	for(i=0; i<lim-1 && (c=getchar())!= EOF && c!='\n'; ++i ){
		s[i] = c;
	} 
	if( c == '\n'){
		s[i] =c;
		++i;
	}
	s[i] = '\0';
	return i;
}
void copy(char to[], char from[]){
	int i;
	i=0;
	while((to[i] = from[i]) != '\0'){
		++i;
	}
}