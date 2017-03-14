#include <stdio.h>
struct primaries_date{
	int month, day, hour;
};

struct usa_primaries{
	struct primaries_date date;
	char *state;
	int is_open; /*boolean*/
	struct * usa_primaries nextNode;
	
};

int main(){
	
	
	
}

void delete(struct usa_primaries *node, struct primaries_date date1, struct primaries_date date2){
	struct usa_primaries *first_keep, *temp;
	
	while(before(node->nextNode->date, date1)){
		node = node->nextNode;
	}
	first_keep = node;
	node = node->nextNode;
	while(before(node->date, date2){
		temp = node;
		node = node->nextNode;
		free(temp);
	}
	first_keep->nextNode = node;
}

int before( struct primaries_date before, struct primaries_date after){/*checks if date1 is or after date 2*/
	if(before.month<after.month){
		return 1; 
	}else if(before.month == after.month){
		if(before.day < after.day){
			return 1;
		}else if(before.day == after.day){
			if(before.hour <= after.hour){
				return 1;
			}
		}
	}
	return 0;
}