#include "set.h"

void assingSet(set S, char setName){
	switch (setName){
		case 'A': free(A); A = S;
					printf("set is A\n"); break;
		case 'B' : free(B); B = S; break;
		case 'C' : free(C); C = S; break;
		case 'D' : free(D); D = S; break;
		case 'E' : free(E); E = S; break;
		case 'F' : free(F); F = S; break;
		default: printf("in read set: no such group as %c\n", setName );
	}
}

set charToSet(char set){
	
	switch (set){
			case 'A': return A;
					
			case 'B' : return B;
			case 'C' : return C;
			case 'D' : return D;
			case 'E' : return E;
			case 'F' : return F;
			default: printf("in char to set - no such group as %c\n",set ); return NULL;
	}
}
void print_set(set S){
	int i=0, j=0;
	char mask = 1;
	int count = 1;
	if(S != NULL){ /*if the set is not empty*/
		
		for(i=0; i<16;i++){
			
			mask = 1;
			/*loops every bit*/
			for(j=0; j<8; j++){
				
				if((S[i]&mask)==mask){
					printf("%d, ", (i*8)+j);
					count++;
				}
				mask = mask << 1;
			}
			
			if(count>15){
				printf("\n");
				count = 0;
			}
		
		}
	}else{
		printf("set is empty\n");
	}
	printf("\n");
}

void read_set(char *input){ /*this function should be changed to work with pointers */
	int i=0;
	int var;
	
	set S = malloc(16);
	int loc =0;
	char mask = 1;
	char *p;
	for(i=0; i<16;i+=1){
		S[i] = 0;
	}
	
	
	i=0;
	/*input[11] is were the numbers begin
	 *input[9] is were the set name is */ 
	for (p = strtok((input+11),","); p != NULL; p = strtok(NULL, ",")){
		
		var = atoi(p);
		if(var == -1){
			break;
		}
		printf("var is: %d\n", var);
		if(var > 127 || var < 0 ){
			/*printf("%d is out of range\n", var);*/
			return;
		}
		/* the i loc*/
		loc = var/8;
		
		/*printf("loc is: %d, or operator is: %d\n",loc, mask<<(var%8));*/
		S[loc] = S[loc]|(mask<<(var%8));
		/*printf("S[loc] is: %d\n", S[loc]);*/
		loc++;
	}
	if(var != -1){
		printf("Error: a set must end with '-1'\n");
		return;
	}
	assingSet(S, input[9]);
	
	
}

void union_set(set A, set B, char setName){
	
	int i=0;
	set S;
	if(A ==NULL || B == NULL){
		printf("one of the grous given as arguments were null\n");
		return;
	}
	printf("freed\n");
	S = malloc(16);
	printf("malloced\n");
	
	printf("assigned\n");
	for(i=0; i<16; i++){
		printf("i: %d\n", i);
		S[i] = A[i]|B[i];
	}
	printf("looped\n");
	
	printf("printed\n");
	assingSet(S, setName);
}
void intersect_set(set A, set B, char setName){
	
	int i=0;
	set S;
	if(A ==NULL || B == NULL){
		printf("one of the grous given as arguments were null\n");
		return;
	}
	printf("freed\n");
	S = malloc(16);
	printf("malloced\n");
	
	printf("assigned\n");
	for(i=0; i<16; i++){
		
		S[i] = A[i]&B[i];
	}
	printf("looped\n");
	
	printf("printed\n");
	assingSet(S, setName);
}

void sub_set(set A, set B, char setName){/* maybe needs to be changed */
	int i=0;
	set S;
	if(A ==NULL || B == NULL){
		printf("one of the grous given as arguments were null\n");
		return;
	}
	printf("freed\n");
	S = malloc(16);
	printf("malloced\n");
	
	printf("assigned\n");
	for(i=0; i<16; i++){
		/*A[i] xor B[i]
		
		*/
		S[i] = A[i]&(~B[i]);
	}
	printf("looped\n");
	
	printf("printed\n");
	assingSet(S, setName);
}
void halt(){
	bool = 0;
	free(A);
	free(B);
	free(C);
	free(D);
	free(E);
	free(F);
}