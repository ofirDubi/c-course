#include <modules.h>
#include <string.h>
#include <ctype.h>
struct Command getCommand(string){
	int i;
	for(i=0; i<16; i++ ){
		if(strcmp(machine_command[i], string)){
			return machine_command[i];
		}
		
	}
	return NULL;
}

int isLabel(char * string){
	if(string[0] == '.' || getCommand(string) || !isalpha(string[0)){
		return 0; /*false*/
	}else{
		return 1;
	}
	
}