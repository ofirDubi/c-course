#include "modules.h"
#include <ctype.h>
#define arrayRealloc(array,array_size, size) {\
\
	printf("____reallocing____\n");\
	*array = realloc(*array, ((array_size)+(size)));\
	printf("done reallocing\n");\
	\
}

#define clearString(string){\
	if (string[strlen(string) - 1] == ':' ||string[strlen(string) - 1] == '\n'  ) {\
		string[strlen(string) - 1] = '\0'; /*removes the ':' or '\n' from the string*/\
	}\
}
struct external * entryList = NULL;
int entry_size = 0;

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
static struct symbol * symbol_table = NULL;
void arrayReallocs(struct command_segmet_rapper ** array, size_t size) {

	printf("____reallocing____\n");
	*array = realloc(*array, (size));
	printf("done reallocing\n");

}




struct Command * getCommand(char * string) {
	int i;
	clearString(string);
	for (i = 0; i<16; i++) {
		if (strcmp(machine_commands[i].name, string) == 0) {
			return &machine_commands[i];
		}

	}
	return NULL;
}

struct symbol * getSymbol(char * str) {
	int i;
	printf("in getSymbol: tested symbol: %s.\n", str);
	for (i = 0; i<symbole_table_size; i++) {
		if (strcmp(str, symbol_table[i].label) == 0) {
			printf("--- in getSymbol --- returning symbol: %s when i is: %d, printing symbols\n", symbol_table[i].label, i);
			printSymboles();
			return &symbol_table[i];
		}
	}
	printf("--- in getSymbol --- returning NULL\n");
	return NULL;

}
int isLabel(char * string) {
	char buf[10];
	if (string[0] == '.' || getCommand(strncpy(buf, string, strlen(string)) - 1) != NULL || !isalpha(string[0]) || string[strlen(string) - 1] != ':') {
		return 0; /*false*/
	}
	else {
		return 1; /*true*/
	}

}

void addToSymboleTable(char * label, int address, int isExternal, int isCommand) {
	printf("in addTSymboleTable, symbole_table_size is: %d", symbole_table_size);
	if (getSymbol(label) != NULL) {
		fprintf(stderr, "ERROR: label %s already exists, getSymbol result is\n", label);
		error = 1;
		return;
	}
	arrayRealloc(&symbol_table, sizeof(struct symbol)*symbole_table_size, sizeof(struct symbol));

	clearString(label);
	/*this is not allocationg*/
	printf("about to do strcpy");
	strcpy(symbol_table[symbole_table_size].label, label);
	symbol_table[symbole_table_size].address = address;
	symbol_table[symbole_table_size].isExternal = isExternal;
	symbol_table[symbole_table_size].isCommand = isCommand;


	symbole_table_size++;
	printf("in addToSymboleTable, add was made, printing symbols:\n");
	printSymboles();
}
void clearSpaces(char *str) {
	char* i = str;
	char* j = str;
	while (*j != 0)
	{
		*i = *j++;
		if (*i != ' ' && *i != '\n')
			i++;
	}
	*i = 0;
}
void addString(char * token) {
	unsigned int i;
	clearSpaces(token);
	if (token[0] != '"' || token[strlen(token) - 1] != '"' ||
		memchr(token + 1, '"', strlen(token) - 2) != NULL) {

		fprintf(stderr, "ERROR: argument-%s is not a valid string.\n", token);
		error = 1;
		return;
	}
	for (i = 1; i < (strlen(token) - 1); i++) {
		arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(word), sizeof(word));

		DATA_SEG[DC].content = token[i];
		DC++;
	}
	arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(word), sizeof(word));
	DATA_SEG[DC].content = 0; /*end of string*/
	DC++;

}
void addData(char * token) {

	word num;
	token = strtok(token, ",");
	while (token != NULL) {
		num.content = strtol(token, NULL, 10); /*add check for wrong numbers*/
		arrayRealloc(&DATA_SEG, sizeof(DC) * sizeof(word), sizeof(word));
		DATA_SEG[DC].content = num.content;
		DC++;
		token = strtok(NULL, ",");
	}


}
enum argument_types getArgumentType(char * argument) {
	/*get a string. and check the type of its argument*/
	argument = strtok(argument, " "); /*remove initial spaces*/
	if (argument[0] == '#') { /*immidiate argument*/
		return immidiate;
	}
	if (argument[0] == 'r') {
		if (argument[2] != '[') {
			return reg_direct;
		}
		else {
			return reg_index;
		}
	}
	else {
		return direct;
	}


}

