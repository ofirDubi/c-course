
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
	enum linePart {label, commandOrDecleration, arguments};
	linePart line_part;
	char line[80], *token;
	FILE * fp = fopen(fileName+".as", r);
	int hasLabel;
	DC =0;
	IC = 100;
	
	while(fgets(line, 80, fp)){ /*start looking at a new line*/
		char * label; /*in case their is a label*/
		
		hasLabel = 0;
		line_part = label;
		token = strtok(line, " ");
		
		if(token[0] == ';'){ /*if the line is a comment*/
			continue;
		}
		
		if(isLabel(token)){
			hasLabel = 1;
			label = token;
			
			token = strtok(NULL, " ");
			printf("DEBUG: check label, label is: %s\n", label );
		}
		line_part++;
		
		while(token!=NULL){/*look at a new part of the line*/
			/*check instructions*/
			if(line_prat >=3){
				fprintf(stderr, "ERROR: unexpected symbol: %s\n", token);
				continue;
			}
			if(strcmp(token, ".data")|| strcmp(token, ".string")){
				if(hasLabel){ /*insert to symbol_table*/
					addToSymboleTable(label, DC, 0,0);
					hasLabel = 0;
				}
				if(strcmp(token, ".data")){
					addData(strstr(line, ".data")+5);/*5 - the length of .data*/
				}else{
					addString(strstr(line, ".string")+7);/*7 - the length of .string*/
				}
				line_part += 2;
			}else if(strcmp(token, ".extern")|| strcmp(token, ".entry")){
				if(hasLabel){
					fprintf(stderr, "WARNING: .exter and .entery dont need labels\n");
					hasLabel = 0;
				}
				if(strcmp(token, ".extern")){
					addToSymboleTable(strtok(NULL, " "), 0, 1,0);
					
				}else{
					handleEntry(); /*TODO*/
				}
				line_part += 2;
			}
			/*check commands*/
			else{
				if(hasLabel){
					addToSymboleTable(label, IC, 0,0);
				}
				struct Command command = getCommand(token);
				if(command == NULL){
					fprintf(stderr, "%s is not a valid command.\n", token);
				}else{
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					writeCommand(command, strstr(line, command.name)+strlen(command.name);/*now doing this */
				}
				line_part += 2;
			} 
			
			
			token = strtok(NULL, " ");
		}
	}
	printf("DEBUG: going to second pass\n");
	adjustSymbols(); /*being called when moving to second pass*/
	secondPass(fp);
}

secondPass(FILE * fp){
	rewind(fp);
	char line[80], *token;
	while(fgets(line, 80, fp)){ /*start looking at a new line*/
		char * label; /*in case their is a label*/
		
		
		line_part = label;
		token = strtok(line, " ");
		
		if(token[0] == ';'){ /*if the line is a comment*/
			continue;
		}
		
		if(isLabel(token)){/*skip this segment*/
			
			token = strtok(NULL, " ");
			printf("DEBUG: check label, label is: %s\n", label );
		}
		line_part++;
		
		while(token!=NULL){/*look at a new part of the line*/
			if(strcmp(token, ".data")|| strcmp(token, ".string")){
				continue;
				
			}else if(strcmp(token, ".extern")|| strcmp(token, ".entry")){
				if(strcmp(token, ".entry")){
					writeEntry(strtok(NULL, " ")); /*TODO*/
				}else{
					break;
				}
			}else{
				/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
				/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
				writeOperands(strstr(line, command.name)+strlen(command.name))
			}
			token = strtok(NULL, " ");
		}
	}
}

