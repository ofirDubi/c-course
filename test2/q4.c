#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	char *arr =(char *) malloc(2*sizeof(char));
	char c;
	int size = 2;
	arr[0] = getchar();
	arr[1] = '\0';
	while((c=getchar())!='\n'){
		arr = (char *) realloc((char *)arr, size+1);
		strcpy(arr+1, arr);
		arr[0] = c;
		size++;
	printf("size is %d\n", size);
	}
	arr[size] = '\0';
	printf("size is %d\n%s",(int)strlen(arr), arr);
	free(arr);
	return 0;
}