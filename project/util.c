#include "modules.h"
#include <ctype.h>



#define arrayRealloc(array,array_size, size) {\
\
	*array = realloc(*array, (array_size)+(size));\
}


#define checkArgument(command, arg_num, type, res){\
	switch (type){\
		case immediate:\
			res  = command.arg_num.immediate;\
			break;\
		case direct:\
			res  = command.arg_num.direct;\
			break;\
		case reg_index:\
			res  = command.arg_num.reg_index;\
			break;\
		case reg_direct:\
			res  = command.arg_num.reg_direct;\
			break;\
		default:\
			break;\
	}\
}	


void printSymboles();
static struct Command machine_commands[16] = { { "mov",0, 2, all_types,not_immediate },
{ "cmp", 1, 2, all_types, all_types },{ "add",2,2,all_types,not_immediate },
{ "sub",3,2,all_types,not_immediate },{ "not",4,1,not_immediate },
{ "clr",5,1, not_immediate },{ "lea",6,2,{ 0,1,1,0 },not_immediate },
{ "inc",7,1,not_immediate },{ "dec", 8, 1, not_immediate },
{ "jmp",9,1,not_immediate },{ "bne", 10, 1, not_immediate },
{ "red", 11, 1, not_immediate },{ "prn", 12, 1, all_types },
{ "jsr", 13, 1,not_immediate },{ "rts", 14,0 },{ "stop",15,0 }

};


int isInEntry(char * arg);



int checkArgumentType(struct Command command, int arg_num, enum argument_types type);


static struct symbol * symbol_table = NULL;







/*returns a pointer to a command with the given name*/
struct Command * getCommand(char * string) {
	int i;
	
	clearSpaces(string);
	strToLower(string);

	for (i = 0; i<16; i++) {
		if (strcmp(machine_commands[i].name, string) == 0  ) {
			return &machine_commands[i];
		}

	}
	return NULL;
}

/*return a pointer to a symbol with the given name*/
struct symbol * getSymbol(char * str) {
	int i;
	
	for (i = 0; i<symbol_table_size; i++) {
		if (strcmp(str, symbol_table[i].label) == 0) {
			
			
			return &symbol_table[i];
		}
	}
	
	return NULL;

}

/*determins if a given string can be a label*/ 
int isLabel(char * string) {
	char buff[10];
	string = trimSpaces(string);/*change to removes the leading and ending spaces 
									and newline characters from a string*/
	if(strlen(string) > 10){
		fprintf(stderr, "ERROR: in line %d, Label or command '%s' is too long\n\n", line_num, string);
		error = 1;
		return 0;
	}
	if(string[0] == 'r'){
		int num = string[1] - '0';
		if(num<=7 && num>=0){
			return 0;
		}
	}
	strncpy(buff, string, strlen(string) - 1); /*doesn't copy the ':'*/
	
	if (string[0] == '.' || string[0] == ',' || getCommand(buff) != NULL || !isalpha(string[0]) || string[strlen(string) - 1] != ':' ) {
		return 0; /*false*/
	}
	else {
		return 1; /*true*/
	}

}

/*adds a new symbol to the symbol table*/
void addToSymbolTable(char * label, int address, int isExternal, int isCommand) {
	
	
	
	if (label[strlen(label) - 1] == ':' ||label[strlen(label) - 1] == '\n'  ) {
		label[strlen(label) - 1] = '\0'; /*removes the ':' or '\n' from the string*/
	}
	if (getSymbol(label) != NULL) {
		if(getSymbol(label)->isExternal==1 && isExternal==1){
			fprintf(stderr, "WARNING: in line %d, the external label: '%s' has been declared before.\n\n", line_num, label);
			return; /*its ok to declare the same external twice*/
		}
		fprintf(stderr, "ERROR: in line %d, label %s already exists, getSymbol result is\n\n", line_num, label);
		error = 1;
		return;
	}
	

	
	arrayRealloc(&symbol_table, sizeof(struct symbol)*symbol_table_size, sizeof(struct symbol));

	

	strcpy(symbol_table[symbol_table_size].label, label);
	symbol_table[symbol_table_size].address = address;
	symbol_table[symbol_table_size].isExternal = isExternal;
	symbol_table[symbol_table_size].isCommand = isCommand;


	symbol_table_size++;

	
}

