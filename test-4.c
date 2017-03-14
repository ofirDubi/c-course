#include <stdio.h>
#define reverse(arr, length,res) {\
	unsigned int mask = 1, lower_bit, upper_bit;\
	int i,j;\
	 /* we want to take [0,0,1,1  ,1,1,0,1] => 1011 1100 */\
	for(i=0;i<length; i++){\
		int temp = arr[i];\
		for(j=0; j<(sizeof(int)/2)*8;j++){\
			lower_bit = ((mask<<j)&arr[i])<<(sizeof(int)*8-j*2-1) ;/*keeps the lower bit */ \
			printf(" for element: %d lower bit: %d\n", i+1,lower_bit);\
			upper_bit = ((mask<<(sizeof(int)*8-j-1)) & arr[i])>>(sizeof(int)*8-j*2-1) ;/*upper bit */ \
			arr[i] &= ~(mask<<j)& ~(mask<<(sizeof(int)*8-j-1)) ; /*make the lower bit zero */ \
			arr[i] |= lower_bit | upper_bit;\
	}\
	printf("%d\n",arr[i]);\
	if(temp==arr[i]){\
		res++;\
	}	\
	}\
}

void bin(int n)
{

 printf("%d", n);
}

int main()

{
	
	unsigned int arr[8] = {1,2,3,4,5,6,7,8};
	int i, n;
	printf("%d\n",(int)sizeof(char));
	for(i=0; i<8; i++){
		printf("element %d before change: ", i+1);
		bin(arr[i]);
		putchar('\n');
	}
	reverse(arr,8,n);
	for(i=0; i<8; i++){
		printf("element %d after change:  ", i+1);
		bin(arr[i]);
		putchar('\n');
	}
	printf("n is %d\n ", n);
	
	return 0;
}