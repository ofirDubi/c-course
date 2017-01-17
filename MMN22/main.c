#include "set.h"

int main(){
	char input[MAXLENGTH];
	char *command;
	char completeInput[MAXLENGTH];
	printf("enter the wanted command. list of commands:\n%s",
		"print_set, read_set, union_set, intersect_set, sub_set, halt\n");
	while(bool==1){
		printf("($_$)>> ");
		
		gets(input);
		strcpy(completeInput, input);
		command = strtok((input)," ");
	
		if(strcmp(command,"print_set") == 0){
			command = strtok(NULL, " ");
			
			if(command == NULL){
				printf("invalid input\n");
				
			}else{
				printf("printing set: %c\n", command[0]);
				print_set(charToSet(command[0]));
			}
			
		}
		else if(strcmp(command, "read_set") ==0){
			printf("reading set\n the input is: %s\n", completeInput);
			read_set(completeInput);
			
		}
		else if(strcmp(command, "union_set")==0){
			command = strtok(NULL, ",");
			if(command == NULL){
				printf("invalid input\n");
				
			}else{
				set temp_A, temp_B;
				printf("preforming union_set\n");
				printf("command is:%c\n", command[strlen(command)-1]);
				temp_A = charToSet(command[strlen(command)-1]) ;/*command is a string*/
				command = strtok(NULL, ",");
				printf("command is:%c\n", command[strlen(command)-1]);
				temp_B = charToSet(command[strlen(command)-1]) ;
				
				command = strtok(NULL, ",");
				printf("command is:%c\n", command[strlen(command)-1]);
				union_set(temp_A,temp_B, command[strlen(command)-1]);
			}
		}
		else if(strcmp(command, "sub_set")==0){
			command = strtok(NULL, ",");
			if(command == NULL){
				printf("invalid input\n");	
			}else{
				set temp_A, temp_B;
				printf("preforming sub_set\n");
				temp_A = charToSet(command[strlen(command)-1]); /*command is a string*/
				command = strtok(NULL, ",");
				temp_B = charToSet(command[strlen(command)-1]); 
				command = strtok(NULL, ",");
				sub_set(temp_A,temp_B, command[strlen(command)-1]);
			}
		}
		else if(strcmp(command, "intersect_set")==0){
			
			command = strtok(NULL, ",");
			if(command == NULL){
				printf("invalid input\n");	
			}else{
				set temp_A, temp_B;
				printf("preforming intersect_set\n");
				temp_A = charToSet(command[strlen(command)-1]);
				command = strtok(NULL, ",");
				temp_B = charToSet(command[strlen(command)-1]);
				command = strtok(NULL, ",");
				intersect_set(temp_A,temp_B, command[strlen(command)-1]);
			}	
		}
		else if(strcmp(command, "halt")==0){
			bool = 0;
			printf("byby");
		}else{
			printf("no such command\n");
		}
	}
	return 0;
}
