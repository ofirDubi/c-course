#include <modules.h>

#include <ctype.h>
struct Command getCommand(char * string){
	int i;
	for(i=0; i<16; i++ ){
		if(strcmp(machine_command[i], string)){
			return machine_command[i];
		}
		
	}
	return NULL;
}

struct symbol getSymbol(char * label){
	int i;
	for(i=0; i<symbole_table_size; i++){
		if(strcmp(label, symbol_table[i].label)){
			return symbol_table[i];
		}
	}
	return NULL;
	
}
int isLabel(char * string){
	char buf[10];
	if(string[0] == '.' || getCommand(strncpy(buf,string,strlen(string)-1 || !isalpha(string[0]) || string[strlen(string)-1] != ':' ){
		return 0; /*false*/
	}else{
		return 1; /*true*/
	}
	
}

void addToSymboleTable(char * label, int address, int isExternal, int isCommand){
	if(getSymbol(label)!= NULL){
		fprintf(stderr, "ERROR: label %s already exists\n", label);
		return;
	}
	
	symbol_table = realloc(symbol_table,
						sizeof(symbol_table)+sizeof(struct symbol));
	
	if(label[strlen(label)-2]==':'){
		label[strlen(label)-2] = '\0'; /*removes the ':' from the label*/
	} 
	symbol_table[symbole_table_size] = {label, address, isExternal, isCommand};
	
	symbole_table_size++;
}
void addString(char * token){
	int i;
	if(token[0] != '"' || token[strlen(token)-1] != '"' || 
	 memchr(token+1, '"', strlen(token)-2) != NULL){
		
		fprintf(stderr, "ERROR: argument: %s is not a valid string.\n", token);
		return;
	}
	for(i=1; i<strlen(token)-1; i++){
		DATA_SEG = realloc(DATA_SEG, sizeof(DATA_SEG) + sizeof(word));
		DATA_SEG[DC] = (word) token[i];
		DC++;
	}
	DATA_SEG = realloc(DATA_SEG, sizeof(DATA_SEG) + sizeof(word));
	DATA_SEG[DC] = 0; /*end of string*/
	DC++;
	
}
void addData(char * token){
	int i, number_Started=0;
	char *endptr;
	word num;
	token = strtok(token, ",");
	while(token != NULL){
		num = (word) strtol(str,&ptr, 10); /*add check for wrong numbers*/
		DATA_SEG = realloc(DATA_SEG, sizeof(DATA_SEG) + sizeof(word));
		DATA_SEG[DC] = num;
		DC++;
		token = strtok(NULL, ",");
	}
	
	
}
argument_types getArgumentType(char * argument){
	/*get a string. and check the type of its argument*/
	argument = strtok(argument," "); /*remove initial spaces*/
	if(argument[0] == '#'){ /*immidiate argument*/
		return immidiate;
	}
	if(argument[0] == 'r'){
		if(argument[2] !='[' ){
			return reg_direct;
		}else{
			return reg_index;
		}
	}else{
		return direct;
	}
	
	
}


void writeCommand(struct Command command, char * arguments){
	/*check for errors*/ 
	word command_word
	char * first_arg, * second_arg, * thired_arg;
	int words=0;
	argument_types arg1, arg2;
	first_arg = strtok(arguments, ",");
	/*using strtok to remove all wihte spaces*/
	if(command.operand_number == 0 && first_arg != NULL){
		fprintf(stderr, "ERROR: trying to pass argument '%s' to a command that doesn't takes \
			arguments (%s)\n", first_arg, command.name);
		return;	
	}
	second_arg = strtok(NULL, ",");
	if(command.operand_number == 1 && second_arg != NULL){
		fprintf(stderr, "ERROR: trying to pass second argument '%s' to a command that takes 1 \
			argument (%s)\n", second_arg, command.name);
			return;	
	}
	if((thired_arg=strtok(NULL, ",")) != NULL){
		fprintf(stderr, "ERROR: trying to pass thired argument '%s' to a command that takes 2 \
			arguments (%s)\n", thired_arg, command.name);
			return;	
	} 
	/*check argument types*/
	
	
	if(command.operand_number == 0){
		words = 1;
	}
	if(command.operand_number == 1 ){
		words = 1;
	}
	if(command.operand_number == 2 ){
		arg1 = getArgumentType(first_arg);
		arg2 = getArgumentType(second_arg);
		if(arg1 == reg_direct && arg2 == reg_direct){
			word = 1;
		}else{
			word = 2;
		}
	}
	/*  unsuded     group                         opcode         firstArg  */
	command_word = 7<<12 + command.operand_number<<10 +command.opcode<<6 + arg1<<4 +
					/*second arg     EAR*/
					arg2<<2       +   0 ;
	
	COMMANDS_SEG = realloc(COMMANDS_SEG, sizeof(COMMANDS_SEG) + sizeof(word));
	COMMANDS_SEG[IC] = command_word;
	IC += word+1;
}
void adjustSymbols(){
	int i;
	for(i=0; i<symbole_table_size; i++){
		if(!symbol_table[i].isExternal && !symbol_table[i].isCommand){ /*if its data*/
			symbol_table[i].address += IC;
		}
	}
	
}













