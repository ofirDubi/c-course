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
	word command_word;
	struct unwritten_argument unwritten_1, unwritten_2;
	char * first_arg, * second_arg, * thired_arg;
	int words=0;
	argument_types arg1, arg2;
	printf("DEBUG:in writeOperands, arguments are: %s", arguments);
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
			unwritten_1.type = doube_reg_direct;
		}else{
			unwritten_1.type = arg1;
			unwritten_1.argument = first_arg;
			
			unwritten_2.type = arg2;
			unwritten_2.argument = second_arg;
			words = 2;
		}
	}
	/*  unsuded     group                         opcode         firstArg  */
	command_word = 7<<12 + command.operand_number<<10 +command.opcode<<6 + arg1<<4 +
					/*second arg     ARE*/
					arg2<<2       +   0 ;
	
	COMMANDS_SEG = realloc(COMMANDS_SEG, sizeof(COMMANDS_SEG) +
					sizeof(command_segment_elements) * words);
	
	COMMANDS_SEG[IC].command_segment_elements.isWord ==1;
	COMMANDS_SEG[IC++].command_segment_elements.incoded_word = command_word;
	if(words >= 1){
		COMMANDS_SEG[IC++].command_segment_elements.unwrittenArgument= unwritten_1;  
		
	}
	if(word==2){
		COMMANDS_SEG[IC++].command_segment_elements.unwrittenArgument= unwritten_2;  
	}
	
	
	 
}
void adjustSymbols(){
	int i;
	for(i=0; i<symbole_table_size; i++){
		if(!symbol_table[i].isExternal && !symbol_table[i].isCommand){ /*if its data*/
			symbol_table[i].address += IC;
		}
	}
	
}
 

void writeOperands(char * arguments){
	
	char * token;
	/*TODO: change things with reg_direct!!!*/
	printf("DEBUG:in writeOperands, arguments are: %s", arguments);
	/*now ic points to the command, so we need to increase it*/
	IC++;
	if(COMMANDS_SEG[IC++].isWord){
		return;
	}else{
		word temp = argToWord(COMMANDS_SEG[IC].command_segment_elements.unwrittenArgument);
		if(COMMANDS_SEG[IC].command_segment_elements.incoded_word.type == reg_direct){
			temp = (temp<<6); /*adjusting the word acording to the rules*/
		}
		COMMANDS_SEG[IC].command_segment_elements.incoded_word = temp;
		
		IC++;
	}
	if(COMMANDS_SEG[IC++].isWord){
		return;
	}else{
		COMMANDS_SEG[IC].command_segment_elements.incoded_word = argToWord(COMMANDS_SEG[IC].command_segment_elements.unwrittenArgument);
		IC++;
	}
	
		
}

word argToWord(struct unwritten_argument arg){
	word incoded_word;
	switch (arg.type){
		case immidiate:
			incoded_word = immidiateToWord(arg.argument);
			break;
		case direct:
			incoded_word = directToWord(arg.argument);
			break;
		case reg_direct:
			incoded_word = regDirectToWord(arg.argument);
			break;
		case reg_index:
			incoded_word = regIndexToWord(arg.argument);
			break;
		case double_reg_direct:
			incoded_word = doubleRegDirectToWord(arg.argument);
	}
	
}

word doubleRegDirectToWord(char * arg){
	return regDirectToWord(strtok(arg, ",")) <<8 + regDirectToWord(strtok(NULL, ","))<<2;
}

word regIndexToWord(char * arg){
	int first_reg, second_reg;
	sscanf(arg, "r%d[r%d]", &first_arg, &second_arg);
	if(first_reg%2 !=1){
		fprintf(stderr, "ERROR: first reg in indexing must be uneven, but its: %d \n". first_reg);
		return 0;
	}
	if(second_reg%2 !=0){
		fprintf(stderr, "ERROR: second reg in indexing must be even, but its: %d \n". second_arg);
		return 0;
	}
	return (word)((first_arg<<2) + (second_arg<<8));
}

word regDirectToWord(char * arg){
	char * token;
	int reg_num;
	/*using strtok to remove all wihte spaces*/
	token = strtok(arg, " ");
	sscanf(token, "r%d", &reg_num);
	if(reg_num<0 || reg_num > 7){
		fprintf(stderr, "ERROR: there are only 8 registers, r0-r7. register number: %d is invalid\n", reg_num);
		return (word)0;
	}
	return (word) reg_num<<2;
	
}


word directToWord(char * arg){
	struct symbol current_symbol = getSymbol(arg);
	
	if(current_symbol.isExternal){
		writeExternal(current_symbol);
		return 1; /*translates to 0000000000000-01*/
	}
	if(current_symbol.isCommand){
		fprintf(stderr, "ERROR: cant use a command (%s) as an operand for a command\n", arg);
		return 0;
	}
	return (word)((current_symbol.address<<2) + 2);/*for A R E*/
	
}

word immidiateToWord(char * arg){
	char * token = strtok(arg, '#');
	int temp;
	if(temp= atoi(token)){ /*there may or may not be spaces before the '#'*/
		printf("DEBUG: SPACES BEFORE '#' \n");
		
	}else{
		token =  strtok(NULL, '#');
		temp = temp= atoi(token);
	}
	if(temp<0){
			temp = ~temp;
	}
	temp = (temp<<2);
	return temp;
}



void writeExternal(struct symbol current_symbol){
	static struct external * externList;
	static int external_size = 0;
	externList = realloc(externList, sizeof(struct external));
	externList[external_size].current_symbol = current_symbol;
	externList[external_size].line = IC;
	external_size++;
}





