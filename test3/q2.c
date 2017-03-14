#include <stdio.h>

#define oddbits(obj, res){\
	int i, pipi;\
	unsigned long mask = 1;\
	res=0;\
	for(i=1;i<(sizeof(obj)*8);i+=2){\
		pipi = obj&(mask<<i);\
		if(pipi != 0){\
		res++;\
		}\
	}\
}
int main(){
	int arr[100], re[100];
	int i, temp=1, kaki;
	for(i=0;i<100;i++){
		arr[i] = i;
	}
	for(i=0;i<100;i++){
		kaki = arr[i];
		oddbits(kaki,temp);
		re[i] = temp;
		printf("for %d : %d\n",arr[i],re[i]);
	}
	return 0;
}