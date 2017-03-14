
/*
Author: Ofir Dubi
Date: 28/1/2017
Description: This file ocntains a function that recives a variable number of integer-type arguments
				that ends with -1, and returns the smallest integer from all function calls
				so far

*/
#include <stdarg.h>
#include <stdio.h>
#define MAX 100 /* the maximun number recived is 100*/ 
int min_call(int first_arg, ...); /*when using stdarg, the function must recive 
								an int argument before the argument list  itself*/ 
int main(){/*example calls*/

	printf("result: %d\n",min_call(90,70,20,-1));
	printf("result: %d\n",min_call(3,50,20,44,12,90,-1));
	printf("result: %d\n",min_call(-1));
	printf("result: %d\n",min_call(0,70,2,15,-1));
	printf("result: %d\n",min_call(90,70,20,-1));

	return 0;
}

int min_call(int first_arg, ...){
	static int smallest =MAX; /*initialize the smallest number to the max possible one*/
	int  num;
	va_list list; /*initilize a new va_list object called list */
	va_start(list, first_arg);
	printf("min_call(");
	for(num = first_arg;num!=-1;num=va_arg(list,int)){ /*if num is equal to -1, 
														then it has reached the end of the list*/
	
		printf(" %d,", num);
		if(num<smallest){
			smallest = num;
		}
	}
	printf(" -1)\n");
	va_end(list); /*frees the memory needed to contain the list */
	return smallest;
}