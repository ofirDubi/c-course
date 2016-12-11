#include <stdio.h>
#include <ctype.h>
int htoi(char str[]);

int main(){
	char str[100];
	printf("enter string in hexadecimal\n");
	gets(str);
	printf("int is: %d", htoi(str));
	
	return 0;
}

int htoi(char s[]){
	int i,n =0;
	for(i =0; (s[i] >= '0' && s[i] <='9') || (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f' ) || tolower(s[i]) == 'x'; i++){
		putchar('w');
		
		if(!(s[i] =='0' && tolower(s[i+1]) == 'x')){
			n = 16 * n + (isdigit(s[i])? s[i]-'0' :(tolower(s[i]) -'a' +10));
		}else{
			i++;
		}
		
	}
	return n;
}