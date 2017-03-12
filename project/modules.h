
#define all_types  {1,1,1,1}
#define not_immediate {0,1,1,1}

typedef word unsigned short int:15;

struct symbol {
	char * label;
	int address;
	unsigned int isExternal:1, isCommand:1;
	};

struct argument_types {
	unsigned int immediate:1;
	unsigned int direct:1;
	unsigned int reg_index:1;
	unsigned int reg_direct:1;
};
struct Command{
	char * name; 
	char opcode;
	unsigned int operands_number:2;
	struct argument_types first_arg;
	struct argument_types second_arg;
};

struct Command machine_commands[16] ={{"mov",0, 2, all_types,not_immediate},
	{"cmp", 1, 2, all_types, all_types}, {"add",2,2,all_types,not_immediate},
	{"sub",3,2,all_types,not_immediate}, {"not",4,1,not_immediate},
	{"clr",5,1, not_immediate}, {"lea",6,2,{0,1,1,0},not_immediate},
	{"inc",7,1,not_immediate}, {"dec", 8, 1, not_immediate}, 
	{"jmp",9,1,not_immediate}, {"bne", 10, 1, not_immediate},
	{"red", 11, 1, not_immediate}, {"prn", 12, 1, all_types},
	{"jsr", 13, 1,not_immediate}, {"rts", 14,0}, {"stop",15,0}
	
	};
int DC, IC
word * COMMANDS_SEG;
word * DATA_SEG;
int isLabel(char * string);