/*add a string to the DATA_SEG*/
void addString(char * token) {
	int i;
	int mul = 5;
	token = trimSpaces(token);
	
	if (token[0] != '"' || token[strlen(token) - 1] != '"' ||
		memchr(token + 1, '"', strlen(token) - 2) != NULL) {

		fprintf(stderr, "ERROR: in line %d, argument-%s is not a valid string.\n\n",line_num, token);
		error = 1;
		return;
	}
	for (i = 1; i < (strlen(token) - 1); i++) {
		arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(struct word), sizeof(struct word)*mul);

		DATA_SEG[DC].content = token[i];
	
		DC++;
	}
	arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(struct word), sizeof(struct word)*mul);
	DATA_SEG[DC].content = 0; /*end of string*/
	DC++;

}
/*adds data to the DATA_SEG*/
void addData(char * token) {
	char * ptr;
	int temp;
	word num;
	
	if(subsequentChar(token, ',')){ /*if there are 2 subsequent ',' in token, report 
										an error*/
	
		fprintf(stderr, "ERROR: in line %d, ',' is an invalid data argument. it should be a number.\n\n", line_num);
		error =1;
		return;
	}

	token = strtok(token, ",");
	
	while (token != NULL) {
		
		temp = strtol(token, &ptr, 10); /*add check for wrong numbers*/
		
		token = trimSpaces(token);
		ptr = trimSpaces(ptr);
		if(strlen(token) ==0 || (temp==0 && token[0] != 0) || strlen(ptr) != 0){
			fprintf(stderr, "ERROR: in line %d, '%s' is an invalid data argument. it should be a number.\n\n", line_num, strlen(token) ==0?" ":token);
			error =1;
			return;
		}
		
		
		if(temp > 16384 ||temp < -16384){/*the maximum number 15 bit can hold*/
		fprintf(stderr, "ERROR: in line %d, numbers can be between 16384 and -16384, the number %d is out of range.\n\n", line_num, temp);
		error = 1;
		}
		num.content = temp;
		arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(struct word), sizeof(struct word)*6);
		DATA_SEG[DC].content = num.content;
		DC++;
		token = strtok(NULL, ",");
	}


}

