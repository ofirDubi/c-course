#include <stdio.h>
/*declaring the funciton that will calculate the scalar product
	vec1[] => the first vector
	vec2[] => the second vector
	arrayLength => the length of the vectors (assuming they have
	the same length)
*/
int scalar_product(int vec1[], int vec2[], int arrayLength);

int main(){
	int i, length =0; /* i is used for the loop, length is the 
						length of the array */
	/*declaring the vectors, with a buffer size of 100 */
	int vec1[100];
	int vec2[100];
	
	printf("enter length of the vectors: \n");
	scanf("%d", &length); /* askikng the user for the vector length*/
	
	for(i=0; i<length; i++){
		/*getting the user input for each vector */
		printf("enter the %d value of vector number 1\n", i+1);
		
		scanf("%d", &vec1[i]);
		
		printf("enter the %d value of vector number 2\n", i+1);
		
		scanf("%d", &vec2[i]);
	}
	printf("scala_product is: %d", scalar_product(vec1,vec2,length)); 
	/*prints the resault of the scalar product */
	return 0;
} 

int scalar_product(int vec1[], int vec2[], int arrayLength){
	int amount = 0; /*the scalar product */
	int i;
	for( i=0; i < arrayLength; i++){
		amount = amount + vec1[i]*vec2[i]; /* calculating the scalar product */
	}
	return amount;
}