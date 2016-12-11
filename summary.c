#include <stdio.h>
#define BUFFER 100

int * summary(int arr1[], int length);

int main(){
	int length, i;
	int arr1[BUFFER];
	int *arr2;
	
	scanf("%d", &length);
	for(i=0; i<length; i++){
		printf("pls enter digit number %d\n", i);
		scanf("%d", &arr1[i]);
	}
	arr2 = summary(arr1, length);
	for(i=0; i<length; i++){
		printf("digit number %d in arr2 is: %d \n", i, *(arr2+i));
	}
	return 0;
}

int * summary(int arr1[], int length ){
	static int arr2[BUFFER];
	int i;
	arr2[0] = arr1[0];
	for(i=1; i<length; i++ ){
		arr2[i] = arr2[i-1] + arr1[i];
	}
	return arr2;
}