/*return the argument type for a given argument*/
enum argument_types getArgumentType(char * argument) {
	char buf[10];
	/*get a string. and check the type of its argument*/
	argument = trimSpaces(argument); /*remove initial spaces*/
	if (argument[0] == '#') { /*immediate argument*/
		return immediate;
	}
	if (tolower(argument[0]) == 'r' ) {
		if (argument[2] != '[') {
			int reg_num = argument[1] - '0';
			if(reg_num > 7 || reg_num < 0 || strlen(argument) >2){
				return direct; /*a label named r9 is legal*/
			}
			return reg_direct;
		}
		else {
			return reg_index;
		}
	}
	else {
		
		if (argument[0] == '.' || argument[0] == ',' || getCommand(strncpy(buf, argument, strlen(argument)) - 1) != NULL || !isalpha(argument[0]) ) { 
			/*if the operand cant be a label*/
			fprintf(stderr, "ERROR: in line %d, unidentified operand - %s.\n\n", line_num, argument);
			error =1;
		}
		
			return direct;
		
			
		
		
	}
}
/*writes the given command into COMMAND_SEG*/
void writeCommand(struct Command command, char * arguments) {
	/*check for errors*/
	char arguments_cpy[20]; /*a copy to be used in strtok*/
	word command_word;
	struct unwritten_argument unwritten_1, unwritten_2;
	char * first_arg, *second_arg;
	
	int words = 0;
	
	enum argument_types arg1=0, arg2=0;

	unwritten_1.line = line_num;
	unwritten_2.line = line_num;
	strcpy(arguments_cpy, arguments);
	
	if(command.operand_number < 2){ /*if the command has less then 2 arguments,
									there is no need for a ',' in the line*/
		first_arg = strtok(arguments, " ");
	}else{
		first_arg = strtok(arguments, ",");
	}
	
	if(first_arg != NULL){
		first_arg = trimSpaces(first_arg);
	}
	if ((command.operand_number == 0 && first_arg != NULL) && strlen(first_arg)!= 0) {
		fprintf(stderr, "ERROR: in line %d, trying to pass argument '%s' to a command that doesn't takes arguments (%s)\n\n", line_num, first_arg, command.name);
		error = 1;
		return;
	}
	if((first_arg == NULL || strlen(first_arg)==0)&&command.operand_number != 0){
		fprintf(stderr, "ERROR: in line %d, command %s requiers %d arguments\n\n", line_num, command.name, command.operand_number);
		error =1;
		return;
	}	
	
	
	
	second_arg = strchr(arguments_cpy, ',');
	
	
	if (command.operand_number == 1 && second_arg != NULL) {
		fprintf(stderr, "ERROR: in line %d, trying to pass second argument '%s' to a command that takes 1 \
			argument (%s)\n\n", line_num, second_arg, command.name);
		error = 1;
		return;
	}
	if(second_arg!=NULL){
		second_arg++; /*get rid of the ','*/
		
		second_arg = trimSpaces(second_arg);
	}
	if((second_arg == NULL||strlen(second_arg)==0) &&command.operand_number == 2){
		fprintf(stderr, "ERROR: in line %d, command '%s' requiers 2 arguments, only one given.\n\n", line_num, command.name);
		error =1;
		return;
	}	
	
	/*check for more then one arguments*/
	if(second_arg != NULL){
		if(strchr(second_arg, ',') != NULL){
			fprintf(stderr, "ERROR: in line %d, unexpected symbol: %s\n\n", line_num,strchr(second_arg, ','));
			error =1;
		}
		else if(strchr(second_arg, ' ') != NULL){
			fprintf(stderr, "ERROR: in line %d, unexpected symbol: %s\n\n", line_num,strchr(second_arg, ' '));
			error =1;
		}
		
	}
	
	/*strtok to get past the second arg in the main function*/
	if(command.operand_number == 2){
	
		strtok(arguments, ",");
		
	}

	
	/*check argument types*/
	if (command.operand_number == 0) {
		words = 0;
		
	}
	if (command.operand_number == 1) {
		words = 1;
		arg1 = getArgumentType(first_arg);
		if(checkArgumentType(command, 0,arg1)==0){
			fprintf(stderr,"ERROR: in line %d, the first argument has wrong type for command %s\n\n", line_num, command.name);
			error = 1;
		} /*0 - the first argument*/
		unwritten_1.type = arg1;
		strcpy(unwritten_1.argument, first_arg);
		
		/*the order of the operands is switched when there is only one operand*/
		arg2 =arg1;
		arg1=0;
	}
	if (command.operand_number == 2) {
		arg1 = getArgumentType(first_arg);
		if(checkArgumentType(command, 0,arg1)==0){
			fprintf(stderr,"ERROR: in line %d, the first argument has wrong type for command %s\n\n", line_num, command.name);
			error = 1;
		}
		
		arg2 = getArgumentType(second_arg);
		
		if(checkArgumentType(command, 1,arg2)==0){
			fprintf(stderr,"ERROR: in line %d, the second argument of type %d has wrong type for command %s\n\n", line_num, arg2, command.name);
			error = 1;
		}
		if (arg1 == reg_direct && arg2 == reg_direct) {
			unwritten_1.type = double_reg_direct;
			words = 1;
			
			strcpy(unwritten_1.argument, first_arg);
			unwritten_1.argument[strlen(first_arg)] = ',';
			unwritten_1.argument[strlen(first_arg)+1] = '\0'; 
			strcat(unwritten_1.argument, second_arg);
		}
		else {
			unwritten_1.type = arg1;
			strcpy(unwritten_1.argument, first_arg);


			unwritten_2.type = arg2;
			strcpy(unwritten_2.argument, second_arg);

			words = 2;
		}
	}


	/*  unsuded     group                         opcode         firstArg  */
	command_word.content = (7 << 12) + (command.operand_number << 10) + (command.opcode << 6) + (arg1 << 4) +
		/*second arg     ARE*/
		(arg2 << 2);

	arrayRealloc(&COMMAND_SEG, sizeof(struct command_segmet_rapper)*(IC),sizeof(struct command_segmet_rapper) * (words+10)); /*words+1: one word for
												the command*/

	if (COMMAND_SEG == NULL) {
		fprintf(stderr, "ERROR: in line %d, realloc failed\n\n", line_num);
		exit(1);
	}/*clear*/

	COMMAND_SEG[IC].isWord = 1;
	COMMAND_SEG[IC++].command_segment_elements.incoded_word = command_word;

	if (words >= 1) {
		COMMAND_SEG[IC].isWord = 0;
		COMMAND_SEG[IC++].command_segment_elements.unwrittenArgument = unwritten_1;

	}


	if (words == 2) {
		COMMAND_SEG[IC].isWord = 0;
		COMMAND_SEG[IC++].command_segment_elements.unwrittenArgument = unwritten_2;
	}

}

