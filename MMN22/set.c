#include "set.h"

/*change char to malloc(or somthing like that) */

 
void callFunc

set A,B,C,D,E,F;
char bool  = 1; /*true */
int main(){
	char input[MAXLENGTH];
	char command[MAXLENGTH];
	while(bool){
		printf("enter the wanted command. list of commands:\n%s",
		"print_set, read_set, union_set, intersect_set, sub_set, halt\n ##");
		gets(input);
		command = strtok((input)," ") 
	
		if(strcmp(command,"print_set") == 0){
			command = strtok(NULL, " ")
			switch (input[0]){
			case 'A': strcpy(A, S);
					printf("set is A\n");
			case 'B' : strcpy(B, S);
			case 'C' : strcpy(C, S);
			case 'D' : strcpy(D, S);
			case 'E' : strcpy(E, S);
			case 'F' : strcpy(F, S);
			case default: printf("no such group as %c\n",input[0] )
	}
			print_set();
		}
		if(strcmp(command, "read_set") ==0){
			read_set(command )
		}
		
	}
	printf("enter groud for read_set\n");
	gets(arr);
	
	read_set(arr);
	printf("Got set, now printing it, %d\n", A[0]);
	print_set(A);
	
}

void callFunc()

void print_set(set S){
	int i=0;
	if(S[i] != '\0'){ /*if the set is not empty*/
		while(S[i] != '\0'){
			for(i; i<16 && S[i] != '\0'; i++){
				printf("%d ", S[i] );
			}
			printf("\n");
		}
	}
	
}

void read_set(char input[]){ /*this function should be changed to work with pointers */
	int i;
	int var;
	int k =1;
	int endOfNum = 1; 
	set S;
	int loc =0;
	
	printf("%s \n", input+1);
	for (char *p = strtok((input+1),","); p != NULL; p = strtok(NULL, ",")){
		/*printf("p is: %s\n", p);*/
		var = atoi(p);
		/*printf("var is: %d\n", var);*/
		S[loc] = var;
		/*printf("S[loc] is: %d\n", S[loc]);*/
		loc++;
	}
	switch (input[0]){
		case 'A': strcpy(A, S);
					printf("set is A\n");
		case 'B' : strcpy(B, S);
		case 'C' : strcpy(C, S);
		case 'D' : strcpy(D, S);
		case 'E' : strcpy(E, S);
		case 'F' : strcpy(F, S);
		case default: printf("no such group as %c\n",input[0] )
	}
	
	/* printf("%d\n", A[0]); */
}

void union_set(set A, set B, set C){
	strcat(C, A);
	strcat(C, B);
}

void intersect_set(set A, set B, set C){
	int i, loc = 0;
	
	for(i=0; i<strlen(A) && i<strlen(B); i++){
		if(strchr(A,B[i])){
			C[loc] = B[i];
			loc++;
		}
	}
}

void sub_set(set A, set B, set C){/* maybe needs to be changed */
	int i, loc = 0;
	
	for(i=0; i<strlen(A) && i<strlen(B); i++){
		if(strchr(B,A[i]) == NULL){
			C[loc] = B[i];
			loc++;
		}
	}
	if(strlen(A)>strlen(B)){
		strcat(C, A+strlen(B));
	}
}
void halt(){
	bool = 0;
}