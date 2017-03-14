#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE *fp1, *fp2;
	char s1[200], s2[200];
	void *res1, *res2;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	if(fp1 == NULL || fp2 == NULL){
		printf("somthing went wrong\n");
		return 1;
	}
	res1 = fgets(s1, 200, fp1);
	res2 = fgets(s2, 200, fp2);
	while(res1 !=NULL && res2 != NULL && strcmp(s1,s2)==0){
		
		res1 = fgets(s1, 200, fp1);
		res2 = fgets(s2, 200, fp2);
		printf("s1: %s\ns2: %s\n",s1,s2);
	}
	printf("res1: %s, res2: %s", (char *)res1, (char *)res2);
	if(res1 == NULL && res2 == NULL){
		printf("files identical");
	}else if(res1==NULL){
		printf("files not identical.\n\"%s\" contains more lines then \"%s\"\n",argv[2],argv[1]);
		}else if(res2==NULL){
		printf("files not identical.\n\"%s\"  contains more lines then \"%s\"\n",argv[1],argv[2]);
		}else{
			printf("files not identical.\ns1: %s\ns2: %s",s1,s2);
		}
		
	
	fclose(fp1);
	fclose(fp2);
	return 0;
}
