#include <stdio.h>
int crack(int org, int dest);
int main(){
	int org = 0x38b2;
	int dest = 0x3693;
	
	
	printf("%d the number that will make it work is:" ,crack(org, dest));
	printf("%d", dest & org);
	return 0;
	
	
}

int crack(int org, int dest){
	int i;
	printf("org : %d, des: %d\n", org, dest);
	for(i=0; i<=0xffff;i++){
		if(dest & i == org){
			printf("found resault!!, using & : %d\n", i);
			//return i;
		}
		if((dest^i) == org){
			printf("found resault!!, using ^ : %d\n", i);
			//return i;
		}
		/*if(org-i == dest){
			printf("found resault!!, using ~ : %d\n", i);
			//return i;
		}*/
		if((org|i) == dest){
			printf("found resault!!, using | : %d\n", i);
			//return i;
		}
		
	}
	return -1;
}