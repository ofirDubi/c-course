#include "modules.h"


void firstPass(char * fileName);
void secondPass(FILE * fp);
void writeToFiles(char * fileName);
void reset();
enum linePart { label_part, commandOrDecleration, arguments };
int main(int argc, char *argv[]) {
	printf("name is %s\n", argv[1]);
	while (--argc != 0) {
		firstPass(argv[argc]);

		reset();
	}
	return 0;

}

void firstPass(char * fileName) {
	
	enum linePart line_part;
	char line[80], *token;
	FILE * fp;
	int hasLabel;
	
	fp = fopen(fileName, "r");
	if(fp == NULL){
		fprintf(stderr, "ERROR: wrong file name, pregram termitating.\n");
		exit(1);
	}
	DC = 0;
	IC = 100;
	printf("first round initialisation complete. \n");
	while (fgets(line, 80, fp)) { /*start looking at a new line*/
		
		char * label; /*in case their is a label*/
		line_part = label_part;
		hasLabel = 0;
		printf("starting a new line: \" %s \" \n", line);
		token = strtok(line, " ");

		if (token[0] == ';') { /*if the line is a comment*/
			continue;
		}

		if (isLabel(token)==1) {
			hasLabel = 1;
			label = token;

			token = strtok(NULL, " ");
			printf("DEBUG: check label, label is: %s\n", label);
		}
		line_part++;
	
		while (token != NULL) {/*look at a new part of the line*/
							   /*check instructions*/
			printf("analysing line: \"%s\" \n", token);
		
			if (line_part >= 3) {
				
				fprintf(stderr, "ERROR: unexpected symbol: %s\n", token);

				error = 1;
				token = strtok(NULL, " ");
				continue;
			}
			
			if (strcmp(token, ".data")==0 || strcmp(token, ".string")==0) {
				
				if (hasLabel) { /*insert to symbol_table*/
					addToSymboleTable(label, DC, 0, 0);
					hasLabel = 0;
				}
				if (strcmp(token, ".data")==0) {
					addData(strstr(line, ".data") + 5);/*5 - the length of .data*/
				}
				else {
					addString(strstr(line, ".string") + 7);/*7 - the length of .string*/
				}
				line_part += 2;
			}
			
			else if (strcmp(token, ".extern")==0 || strcmp(token, ".entry")==0) {
				
				if (hasLabel) {
					fprintf(stderr, "WARNING: .extern and .entery dont need labels\n");

					hasLabel = 0;
				}
				if (strcmp(token, ".extern")==0) {
					addToSymboleTable(strtok(NULL, " "), 0, 1, 0);

				}else{
					token = strtok(NULL, " ");
				}
				line_part += 2;
			}
			/*check commands*/
			
			else {
				
				struct Command * command = getCommand(token);
				
				if (hasLabel) {
					printf("adding label\n");
					addToSymboleTable(label, IC, 0, 0);
					
				}

				if (command == NULL) {
					fprintf(stderr, "ERROR: %s is not a valid command.\n", token);
					error = 1;
				}
				else {
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					
					writeCommand(*command, strtok(NULL, " "));/*now doing this */
					
				}
				line_part += 2;
			}


			token = strtok(NULL, " ");
		}
	}
	printf("DEBUG: going to second pass\n");
	adjustSymbols(); /*being called when moving to second pass*/
	secondPass(fp);
	writeToFiles(fileName);
}

void secondPass(FILE * fp) {
	char line[80], *token;
	enum linePart line_part;
	rewind(fp);
	while (fgets(line, 80, fp)) { /*start looking at a new line*/
		char * label; /*in case their is a label*/


		line_part = label_part;
		token = strtok(line, " ");

		if (token[0] == ';') { /*if the line is a comment*/
			continue;
		}

		if (isLabel(token)) {/*skip this segment*/
			label = token;
			token = strtok(NULL, " ");
			printf("DEBUG: check label, label is: %s\n", label);
		}
		line_part++;

		while (token != NULL) {/*look at a new part of the line*/
			if (strcmp(token, ".data")==0 || strcmp(token, ".string")==0) {
				continue;

			}
			else if (strcmp(token, ".extern")==0 || strcmp(token, ".entry")==0) {
				if (strcmp(token, ".entry")==0) {
					writeEntry(strtok(NULL, " ")); /*TODO*/
				}
				else {
					break;
				}
			}
			else {
				struct Command * command = getCommand(token);
				if (command == NULL) {
					fprintf(stderr, "%s is not a valid command.\n", token);
					error = 1;
				}
				else {
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					writeOperands(strstr(line, command->name) + strlen(command->name));
				}
			}
			token = strtok(NULL, " ");
		}
	}

}


void writeToFiles(char * fileName) {
	char newFileName[20];
	FILE * fp_obj;
	FILE * fp_entry;
	FILE * fp_extern;
	int i;
	if (error == 1) {
		return;
	}
	strcpy(newFileName, fileName);
	strcat(newFileName, ".obj");
	fp_obj = fopen(newFileName, "w");
	strcpy(newFileName, fileName);
	strcat(newFileName, ".ent");
	fp_entry = fopen(newFileName, "w");
	strcpy(newFileName, fileName);
	strcat(newFileName, ".ext");
	fp_extern = fopen(newFileName, "w");

	/*write to entry*/
	for (i = 0; i<entry_size; i++) {
		fprintf(fp_entry, "%s  %x\n", entryList[i].current_symbol.label, entryList[i].line);
	}
	/*write to external*/
	for (i = 0; i<external_size; i++) {
		fprintf(fp_extern, "%s  %x\n", externList[i].current_symbol.label, externList[i].line);
	}

	/*write to obj*/
	fprintf(fp_obj, "Base 16    Base 16\nAddress    Machine-Code\n");
	fprintf(fp_obj, "        %d  %d\n\n", IC, DC);
	for (i = 100; i<IC; i++) {
		fprintf(fp_obj, "%X      %x\n", i, COMMAND_SEG[i].command_segment_elements.incoded_word.content);
	}
	for (i = IC; i<IC + DC; i++) {
		fprintf(fp_obj, "%X      %x\n", i,
			DATA_SEG[i].content);
	}
	printf("DONE!!!");
}


void reset() {
	free(DATA_SEG);
	free(COMMAND_SEG);
	free(externList);
	free(entryList);
	IC = 0;
	DC = 0;
	external_size = 0;
	entry_size = 0;
	symbole_table_size = 0;
}






