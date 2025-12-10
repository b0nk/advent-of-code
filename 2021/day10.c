#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node{
	char* line;
	Node* chunks;
	Node* next;
};

Node* create_node(char str[]){
	Node* node = malloc(sizeof(Node));
	
	node->line = strdup(str);
	node->chunks = NULL;
	node->next = NULL;
	
	return node;
}


int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		
		head = create_node(line);
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
