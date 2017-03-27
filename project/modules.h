#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define all_types  {1,1,1,1}
#define not_immediate {0,1,1,1}

typedef struct word {
	unsigned  int content : 15;
} word;
enum argument_types { immidiate, direct, reg_index, reg_direct, double_reg_direct }; /*double_reg_direct is for when both operands  are
																					 reg_direct */

struct unwritten_argument {
	enum argument_types type;
	char * argument;
};

struct command_segmet_rapper {
	unsigned int isWord : 1; /*tagged union*/
	union command_segment_elements {
		struct unwritten_argument unwrittenArgument;
		word incoded_word;
	}command_segment_elements;
};

struct symbol {
	char * label;
	int address;
	unsigned int isExternal : 1, isCommand : 1;
};

struct external {
	struct symbol current_symbol;
	int line;
};

struct possible_argument_types {
	unsigned int immediate : 1;
	unsigned int direct : 1;
	unsigned int reg_index : 1;
	unsigned int reg_direct : 1;
};
struct Command {
	char * name;
	char opcode;
	unsigned int operand_number : 2;
	struct possible_argument_types first_arg;
	struct possible_argument_types second_arg;
};


struct symbol * getSymbol(char * label);

struct Command * getCommand(char * string);

void addToSymboleTable(char * label, int address, int isExternal, int isCommand);

int isLabel(char * string);

word argToWord(struct unwritten_argument arg);

word doubleRegDirectToWord(char * arg);

word regIndexToWord(char * arg);

word regDirectToWord(char * arg);

word directToWord(char * arg);

word immidiateToWord(char * arg);

void addData(char * token);

void addString(char * token);

void writeOperands(char * arguments);

void writeCommand(struct Command command, char * arguments);

void adjustSymbols();

void writeExternal(struct symbol current_symbol);

void writeEntry(char * arg);


extern int error;
extern int DC, IC, symbole_table_size;
extern struct command_segmet_rapper * COMMAND_SEG;
extern word * DATA_SEG;
extern struct external * externList;
extern int external_size;

extern struct external * entryList;
extern int entry_size;

