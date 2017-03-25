#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct word{
		 unsigned  int content:15;
} word; 

void kaki(word **f);
int main(){
	word * f;
	
	
	printf("done one\n");
	kaki(&f);
	f[0].content = 22;
	
	printf("%d", f[0].content);
	

	
	
	return 1;
}
void kaki(word **f ){
	*f = realloc(*f, sizeof(*f)+sizeof(word));
}
