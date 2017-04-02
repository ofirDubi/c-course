/*
*author - Ofir Dubi
*
*Date - 2/4/2017
*
*Description - This is the main file of the C assembler project.
*				it turns assembly files into machine code.
*
*Note: The assembler accepts upper case commands and instructions.
*/


#include "modules.h"

void firstPass(char * fileName);
void secondPass(FILE * fp);
void writeToFiles(char * fileName);
void reset();/*called after each file, free's arrays and reset variables*/

enum linePart { label_part, commandOrDecleration, arguments };
/*line part is used to know if any more arguments need to come, or if the line is supose to end*/

/*initialising global variables*/
int error = 0, DC = 0, IC = 0, symbol_table_size = 0, line_num = 0;
struct command_segmet_rapper * COMMAND_SEG = NULL;
word * DATA_SEG = NULL;
struct external * externList = NULL;
int external_size = 0;
struct external * entryList = NULL;
int entry_size = 0;
/*max_ic will be changed when moving from first pass to the second pass*/
int max_IC = 1000;

int main(int argc, char *argv[]) {

	while (--argc != 0) {

		firstPass(argv[argc]);

		reset();
	}
	return 0;

}

void firstPass(char * fileName) {

	enum linePart line_part;
	char line[80], *token;
	char strtok_line[80]; /*a copy of the current line, to perform strtok on
							it*/
	FILE * fp;
	int hasLabel =0;	
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR: wrong file name, pregram termitating.\n\n");
		return;
	}	
	if(strcmp(strchr(fileName, '.'), ".as") !=0){
		fprintf(stderr, "ERROR: wrong file format, given format is: %s, expecting: '.as'\n\n",strchr(fileName, '.'));
		return;
	}

	
	while (fgets(line, 80, fp)) { /*start looking at a new line*/
		char * label; /*in case their is a label*/
		line_part = label_part;
		hasLabel = 0;
		line_num++;
		tabsToSpaces(line); /*my code doesn't handle tabs, so i transform every tab into a space*/
		
		
		strcpy(strtok_line, line);
		token = strtok(strtok_line, " "); /*the line parts are supose to be 
											separated by spaces*/
		
		if (token[0] == ';' || token[0] =='\n') { /*if the line is a comment*/
			continue;
		}
		
		
		
		if (isLabel(token)) { 
			hasLabel = 1;
			label = token;

			token = strtok(NULL, " ");
			
		}
		line_part++;

		while (token != NULL) {/*look at a new part of the line*/
							  


			if (line_part >= 3) {/*if the line is supose to end*/

				fprintf(stderr, "ERROR: in line %d, unexpected symbol: %s\n\n", line_num, token);

				error = 1;
				token = strtok(NULL, " ");
				continue;
			}
			/*if the line is a data or string statment*/
			if (strcmp(token, ".data") == 0 || strcmp(token, ".string") == 0 ||strcmp(token, ".DATA") == 0 || strcmp(token, ".STRING") == 0 ) {

				if (hasLabel) { /*insert to symbol_table*/
											
					addToSymbolTable(label, DC, 0, 0);/*the 0,0 are for
														isCommand and isExternal*/
					hasLabel = 0;
				}
				if (strcmp(token, ".data") == 0 || strcmp(token, ".DATA") == 0) {
					char * data_loc;

					data_loc = strstr(line, ".data");
					if(data_loc == NULL){
						data_loc = strstr(line, ".DATA");
					}
					addData(data_loc + 5);/*5 - the length of .data*/
				}
				else {
					char * data_loc;

					data_loc = strstr(line, ".string");
					if(data_loc == NULL){
						data_loc = strstr(line, ".STRING");
					}
					addString(data_loc + 7);/*7 - the length of .string */
					token = strtok(strrchr(line, '"'), " ");
				}
				line_part += 2; /*the line should end*/
			}

			else if (strcmp(token, ".extern") == 0 || strcmp(token, ".entry") == 0 ||strcmp(token, ".EXTERN") == 0 || strcmp(token, ".ENTRY") == 0) {

				if (hasLabel) {
					fprintf(stderr, "WARNING: .extern and .entery dont need labels\n\n");

					hasLabel = 0;
				}
				if (strcmp(token, ".extern") == 0 ||strcmp(token, ".EXTERN") == 0 ) {

												/*adress of extern is 0*/
					addToSymbolTable(strtok(NULL, " "), 0, 1, 0);

				}
				else {
					token = strtok(NULL, " ");
				}
				line_part += 2;
			}
			
			/*check commands*/
			else {

				struct Command * command = getCommand(token);
		
				if (hasLabel) {
				
					addToSymbolTable(label, IC + 100, 0, 1);

				}

				if (command == NULL) {
					fprintf(stderr, "ERROR: in line %d, '%s' is not a valid command or label.\n\n", line_num, token);
					error = 1;
					break;
				}
				else {
					
					char * arguments;
					
					arguments = strstr(line, command->name);
					if(arguments == NULL){
	
						strToUpper(token);/*the token still contains the the name of the command*/
						arguments = strstr(line, token);
						
					}
					if(arguments == NULL){ /*no match for nither lower or 
											upper case letters, it means that the command is written with mixed letters - some lower case and some upper case, which is a mistake*/
						fprintf(stderr, "ERROR: in line %d, the command %s was written with mixed case letters. write commands in all-lower or all-upper case\n\n", line_num,command->name);
						error = 1;
						break;
					}
					
					writeCommand(*command, arguments + strlen(command->name));/*write the command to the COMMAND_SEG */
				
				}
				line_part += 2;
			}


			token = strtok(NULL, " ");
			
		}
	}
	
	adjustSymbols(); /*changes the adress of some of the symbols according to IC*/
	max_IC = IC;
	IC =0;
	line_num = 0;
	secondPass(fp);


	fclose(fp);

	writeToFiles(fileName);
}

