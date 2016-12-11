#include <math.h>
#include <stdio.h>

int f(unsigned x);
int main()
{
	int x;
	f(x);
}

inf f(unsigned x){
		/* make mask*/
	int msk = -(1.0/3) + (4.0/3)*pow(4,sizeof(int)*4-1);
	
	printf("\n using mask : \n");
	printBin(msk);
	putchar('\n')

	return ((x>>1)&msk) | ((x<<1)&-msk)
}

void s(int x){
	unsigned mask = 1<<(sizeof(int)*8-1);
	while(mask){
		putchar((x&mask)?:'1':'0');
	}
}