/*adjusting he symbols adress when going to second pass*/
void adjustSymbols() {
	int i;
	for (i = 0; i<symbol_table_size; i++) {
		if (!symbol_table[i].isExternal && !symbol_table[i].isCommand) { /*if its data*/
			symbol_table[i].address += IC +100;
		}
	}

}

/* writes the operands of the commands in COMMAND_SEG*/
void writeOperands(char * arguments) {
	word temp;

	/*now ic points to the command, so we need to increase it*/
	IC++;
	
	if(IC>=max_IC){/*if the code ends*/
		return;
	}
	
	if(COMMAND_SEG[IC].command_segment_elements.unwrittenArgument.line != line_num){
		
		
		IC--;
		return;
		
	}
	
	temp = argToWord(COMMAND_SEG[IC].command_segment_elements.unwrittenArgument);

	if (COMMAND_SEG[IC].command_segment_elements.unwrittenArgument.type == reg_direct) {
		temp.content = (temp.content << 6); /*adjusting the word acording to the rules*/
	}
		
	COMMAND_SEG[IC].command_segment_elements.incoded_word.content =
		temp.content;
	
	IC++;

	
	if(IC>max_IC){
		return;
	}
	if (COMMAND_SEG[IC].isWord==1) {
		
		return;
	}
	else {
		word temp;
		temp =argToWord(COMMAND_SEG[IC].command_segment_elements.unwrittenArgument);
		COMMAND_SEG[IC].command_segment_elements.incoded_word = temp;
		IC++;
	}


}
/*returns the word that matchs a given argument*/
word argToWord(struct unwritten_argument arg) {
	word incoded_word;

	switch (arg.type) {
	case immediate:
		incoded_word = immediateToWord(arg.argument);
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
		break;
	 default:
		
		incoded_word.content = 0;
		break;
	}
	return incoded_word;

}

/*returns a word that matchs an argument of type doubleRegDirect*/
word doubleRegDirectToWord(char * arg) {
	word res[1];
	word temp1, temp2;

	temp1 = regDirectToWord(strtok(arg, ","));
	
	temp2 = regDirectToWord(strtok(NULL, ","));

	/*temp1.content = (temp1.content>>2);*//*temp1 and temp 2 are getting shifted on 
						regDirectToWord, so i unshift them*/
	/*temp2.content = (temp2.content>>2);*/
	res->content = (temp1.content << 6) + temp2.content;
	return *res;
}

/*returns a word that matchs an argument of type regIndex*/
word regIndexToWord(char * arg) {
	word res[1];
	int first_reg, second_reg;
	sscanf(arg, "r%d[r%d]", &first_reg, &second_reg);
	if (first_reg % 2 != 1 || first_reg>7 || first_reg<0) {
		fprintf(stderr, "ERROR: in line %d, first reg in indexing must be uneven and between 0 to 7, but its: %d \n\n", line_num,  first_reg);
		error = 1;
		res->content = 0;
		return *res;
	}
	if (second_reg % 2 != 0|| second_reg>7 || second_reg<0) {
		fprintf(stderr, "ERROR: in line %d, second reg in indexing must be even and between 0 to 7, but its: %d \n\n",line_num, second_reg);
		error = 1;
		res->content = 0;
		return *res;
	}
	res->content = (first_reg << 2) + (second_reg << 8);
	return *res;
}
/*returns a word that matchs an argument of type regDirect*/
word regDirectToWord(char * arg) {
	word res[1];
	
	int reg_num;
	
	
	arg = trimSpaces(arg);
	strToLower(arg);/* if reciving R*/
	sscanf(arg, "r%d", &reg_num);
	if (reg_num<0 || reg_num > 7) {
		fprintf(stderr, "ERROR: in line %d, there are only 8 registers, r0-r7. register number: %d is invalid\n\n", line_num,  reg_num);
		res->content = 0;
		error = 1;
		return *res;
	}
	res->content = reg_num << 2;
	return *res;

}