void writeCommand(struct Command command, char * arguments) {
	/*check for errors*/

	word command_word;
	struct unwritten_argument unwritten_1, unwritten_2;
	char * first_arg, *second_arg, *thired_arg;

	int words = 0;

	enum argument_types arg1 = 0, arg2 = 0;
	printf("WTFFF\n");
	if (arguments == NULL) {
		printf("im fcked\n");
	}
	else
		printf("DEBUG:in writeCommand, arguments are: %s\n", arguments);

	first_arg = strtok(arguments, ",");
	/*using strtok to remove all wihte spaces*/

	if ((command.operand_number == 0 && first_arg != NULL) && first_arg[0] != '\n') {
		fprintf(stderr, "ERROR: trying to pass argument '%s' to a command that doesn't takes \
			arguments (%s)\n", first_arg, command.name);
		error = 1;
		return;
	}
	printf("first arg finished(%s), ", first_arg);
	second_arg = strtok(NULL, ",");
	clearString(first_arg);
	if (command.operand_number == 1 && second_arg != NULL) {
		fprintf(stderr, "ERROR: trying to pass second argument '%s' to a command that takes 1 \
			argument (%s)\n", second_arg, command.name);
		error = 1;
		return;
	}
	printf("second arg finishd(%s), ", second_arg);
	if ((thired_arg = strtok(NULL, ",")) != NULL) {
		fprintf(stderr, "ERROR: trying to pass thired argument '%s' to a command that takes 2 \
			arguments (%s)\n", thired_arg, command.name);
		error = 1;
		return;
	}
	/*check argument types*/


	if (command.operand_number == 0) {
		words = 1;
	}
	if (command.operand_number == 1) {
		words = 1;
		arg1 = getArgumentType(first_arg);
		unwritten_1.type = arg1;
		strcpy(unwritten_1.argument, first_arg);

	}
	if (command.operand_number == 2) {
		arg1 = getArgumentType(first_arg);
		arg2 = getArgumentType(second_arg);
		if (arg1 == reg_direct && arg2 == reg_direct) {
			unwritten_1.type = double_reg_direct;
		}
		else {
			unwritten_1.type = arg1;
			strcpy(unwritten_1.argument, first_arg);


			unwritten_2.type = arg2;
			strcpy(unwritten_2.argument, second_arg);

			words = 2;
		}
	}

	printf("words needed finished, ");
	/*  unsuded     group                         opcode         firstArg  */
	command_word.content = (7 << 12) + (command.operand_number << 10) + (command.opcode << 6) + (arg1 << 4) +
		/*second arg     ARE*/
		(arg2 << 2);
	printf("in writeCommand, IC is: %d\n", IC);
	printf("word calculated(%d), size of arr is %d ", words, (int)(sizeof(struct command_segmet_rapper)*(IC)+sizeof(struct command_segmet_rapper) * words));
	arrayRealloc(&COMMAND_SEG, sizeof(struct command_segmet_rapper)*(IC),sizeof(struct command_segmet_rapper) * (words + 9));

	printf("memory allocated, ");
	if (COMMAND_SEG == NULL) {
		fprintf(stderr, "ERROR: realloc failed");
		exit(1);
	}/*clear*/

	COMMAND_SEG[IC].isWord = 1;
	COMMAND_SEG[IC++].command_segment_elements.incoded_word = command_word;

	if (words >= 1) {
		COMMAND_SEG[IC++].command_segment_elements.unwrittenArgument = unwritten_1;

	}


	if (words == 2) {
		COMMAND_SEG[IC++].command_segment_elements.unwrittenArgument = unwritten_2;
	}


	printf("done.\n");


}
void adjustSymbols() {
	int i;
	for (i = 0; i<symbole_table_size; i++) {
		if (!symbol_table[i].isExternal && !symbol_table[i].isCommand) { /*if its data*/
			symbol_table[i].address += IC;
		}
	}

}


void writeOperands(char * arguments) {

	/*TODO: change things with reg_direct!!!*/
	printf("DEBUG:in writeOperands, arguments are: %s", arguments);
	/*now ic points to the command, so we need to increase it*/
	IC++;
	if (COMMAND_SEG[IC++].isWord) {
		return;
	}
	else {
		word temp;
		printf("requesting first arg\n");
		temp = argToWord(COMMAND_SEG[IC].command_segment_elements.unwrittenArgument);
		if (COMMAND_SEG[IC].command_segment_elements.unwrittenArgument.type == reg_direct) {
			temp.content = (temp.content << 6); /*adjusting the word acording to the rules*/
		}
		COMMAND_SEG[IC].command_segment_elements.incoded_word.content =
			temp.content;

		IC++;
	}
	if (COMMAND_SEG[IC++].isWord) {
		return;
	}
	else {
		printf("requesting second arg\n");
		COMMAND_SEG[IC].command_segment_elements.incoded_word.content = argToWord(COMMAND_SEG[IC].command_segment_elements.unwrittenArgument).content;
		IC++;
	}


}

