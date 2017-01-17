#include <stdio.h>
#include<stdlib.h>
/*what i realy need to do:
	insted of creating a char variable for each item in the set
	i use a 16-byte long variable - 128 bits
	to do that i create a struct.. use malloc

*/
typedef char *set;
set A, B,C;
int main(){
	if(A==NULL){
		putchar('k');
	}
	free(A);
	A =  malloc(16);
	A[0]='a';
	A[2]='3';
	B = A;
	B[0] = '5';
	C = malloc(1);
	
	B = C;
	C[0] = '3';
	putchar(A[0]);
	free(A);
	return 0;
}