/*returns a word that matchs an argument of type Direct*/
word directToWord(char * arg) {
	word res[1];
	
	struct symbol * current_symbol = getSymbol(arg);
	
	if(current_symbol == NULL){
		fprintf(stderr, "ERROR: in line %d, the label '%s' is undefined\n\n", line_num, arg);
		error = 1;
		res->content = 0;
		return *res;
	}
	if (current_symbol->isExternal) {
		writeExternal(*current_symbol);
		
		res->content = 1;
		
		return *res; /*translates to 0000000000000-01*/
	}
	if (current_symbol->isCommand) {
		fprintf(stderr, "ERROR: in line %d, cant use a command (%s) as an operand for a command\n\n",line_num,  arg);
		error = 1;
		res->content = 0;
		return *res;
	}
	
	res->content = (current_symbol->address << 2) + 2;/*for A R E*/
	return *res;

}
/*returns a word that matchs an argument of type immediate*/
word immediateToWord(char * arg) {
	word res[1];
	unsigned int temp;
	int isNegative=0;
	char * token, *ptr;
	arg = trimSpaces(arg);

	if(arg[1] == '-'){
		
		isNegative = 1;
		token = strchr(arg, '-')+1;
	}else{
		token = strchr(arg, '#')+1;
	}
	temp = strtol(token, &ptr, 10);
	if((temp ==0 && token[0] != '0') || ptr != token +strlen(token)){
		fprintf(stderr, "ERROR: in line %d, '%s' is not a legal immediate number\n\n", line_num, token);
	}
	if(temp > 4096){
		fprintf(stderr, "ERROR: in line %d, immediate numbers can be between 4096 and -4096, the number %d is out of range.\n\n",line_num, temp);
		error = 1;
	}
	if (isNegative==1) {
		temp = (~temp); /*2's compliment*/
		temp++;
	}
	
	temp = (temp << 2);
	res->content = temp;
	return *res;
}


/*adds a symbol to the external list*/
void writeExternal(struct symbol current_symbol) {

	
	arrayRealloc(&externList, sizeof(struct external)* external_size, sizeof(struct external));

	externList[external_size].current_symbol = current_symbol;
	externList[external_size].line = IC + 100;
	external_size++;
	
	}

/*adds a symbol to the entry list*/
void writeEntry(char * arg) {
	
	struct symbol * current_symbol;
	if(arg == NULL){
		fprintf(stderr, "ERROR: in line %d, missing entry operand\n\n", line_num);
		error = 1;
		return;
	}
	clearSpaces(arg);
	if(strlen(arg)==0){
		fprintf(stderr, "ERROR: in line %d, missing entry operand\n\n", line_num);
		error = 1;
		return;
	}
	current_symbol = getSymbol(arg);
	
	if(current_symbol == NULL){
		fprintf(stderr, "ERROR: in line %d, the label '%s' is undefined.\n\n", line_num, trimSpaces(arg)); /*trim spaces for better looking output*/
		error = 1;
		return;
	}
	if(isInEntry(arg)){
		return;
	}
	arrayRealloc(&entryList, sizeof(struct external)* entry_size, sizeof(struct external));

	entryList[entry_size].current_symbol = *current_symbol;
	entryList[entry_size].line = current_symbol->address;
	entry_size++;
	
}

/*returns 1 if the given argument is on the entry list, and 0 if its not in it*/
int isInEntry(char * arg){
	int i;
	for(i=0; i<entry_size; i++){
		if(strcmp(entryList[i].current_symbol.label, arg)==0){
			return 1;
		}
	}
	return 0;
}	

/*checks if the operands have a currect type for the given command*/
int checkArgumentType(struct Command command, int arg_num, enum argument_types type){
	int res = 0;
	if(arg_num ==0){
		checkArgument(command, first_arg, type, res)
	}
	if(arg_num ==1){
		checkArgument(command, second_arg, type, res)
	}

	return res;
}



