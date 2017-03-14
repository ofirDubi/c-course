#include <stdio.h>
#include <string.h>
#include <malloc.h>
char *obtain_data();
int main(){
	printf("%s", obtain_data());
	return 1;
	
}

char *obtain_data(){
	char *buf = malloc(100);
	FILE *f;
	size_t length = 0;
	if(!buf) return NULL;
	f = fopen("data.txt", "r");
	if(!f) return NULL;
	*buf = '\0';
	printf("buf points to: %p\n", buf);
	while(fgets(buf+length, 100, f)){
		printf("now buf points to: %p\n", buf);
		length = strlen(buf);
		buf = realloc(buf, length+100);
	}
	fclose(f);
	return buf;
}