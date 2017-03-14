#include <stdio.h>
void main(void){
	char vec[] = "abcdefghij";
	putchar(vec[vec[1] -vec[0]] +=1);
}