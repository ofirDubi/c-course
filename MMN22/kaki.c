#include <stdio.h>
#include<stdlib.h>
/*what i realy need to do:
	insted of creating a char variable for each item in the set
	i use a 16-byte long variable - 128 bits
	to do that i create a struct.. use malloc

*/
#define act(action) x action y
typedef char *set;

int main(){
		int x=1, y=2;
	
		printf("%d", act(+));
	
	return 0;
}
