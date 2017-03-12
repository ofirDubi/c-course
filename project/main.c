#include <stdio.h>
#include <string.h>
#include <modules.h>
firstPass(char * fileName);

int main(int argc, char *argv[]){
	while(--argc !=0){
		firstPass(argv[argc]);
		secondPass(argv[argc]);
		reset();
	}
	
	
}


firstPass(char * fileName){
	char line[80], *token;
	FILE * fp = fopen(fileName+".as", r);
	int hasLabel;
	DC =0;
	IC = 0;
	
	while(fgets(line, 80, fp)){
		token = strtok(line, " ");
		if(token[0] == ';'){ /*if the line is a comment*/
			continue;
		}
		while(token!=NULL){
			hasLabel = isLabel(line);
			if(strcmp(token, ".data")|| strcmp(token, ".string")){
				if(hasLabel)
			}			
			token = strtok(NULL, " ");
		}
	}
	
}