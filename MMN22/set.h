#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 1000


typedef char * set;

set A,B,C,D,E,F;

void assignSet(set S, char setName);
set charToSet(char set);
void print_set(set S);
void read_set(char *input);
void union_set(set A, set B, char setName);
void intersect_set(set A, set B, char setName);
void sub_set(set A, set B, char setName);
void halt();
 static char bool = 1;
