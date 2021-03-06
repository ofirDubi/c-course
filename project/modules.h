#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*also contains string.h*/

#define all_types  {1,1,1,1} /*used to initialize the command list*/
#define not_immediate {0,1,1,1}

typedef struct word {
	unsigned  int content : 15;
} word;
enum argument_types { immediate, direct, reg_index, reg_direct, double_reg_direct }; /*double_reg_direct is for when both operands are
					reg_direct - they fit into one word*/

struct unwritten_argument {/*place holder for operands*/
	int line; /*used mostly for errors*/
	enum argument_types type;
	char argument[20];
};

struct command_segmet_rapper { /*the code that will be written in obj*/
	unsigned int isWord : 1; /*tagged struct*/
	struct command_segment_elements {
		struct unwritten_argument unwrittenArgument;
		word incoded_word;
	}command_segment_elements;
};

struct symbol { /*a structure for labels*/
	char label[20];
	int address;
	unsigned int isExternal : 1, isCommand : 1;
};

struct external { /*a structure for the extern and entry file*/
	struct symbol current_symbol;
	int line;
};

struct possible_argument_types {
	unsigned int immediate : 1;
	unsigned int direct : 1;
	unsigned int reg_index : 1;
	unsigned int reg_direct : 1;
};
struct Command { /*a structure for commands*/
	
	char * name;
	char opcode;
	unsigned int operand_number : 2;
	struct possible_argument_types first_arg;
	struct possible_argument_types second_arg;
};

/*function declerations */
struct symbol * getSymbol(char * label);

struct Command * getCommand(char * string);

void addToSymbolTable(char * label, int address, int isExternal, int isCommand);

int isLabel(char * string);

word argToWord(struct unwritten_argument arg);

word doubleRegDirectToWord(char * arg);

word regIndexToWord(char * arg);

word regDirectToWord(char * arg);

word directToWord(char * arg);

word immediateToWord(char * arg);

void addData(char * token);

void addString(char * token);

void writeOperands(char * arguments);

void writeCommand(struct Command command, char * arguments);

void adjustSymbols();

void writeExternal(struct symbol current_symbol);

void writeEntry(char * arg);

void printData();

void clearSpaces();

void strToUpper(char * str);

void tabsToSpaces(char * str);
void strToLower(char * str);

char * trimSpaces(char * str);

int subsequentChar(char * str, char mark);

/*global variable declerations*/

extern int error; /*if an error acurs during the compilation, the value of	
					error will be 1*/
					
		/*DC - data countre, IC - instractions counter, line_num - the current line in code (used for errors)*/			
extern int DC, IC, symbol_table_size, line_num;
extern struct command_segmet_rapper * COMMAND_SEG;
extern word * DATA_SEG;
extern struct external * externList;
extern int external_size;

extern struct external * entryList;
extern int entry_size;

extern int max_IC;/*the number of command words in the obj file*/
