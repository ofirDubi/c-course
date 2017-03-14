/*q7 - a*/

struct studentNode {
	int grade;
	int id;
	struct studentNode * nextStudent;
}
/*q7-b*/


studentNode *initList(){
	FILE *indexFile, *StudentFile;
	char line[100]; /*buffer size*/
	int curr_id;
	struct studentNode firstNode;
	struct studentNode *currNode = &firstNode;
	indexFile = fopen("index.txt", "r"); /*assuming that the index file is called
									"index.txt" */
	StudentFile = fopen("students.txt", "r"); /*assuming that the index file is called
									"index.txt" */
	fgets(line, 100, studentFlie);
	
	/*loop through student file*/
	firstNode = newStudent(line);
	while(fgets(line  , 100, studentFlie)!=NULL){
		currNode->nextStudent = &newStudent(line);
		currNode = currNode->nextStudent;
	}
	/*now currNode is the last node on the list*/
	currNode->newStudent = &firstNode;
	while(fgets(line  , 100, indexFile)!=NULL){
		sscanf(line,"%d", &curr_id);
		currNode->nextStudent = &newStudent(line);
		currNode = currNode->nextStudent;
	}
}
studentNode * studentById(int id, struct studentNode node){
	while(node->id != id){ /*assuming the id exists in list*/
		node = node->nextStudent;
	}
	return node;
}

studentNode newStudent(char * line){
	struct studentNode node = malloc(sizeof(struct studentNode));
	sscanf(line, "%d, %d", &studentNode.id, &studentNode.grade); /*id and a grade in every line*/
	return node;
}