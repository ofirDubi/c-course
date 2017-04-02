#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define arrayRealloc(array,array_size, size) {\
\
	printf("____reallocing____\n");\
	*array = realloc(*array, ((array_size)+(size)));\
	printf("done reallocing\n");\
	\
}

typedef struct word {
	unsigned  int content : 15;
} word;
struct symbol {
	char label[20];
	int address;
	unsigned int isExternal : 1, isCommand : 1;
};

struct external {
	struct symbol current_symbol;
	int line;
};

struct external * entryList = NULL;
int entry_size = 0;
void kaki();
int main(){
	printf("about to realloc entry, giving it size of %d",(int)( sizeof(struct external)* entry_size+ sizeof(struct external)));
	kaki();
	
	return 1;
}
void kaki(){
	word * res = malloc(sizeof(word));
	res->content = 2;
	printf("%d\n", res->content);
	arrayRealloc(&entryList,  sizeof(struct external)* entry_size, sizeof(struct external));
}