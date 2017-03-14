#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *obtain_data();
int main(){
	char *s = obtain_data();
	printf("final is %s", s);
	free(s);
	return 0;
}

char *obtain_data(){
	char *buf = malloc(100);
	FILE *f;
	size_t length = 0;
	
	if(!buf) return NULL;
	f = fopen("data.txt", "r");
	if(!f) return NULL;
	
	*buf = '\0';
	while(fgets(buf+length, 100, f)){
		
		length = strlen(buf);
		
		printf("printed buf loc : %p\n", buf);
		buf = realloc(buf, length+100);
		printf("printed buf loc : %p\n", buf);
		printf("did realloc, ");
	}
	fclose(f);
	return buf;
}






/*#include <stdio.h>
#include <malloc.h>
#include <string.h>
char *obtain_data();
int main(){
	char *s = obtain_data();
	printf("%s", s);
	free(s);
	return 0;
}

char *obtain_data(){
	char *buf = malloc(100);
	FILE *f;
	size_t length = 0;
	
	if(!buf) return NULL;
	f = fopen("data.txt", "r");
	if(!f) return NULL;
	
	*buf = '\0';
	while(fgets(buf+length, 100, f)){
		
		length = strlen(buf);
		printf("did strlen, ");
		realloc(buf, length+100);
		printf("did realloc, ");
	}
	fclose(f);
	return buf;
}*/