void secondPass(FILE * fp) {

	char line[80], *token;
	char strtok_line[80];
	enum linePart line_part;
	rewind(fp);
	while (fgets(line, 80, fp)) { /*start looking at a new line*/
		line_num++;
		tabsToSpaces(line); 
	

		line_part = label_part;
		strcpy(strtok_line, line);
		token = strtok(strtok_line, " ");

		if (token[0] == ';' || token[0] == '\n') { /*if the line is a comment*/
			continue;
		}

		if (isLabel(token)) {/*skip this segment*/
			
			token = strtok(NULL, " ");
			
		}
		line_part++;

		while (token != NULL) {/*look at a new part of the line*/
		
			if (strcmp(token, ".data") == 0 || strcmp(token, ".string") == 0 ||strcmp(token, ".DATA") == 0 || strcmp(token, ".STRING") == 0){
				break;

			}
			else if (strcmp(token, ".extern") == 0 || strcmp(token, ".entry") == 0 || strcmp(token, ".EXTERN") == 0 || strcmp(token, ".ENTRY") == 0) {
				if (strcmp(token, ".entry") == 0 || strcmp(token, ".ENTRY") == 0) {

					writeEntry(strtok(NULL, " ")); /*TODO*/
				}
				else {
					break;
				}
			}
			else {
				struct Command * command = getCommand(token);
				if (command == NULL) {
					/*an error message was issued in the first pass*/
					error = 1;
				}
				else {
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					/*CHANGE THE ARGUMENT TO SOMTHING THAT WORKS FOR SURE*/
					char * arguments;
					
					
					
					arguments = strstr(line, command->name);
					if(arguments == NULL){
						
						strToUpper(token);/*the token still contains the the name of the command*/
						arguments = strstr(line, token);
						
					}
					if(arguments == NULL){ /*no match for nither lower or 
											upper case letters, it means that the command is written with mixed letters - some lower case and some upper case, which is a mistake*/
						/*an error message was written in the first pass*/
						token = NULL;
						break;
					}
					writeOperands(arguments + strlen(command->name));
					/*write the operand of the command in COMMAND_SEG*/
					token = NULL;
					break;
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
	int i, file_len = strlen(fileName);
	if (error == 1) {
		printf("AN ERROR ACCURED, SO NO FILES WILL BE CREATED");
		return;
	}
	
	
	strncpy(newFileName, fileName, file_len-3); /*3 is the lenght of ".as"*/
	newFileName[file_len-3] = '\0'; /*to terminate any garbage value*/
	strcat(newFileName, ".obj");
	fp_obj = fopen(newFileName, "w");
	strncpy(newFileName, fileName, file_len-3); /*3 is the lenght of ".as"*/
	newFileName[file_len-3] = '\0'; /*to terminate any garbage value*/
	strcat(newFileName, ".ent");
	fp_entry = fopen(newFileName, "w");
	strncpy(newFileName, fileName, file_len-3); /*3 is the lenght of ".as"*/
	newFileName[file_len-3] = '\0'; /*to terminate any garbage value*/
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
	fprintf(fp_obj, "    %X    %X\n\n", IC, DC);
	
	for (i = 0; i<IC; i++) {
		
	
		
		fprintf(fp_obj, " %X      %04X \n", i + 100,COMMAND_SEG[i].command_segment_elements.incoded_word.content);
	}

	for (i = IC; i<IC + DC; i++) {
		
		fprintf(fp_obj, " %X      %04X \n", i + 100,
			DATA_SEG[i-IC].content);
	}
	fclose(fp_entry);
	fclose(fp_extern);
	fclose(fp_obj);
	printf("DONE!!!");
}


void reset() {
	
	
	if(COMMAND_SEG != NULL){
		
		free(COMMAND_SEG);
		COMMAND_SEG = NULL;
	}
	
	if(externList != NULL){
		
		free(externList);
		externList = NULL;
	}
	
	if(DATA_SEG != NULL){
	
		DATA_SEG = NULL;
	}
	
	if(entryList != NULL){
		
		free(entryList);
		entryList = NULL;
	}
	error = 0;
	IC = 0;
	DC = 0;
	line_num = 0;
	external_size = 0;
	entry_size = 0;
	symbol_table_size = 0;

}






