#include <stdio.h>
#include <stdlib.h>
void printInput(FILE *, FILE *);

int main(int argc, char *argv[]){
	FILE *fp;
	if(argc==1){
		printInput(stdin, stdout);
	}else{
		while (--argc>0)
			if((fp = fopen(*++argv, "r")) == NULL){
				fprintf(stderr,"invalid input\n");
				exit(1);
			}else{
				printInput(fp, stdout);
				fclose(fp);
			}
			
		}
		  
	
	return 0;
}

void printInput(FILE * input, FILE *output){
	
	int c;
	while((c=getc(input))!=EOF){
		putc(c, output);
	}
}