word argToWord(struct unwritten_argument arg) {
	word incoded_word;
	switch (arg.type) {
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
		break;
	default:
		printf("ERROR: somthing wierd happened in argToWord, argument recives was %s with type %d\n", arg.argument, arg.type);
		incoded_word.content = 0;
		break;
	}
	return incoded_word;

}

word doubleRegDirectToWord(char * arg) {
	word * res = malloc(sizeof(word));
	res->content = (regDirectToWord(strtok(arg, ",")).content << 8) + (regDirectToWord(strtok(NULL, ",")).content << 2);
	return *res;
}
/*CHANGE IT**/

word regIndexToWord(char * arg) {
	word * res = malloc(sizeof(word));
	int first_reg, second_reg;
	sscanf(arg, "r%d[r%d]", &first_reg, &second_reg);
	if (first_reg % 2 != 1) {
		fprintf(stderr, "ERROR: first reg in indexing must be uneven, but its: %d \n", first_reg);
		error = 1;
		res->content = 0;
		return *res;
	}
	if (second_reg % 2 != 0) {
		fprintf(stderr, "ERROR: second reg in indexing must be even, but its: %d \n", second_reg);
		error = 1;
		res->content = 0;
		return *res;
	}
	res->content = (first_reg << 2) + (second_reg << 8);
	return *res;
}

word regDirectToWord(char * arg) {
	word * res = malloc(sizeof(word));
	char * token;
	int reg_num;
	/*using strtok to remove all wihte spaces*/
	token = strtok(arg, " ");
	sscanf(token, "r%d", &reg_num);
	if (reg_num<0 || reg_num > 7) {
		fprintf(stderr, "ERROR: there are only 8 registers, r0-r7. register number: %d is invalid\n", reg_num);
		res->content = 0;
		error = 1;
		return *res;
	}
	res->content = reg_num << 2;
	return *res;

}


word directToWord(char * arg) {
	word * res = malloc(sizeof(word));
	struct symbol * current_symbol = getSymbol(arg);

	if (current_symbol->isExternal) {
		writeExternal(*current_symbol);
		res->content = 1;
		return *res; /*translates to 0000000000000-01*/
	}
	if (current_symbol->isCommand) {
		fprintf(stderr, "ERROR: cant use a command (%s) as an operand for a command\n", arg);
		error = 1;
		res->content = 0;
		return *res;
	}
	res->content = (current_symbol->address << 2) + 2;/*for A R E*/
	return *res;

}

word immidiateToWord(char * arg) {
	word * res = malloc(sizeof(word));
	int temp;
	char * token;
	token = strtok(arg, "#");

	if ((temp = atoi(token))) { /*there may or may not be spaces before the '#'*/
		printf("DEBUG: SPACES BEFORE '#' \n");

	}
	else {
		token = strtok(NULL, "#");
		temp = atoi(token);
	}
	if (temp<0) {
		temp = ~temp;
	}
	temp = (temp << 2);
	res->content = temp;
	return *res;
}



void writeExternal(struct symbol current_symbol) {

	arrayRealloc(&externList, sizeof(struct external)* external_size, sizeof(struct external));

	externList[external_size].current_symbol = current_symbol;
	externList[external_size].line = IC + 100;
	external_size++;
}
void printSymboles() {
	int i;
	printf("***********DEBUG: printing symbole table***********\n");
	for (i = 0; i<symbole_table_size; i++) {
		printf("%s,", symbol_table[i].label);
	}
	printf("\n***********DEBUG: done printing symbole table***********\n");
}
void writeEntry(char * arg) {
	if(entryList == NULL){
		printf("idk what the fck is going on\n");
		
	}
	printf("dark magic is not real\n");
	printf("about to realloc entry: %s, giving it size of %d",arg,(int)( sizeof(struct external)* entry_size+ sizeof(struct external)));
	entryList = realloc(entryList, (sizeof(struct external)* entry_size+ sizeof(struct external)));
	
	printf("malloced successaafaf\n");
	printf("arg is: %s", arg);

	printSymboles();
	clearString(arg);
	entryList[entry_size].current_symbol = *getSymbol(arg);
	entryList[entry_size].line = entryList[entry_size].current_symbol.address;
	entry_size++;
}




void utilReset() {
	
	/*for (i = 0; i<symbole_table_size; i++) {
		free(symbol_table[i].label);

	}*/
	free(symbol_table);
}
