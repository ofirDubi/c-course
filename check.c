#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct word{
		 unsigned  int content;
} word; 

void kaki(word **f, size_t size);
int main(){
	word * f = NULL;
	
	
	printf("done one\n");
	
	kaki(&f, sizeof(word));
	
	kaki(&f, sizeof(word));
	f[7].content = 124;
	
	
	printf("%d", f[7].content);
	

	
	free(f);
	return 1;
}
void kaki(word **array ,size_t size){
	
	printf("____reallocing____\n");
		*array = realloc(*array, sizeof(*array) sizeof(*array) +size);
	
}
